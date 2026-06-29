#!/usr/bin/env python3
"""Self-contained UE 5.8 -> UE 5.7 MCP PortKit.

The kit intentionally stores all mutable working state under this directory and
does not vendor Epic source code. It imports source from the user's licensed
EpicGames/UnrealEngine access, then applies local patch files.
"""

from __future__ import annotations

import argparse
import fnmatch
import json
import os
import re
import shutil
import stat
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


KIT_DIR = Path(__file__).resolve().parent
MANIFEST_PATH = KIT_DIR / "portkit.manifest.json"


class PortKitError(RuntimeError):
    pass


def log(message: str) -> None:
    print(f"[MCPPortKit] {message}")


def run(
    args: list[str],
    *,
    cwd: Path | None = None,
    check: bool = True,
    capture: bool = False,
) -> subprocess.CompletedProcess[str]:
    result = subprocess.run(
        args,
        cwd=str(cwd) if cwd else None,
        check=False,
        text=True,
        encoding="utf-8",
        errors="replace",
        stdout=subprocess.PIPE if capture else None,
        stderr=subprocess.STDOUT if capture else None,
    )
    if check and result.returncode != 0:
        output = result.stdout or ""
        command = " ".join(args)
        raise PortKitError(f"Command failed ({result.returncode}): {command}\n{output}")
    return result


def load_manifest() -> dict[str, Any]:
    if not MANIFEST_PATH.exists():
        raise PortKitError(f"Missing manifest: {MANIFEST_PATH}")
    return json.loads(MANIFEST_PATH.read_text(encoding="utf-8"))


def find_project_root(start: Path) -> tuple[Path, Path]:
    for candidate in [start, *start.parents]:
        uprojects = sorted(candidate.glob("*.uproject"))
        if len(uprojects) == 1:
            return candidate, uprojects[0]
        if len(uprojects) > 1:
            names = ", ".join(p.name for p in uprojects)
            raise PortKitError(f"Multiple .uproject files found in {candidate}: {names}. Use --project.")
    raise PortKitError("No .uproject found from current directory upward. Use --project.")


def resolve_project(project_arg: str | None) -> tuple[Path, Path]:
    if project_arg:
        project = Path(project_arg).resolve()
        if project.is_dir():
            uprojects = sorted(project.glob("*.uproject"))
            if len(uprojects) != 1:
                raise PortKitError(f"Expected exactly one .uproject under {project}.")
            return project, uprojects[0]
        if project.suffix.lower() != ".uproject" or not project.exists():
            raise PortKitError(f"Invalid project path: {project}")
        return project.parent, project
    return find_project_root(Path.cwd().resolve())


def read_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8-sig"))


def write_json(path: Path, value: dict[str, Any]) -> None:
    path.write_text(json.dumps(value, indent="\t", ensure_ascii=False) + "\n", encoding="utf-8")


def get_project_name(uproject: Path) -> str:
    data = read_json(uproject)
    modules = data.get("Modules") or []
    for module in modules:
        name = str(module.get("Name", ""))
        if module.get("Type") == "Editor" and name.endswith("Editor"):
            return name[:-6]
    return uproject.stem


def candidate_engine_roots(uproject: Path, explicit: str | None) -> list[Path]:
    candidates: list[Path] = []
    if explicit:
        candidates.append(Path(explicit))

    for key in ("UE_ROOT", "UNREAL_ENGINE_ROOT"):
        value = os.environ.get(key)
        if value:
            candidates.append(Path(value))

    try:
        association = str(read_json(uproject).get("EngineAssociation", "")).strip()
    except Exception:
        association = ""
    if association:
        normalized = association if association.startswith("UE_") else f"UE_{association}"
        candidates.extend(
            [
                Path("Q:/DevTools/Unreal Engine") / normalized,
                Path("C:/Program Files/Epic Games") / normalized,
            ]
        )

    candidates.extend(
        [
            Path("Q:/DevTools/Unreal Engine/UE_5.7"),
            Path("C:/Program Files/Epic Games/UE_5.7"),
        ]
    )
    return candidates


def find_engine_root(uproject: Path, explicit: str | None) -> Path:
    for root in candidate_engine_roots(uproject, explicit):
        root = root.expanduser().resolve()
        if (root / "Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe").exists():
            return root
    raise PortKitError("UE 5.7 root not found. Set UE_ROOT or pass --engine-root.")


def clean_tree(path: Path) -> None:
    if path.exists():
        def retry_writeable(function: Any, failed_path: str, _: Any) -> None:
            os.chmod(failed_path, stat.S_IWRITE)
            function(failed_path)

        try:
            shutil.rmtree(path, onexc=retry_writeable)
        except TypeError:
            shutil.rmtree(path, onerror=retry_writeable)


def copy_tree_filtered(src: Path, dst: Path, ignore_patterns: list[str]) -> None:
    if not src.exists():
        raise PortKitError(f"Missing source path: {src}")
    if dst.exists():
        shutil.rmtree(dst)

    def ignore(directory: str, names: list[str]) -> set[str]:
        rel_dir = Path(directory).relative_to(src) if Path(directory) != src else Path()
        ignored: set[str] = set()
        for name in names:
            rel = (rel_dir / name).as_posix()
            for pattern in ignore_patterns:
                if fnmatch.fnmatch(name, pattern) or fnmatch.fnmatch(rel, pattern):
                    ignored.add(name)
                    break
        return ignored

    shutil.copytree(src, dst, ignore=ignore)


def ensure_sparse_source(manifest: dict[str, Any], ref_override: str | None = None) -> Path:
    source_cfg = manifest["source"]
    repo = source_cfg["repo"]
    ref = ref_override or source_cfg["ref"]
    source_dir = KIT_DIR / "cache" / "ue58-source"
    sparse_paths = {f"/{plugin['source']}" for plugin in manifest["plugins"]}
    for plugin in manifest.get("generated_plugins", []):
        for file_mapping in plugin.get("source_files", []):
            sparse_paths.add(f"/{file_mapping['source']}")
    sparse_paths = sorted(sparse_paths)
    sparse_paths.append("/Engine/Build/Build.version")

    if not (source_dir / ".git").exists():
        clean_tree(source_dir)
        source_dir.mkdir(parents=True, exist_ok=True)
        log(f"Fetching UE 5.8 source sparsely into {source_dir}")
        run(["git", "init"], cwd=source_dir)
        run(["git", "remote", "add", "origin", repo], cwd=source_dir)
        run(["git", "sparse-checkout", "init", "--no-cone"], cwd=source_dir)

    run(["git", "sparse-checkout", "set", "--no-cone", *sparse_paths], cwd=source_dir)
    run(["git", "fetch", "--depth=1", "--filter=tree:0", "origin", ref], cwd=source_dir)
    run(["git", "checkout", "--force", "FETCH_HEAD"], cwd=source_dir)

    build_version = source_dir / "Engine/Build/Build.version"
    if build_version.exists():
        version = read_json(build_version)
        expected = source_cfg.get("expected_build", {})
        for key, expected_value in expected.items():
            if version.get(key) != expected_value:
                raise PortKitError(
                    f"UE source mismatch for {key}: got {version.get(key)!r}, expected {expected_value!r}"
                )
    return source_dir


def update_uproject_plugins(uproject: Path, plugin_names: list[str]) -> None:
    data = read_json(uproject)
    entries = data.setdefault("Plugins", [])
    requested = set(plugin_names)
    normalized: list[Any] = []
    by_name: dict[str, dict[str, Any]] = {}

    for entry in entries:
        if not isinstance(entry, dict):
            normalized.append(entry)
            continue

        name = str(entry.get("Name", ""))
        if not name:
            normalized.append(entry)
            continue

        existing = by_name.get(name)
        if existing:
            if name in requested:
                existing.update(entry)
                existing["Enabled"] = True
            continue

        if name in requested:
            entry["Enabled"] = True
        by_name[name] = entry
        normalized.append(entry)

    for name in plugin_names:
        if name not in by_name:
            normalized.append({"Name": name, "Enabled": True, "TargetAllowList": ["Editor"]})

    data["Plugins"] = normalized
    write_json(uproject, data)


def apply_patches(project_root: Path, manifest: dict[str, Any]) -> None:
    for patch_name in manifest.get("patches", []):
        patch_path = KIT_DIR / "patches" / patch_name
        if not patch_path.exists():
            log(f"Skipping missing patch: {patch_name}")
            continue
        log(f"Applying patch: {patch_name}")
        run(["git", "apply", "--binary", "--3way", "--whitespace=nowarn", str(patch_path)], cwd=project_root)


def get_local_plugins(manifest: dict[str, Any]) -> list[dict[str, Any]]:
    return list(manifest.get("local_plugins", manifest.get("owned_plugins", [])))


def get_generated_plugins(manifest: dict[str, Any]) -> list[dict[str, Any]]:
    return list(manifest.get("generated_plugins", []))


def write_generated_json_utilities_editor(dst: Path) -> None:
    uplugin = {
        "FileVersion": 3,
        "Version": 1,
        "VersionName": "1.0",
        "FriendlyName": "Json Utilities Editor",
        "Description": "Generated UE 5.8 JsonUtilitiesEditor compatibility module for the MCP UE 5.7 port.",
        "Category": "Editor",
        "EditorOnly": True,
        "EnabledByDefault": False,
        "CanContainContent": False,
        "Installed": False,
        "Modules": [
            {
                "Name": "JsonUtilitiesEditor",
                "Type": "Editor",
                "LoadingPhase": "Default",
                "TargetAllowList": ["Editor"],
            }
        ],
    }
    write_json(dst / "JsonUtilitiesEditor.uplugin", uplugin)

    module_dir = dst / "Source" / "JsonUtilitiesEditor"
    module_dir.mkdir(parents=True, exist_ok=True)
    (module_dir / "JsonUtilitiesEditor.Build.cs").write_text(
        """using UnrealBuildTool;

public class JsonUtilitiesEditor : ModuleRules
{
    public JsonUtilitiesEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "Slate",
                "SlateCore",
                "Json",
                "JsonUtilities",
                "BlueprintGraph",
                "AssetTools",
            }
        );

        PrivateIncludePaths.Add(System.IO.Path.Combine(GetModuleDirectory("JsonUtilities"), "Private"));
    }
}
""",
        encoding="utf-8",
    )

    private_dir = module_dir / "Private"
    private_dir.mkdir(parents=True, exist_ok=True)
    (private_dir / "JsonUtilitiesEditorModule.cpp").write_text(
        """#include \"Modules/ModuleManager.h\"

IMPLEMENT_MODULE(FDefaultModuleImpl, JsonUtilitiesEditor)
""",
        encoding="utf-8",
    )


def generate_plugin_from_source(source_root: Path, plugin: dict[str, Any], dst: Path) -> None:
    clean_tree(dst)
    dst.mkdir(parents=True, exist_ok=True)

    if plugin["target"] == "JsonUtilitiesEditor":
        write_generated_json_utilities_editor(dst)
    else:
        raise PortKitError(f"Unsupported generated plugin: {plugin['name']}")

    for file_mapping in plugin.get("source_files", []):
        src = source_root / file_mapping["source"]
        target = dst / file_mapping["target"]
        if not src.exists():
            raise PortKitError(f"Missing generated plugin source file: {src}")
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, target)


def build_project(project_root: Path, uproject: Path, engine_root: Path) -> None:
    project_name = get_project_name(uproject)
    target = f"{project_name}Editor"
    ubt = engine_root / "Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe"
    if not ubt.exists():
        raise PortKitError(f"Missing UBT: {ubt}")
    log(f"Building {target}")
    run([str(ubt), f"-Target={target} Win64 Development", f"-Project={uproject}"], cwd=project_root)


def run_mcp_probe(project_root: Path, uproject: Path, engine_root: Path, manifest: dict[str, Any]) -> None:
    editor = engine_root / "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
    if not editor.exists():
        raise PortKitError(f"Missing UnrealEditor-Cmd: {editor}")

    expected = manifest.get("expected_toolsets", {})
    reports = KIT_DIR / "reports"
    reports.mkdir(parents=True, exist_ok=True)
    report_path = reports / "mcp_probe.json"

    script = f"""
import json
import unreal

expected = {json.dumps(expected)}
report = {{"status": "pass", "toolsets": {{}}, "errors": []}}
try:
    if not unreal.ToolsetRegistry.is_available():
        raise RuntimeError("ToolsetRegistry is not available")
    schemas = json.loads(unreal.ToolsetRegistry.get_all_toolset_json_schemas())
    if not isinstance(schemas, list):
        raise RuntimeError("Toolset schema root is not a list")
    for schema in schemas:
        name = str(schema.get("name", ""))
        tools = schema.get("tools", []) or []
        report["toolsets"][name] = len(tools)
    for name, count in expected.items():
        actual = report["toolsets"].get(name)
        if actual != count:
            report["errors"].append(f"{{name}} expected {{count}}, got {{actual}}")
    if report["errors"]:
        report["status"] = "fail"
except Exception as exc:
    report["status"] = "fail"
    report["errors"].append(str(exc))
with open(r"{report_path}", "w", encoding="utf-8") as handle:
    json.dump(report, handle, indent=2)
if report["status"] != "pass":
    raise RuntimeError(report["errors"])
"""
    temp_dir = KIT_DIR / "temp"
    temp_dir.mkdir(parents=True, exist_ok=True)
    probe = temp_dir / "mcp_probe.py"
    probe.write_text(script, encoding="utf-8")
    log("Running MCP probe")
    run([str(editor), str(uproject), "-run=pythonscript", f"-script={probe}", "-unattended", "-nop4"], cwd=project_root)


def install(args: argparse.Namespace) -> None:
    manifest = load_manifest()
    project_root, uproject = resolve_project(args.project)
    engine_root = find_engine_root(uproject, args.engine_root)
    source_root = ensure_sparse_source(manifest, args.ue58_ref)

    plugins_dir = project_root / "Plugins"
    plugins_dir.mkdir(exist_ok=True)
    ignore_patterns = manifest["ignore_patterns"]
    for plugin in manifest["plugins"]:
        src = source_root / plugin["source"]
        dst = plugins_dir / plugin["target"]
        log(f"Importing {plugin['name']}")
        copy_tree_filtered(src, dst, ignore_patterns)
    for plugin in get_generated_plugins(manifest):
        dst = plugins_dir / plugin["target"]
        log(f"Generating {plugin['name']} from licensed UE source")
        generate_plugin_from_source(source_root, plugin, dst)
    for plugin in get_local_plugins(manifest):
        src = KIT_DIR / "owned" / plugin["source"]
        dst = plugins_dir / plugin["target"]
        log(f"Installing local plugin {plugin['name']}")
        copy_tree_filtered(src, dst, ignore_patterns)

    apply_patches(project_root, manifest)
    enabled_plugins = [plugin["target"] for plugin in manifest["plugins"] if plugin.get("enable", True)]
    enabled_plugins.extend(plugin["target"] for plugin in get_generated_plugins(manifest) if plugin.get("enable", True))
    enabled_plugins.extend(plugin["target"] for plugin in get_local_plugins(manifest) if plugin.get("enable", True))
    update_uproject_plugins(uproject, enabled_plugins)
    build_project(project_root, uproject, engine_root)
    run_mcp_probe(project_root, uproject, engine_root, manifest)
    clean_tree(KIT_DIR / "temp")
    log("Install completed")


def create_patch(args: argparse.Namespace) -> None:
    manifest = load_manifest()
    project_root, _ = resolve_project(args.project)
    source_root = Path(args.ue58_source).resolve() if args.ue58_source else ensure_sparse_source(manifest, args.ue58_ref)
    patches_dir = KIT_DIR / "patches"
    patches_dir.mkdir(exist_ok=True)

    temp_repo = KIT_DIR / "temp" / "diffrepo"
    clean_tree(KIT_DIR / "temp")
    temp_repo.mkdir(parents=True)

    try:
        for plugin in manifest["plugins"]:
            copy_tree_filtered(source_root / plugin["source"], temp_repo / "Plugins" / plugin["target"], manifest["ignore_patterns"])
        for plugin in get_generated_plugins(manifest):
            generate_plugin_from_source(source_root, plugin, temp_repo / "Plugins" / plugin["target"])

        run(["git", "init"], cwd=temp_repo)
        run(["git", "add", "-A", "Plugins"], cwd=temp_repo)
        run(
            [
                "git",
                "-c",
                "user.name=MCP PortKit",
                "-c",
                "user.email=mcp-portkit@example.invalid",
                "commit",
                "-m",
                "baseline",
            ],
            cwd=temp_repo,
        )

        clean_tree(temp_repo / "Plugins")
        (temp_repo / "Plugins").mkdir(parents=True)
        for plugin in manifest["plugins"]:
            copy_tree_filtered(project_root / "Plugins" / plugin["target"], temp_repo / "Plugins" / plugin["target"], manifest["ignore_patterns"])
        for plugin in get_generated_plugins(manifest):
            copy_tree_filtered(project_root / "Plugins" / plugin["target"], temp_repo / "Plugins" / plugin["target"], manifest["ignore_patterns"])

        output = subprocess.run(
            ["git", "-c", "core.autocrlf=false", "diff", "--binary", "--no-ext-diff", "HEAD", "--", "Plugins"],
            cwd=str(temp_repo),
            check=False,
            text=True,
            encoding="utf-8",
            errors="replace",
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if output.returncode not in (0, 1):
            raise PortKitError(f"git diff failed ({output.returncode}):\n{output.stderr}")
        patch_text = output.stdout or ""
        patch_path = patches_dir / manifest["generated_patch_name"]
        patch_path.write_text(patch_text, encoding="utf-8")
        log(f"Wrote patch: {patch_path}")
    finally:
        clean_tree(KIT_DIR / "temp")


def clean(_: argparse.Namespace) -> None:
    for name in ("cache", "temp", "reports"):
        clean_tree(KIT_DIR / name)
    log("Local PortKit state cleaned")


def license_audit(_: argparse.Namespace) -> None:
    """Detect files that should not live in tracked local support plugins."""
    manifest = load_manifest()
    markers = (
        "Copyright Epic Games",
        "Epic Games, Inc.",
        "All Rights Reserved.",
    )
    findings: list[dict[str, Any]] = []
    for plugin in get_local_plugins(manifest):
        root = KIT_DIR / "owned" / plugin["source"]
        if not root.exists():
            findings.append({"plugin": plugin["name"], "path": str(root), "reason": "missing local support plugin"})
            continue
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix.lower() not in {".h", ".hpp", ".cpp", ".cs", ".uplugin"}:
                continue
            try:
                text = path.read_text(encoding="utf-8", errors="ignore")
            except OSError as exc:
                findings.append({"plugin": plugin["name"], "path": str(path), "reason": str(exc)})
                continue
            for marker in markers:
                if marker in text:
                    findings.append(
                        {
                            "plugin": plugin["name"],
                            "path": str(path.relative_to(KIT_DIR)),
                            "reason": f"contains marker: {marker}",
                        }
                    )
                    break

    reports = KIT_DIR / "reports"
    reports.mkdir(parents=True, exist_ok=True)
    report_path = reports / "license_audit.json"
    report_path.write_text(json.dumps({"findings": findings}, indent=2), encoding="utf-8")

    if findings:
        for finding in findings:
            log(f"LICENSE BLOCKER: {finding['path']} ({finding['reason']})")
        raise PortKitError(f"License audit failed. See {report_path}")

    log(f"License audit passed. Report: {report_path}")


def doctor(args: argparse.Namespace) -> None:
    manifest = load_manifest()
    project_root, uproject = resolve_project(args.project)
    engine_root = find_engine_root(uproject, args.engine_root)
    git_version = run(["git", "--version"], capture=True).stdout.strip()
    log(f"Project: {uproject}")
    log(f"Engine: {engine_root}")
    log(f"Git: {git_version}")
    log(f"UE 5.8 ref: {args.ue58_ref or manifest['source']['ref']}")


def main() -> int:
    parser = argparse.ArgumentParser(description="UE 5.8 -> UE 5.7 MCP PortKit")
    parser.add_argument("--project", help="Optional .uproject or project root override")
    parser.add_argument("--engine-root", help="Optional UE 5.7 root override")
    parser.add_argument("--ue58-ref", help="Optional UE 5.8 source ref override")

    subparsers = parser.add_subparsers(dest="command", required=True)

    def add_common_options(command_parser: argparse.ArgumentParser) -> None:
        command_parser.add_argument("--project", help=argparse.SUPPRESS)
        command_parser.add_argument("--engine-root", help=argparse.SUPPRESS)
        command_parser.add_argument("--ue58-ref", help=argparse.SUPPRESS)

    install_parser = subparsers.add_parser("install")
    add_common_options(install_parser)
    create = subparsers.add_parser("create-patch")
    add_common_options(create)
    create.add_argument("--ue58-source", help="Optional existing UE 5.8 source checkout")
    clean_parser = subparsers.add_parser("clean")
    add_common_options(clean_parser)
    doctor_parser = subparsers.add_parser("doctor")
    add_common_options(doctor_parser)
    audit_parser = subparsers.add_parser("license-audit")
    add_common_options(audit_parser)

    args = parser.parse_args()
    try:
        if args.command == "install":
            install(args)
        elif args.command == "create-patch":
            create_patch(args)
        elif args.command == "clean":
            clean(args)
        elif args.command == "doctor":
            doctor(args)
        elif args.command == "license-audit":
            license_audit(args)
        return 0
    except PortKitError as exc:
        print(f"[MCPPortKit] ERROR: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
