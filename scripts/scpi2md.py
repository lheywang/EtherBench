#!/usr/bin/env python3
"""
EtherBench SCPI & Shell Reference Manual Generator
Parses structural commands from the firmware layer and merges them with
localized documentation TOML tables. Implements architectural grouping to
isolate IEEE-488.2 core commands, POSIX filesystem operations, and low-level
shell hooks into dedicated appendices, preventing document clutter.
"""

import os
import pathlib
import tomllib

# --- Architectural Paths ---
COMMAND_PATH = "EtherBenchFirmware/tasks/parser/config/commands.toml"
DOC_PATH = "data/commands"
OUTPUT_PATH = "docs/programming/generated/scpi_reference.md"

# --- Document UI Badges (HTML Injection for WeasyPrint Layouts) ---
DURATION_BADGES = {
    "very fast": '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Very fast (&lt;10µs)</span>',
    "fast": '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Fast (&lt;100µs)</span>',
    "normal": '<span style="background-color: #f5f5f5; color: #424242; border: 1px solid #e0e0e0; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Normal</span>',
    "slow": '<span style="background-color: #fff3e0; color: #ef6c00; border: 1px solid #ffcc80; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Slow</span>',
    "very slow": '<span style="background-color: #ffebee; color: #c62828; border: 1px solid #ffcdd2; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Very slow</span>',
}

ALERT_STYLES = {
    "warning": {"bg": "#ffebee", "border": "#c62828", "title": "WARNING"},
    "caution": {"bg": "#fff3e0", "border": "#ef6c00", "title": "CAUTION"},
    "important": {"bg": "#e8eaf6", "border": "#3f51b5", "title": "IMPORTANT"},
    "note": {"bg": "#f5f5f5", "border": "#616161", "title": "NOTE"},
    "tip": {"bg": "#e8f5e9", "border": "#2e7d32", "title": "TIP"},
}

# --- Human-Readable Section Mapping ---
CATEGORY_TITLES = {
    "programmation": "Target Programming Interface",
    "analog": "Analog Subsystem Metrology (ADC / DAC)",
    "hardware": "Hardware Input Outputs",
    "scan": "Bus scanning",
    "file": "IEEE-488.2 File commands",
    "ieee_core": "IEEE-488.2 Standard Core Commands",
    "logger": "Logging controls",
    "sequences": "Sequencing",
    "extensions": "Extensions configuration",
    "actions": "Automated actions controls",
    "unix_cli": "POSIX Filesystem & Shell Commands",
    "shell_generic": "Low-Level System Shell Utilities",
}

# --- Static Filter List for Root-Level POSIX Commands ---
UNIX_STANDARD_COMMANDS = {
    "cat",
    "cd",
    "clear",
    "cp",
    "file",
    "ls",
    "mkdir",
    "mv",
    "pwd",
    "rm",
    "rmdir",
}


def get_flat_keys(data: dict, prefix: str = "") -> set:
    """Recursively crawls the nested TOML structure to extract flattened

    sub-system dot-notation keys (e.g., 'programmation.connect').
    """
    flat_keys = set()
    for key, value in data.items():
        current_key = f"{prefix}.{key}" if prefix else key

        # If it's a leaf node containing a firmware handler, stop recursion
        if (
            isinstance(value, dict)
            and "handler_scpi_set" not in value
            and "handler_scpi_query" not in value
            and "handler_shell" not in value
            and "shell" not in value
            and "shell_" not in value
        ):
            flat_keys.update(get_flat_keys(value, current_key))
        else:
            flat_keys.add(current_key)
    return flat_keys


def get_nested_command_config(master_dict: dict, flat_key: str) -> dict:
    """Safe navigation helper to retrieve configuration dictionaries

    from nested structures using a flattened string key.
    """
    parts = flat_key.split(".")
    current = master_dict
    for part in parts:
        if isinstance(current, dict) and part in current:
            current = current[part]
        else:
            return {}
    return current


def generate_doc(command_name: str, cmd_data: dict, cmd_cmd: dict) -> list:
    """Compiles local metadata tables and system traits into a clean,

    non-breaking Markdown block optimized for Paged Media output.
    """
    requirements = ["description", "args", "returns"]
    for requirement in requirements:
        if requirement not in cmd_data.keys():
            print(
                f"[WARNING] Command '{command_name}' skipped: missing metadata '{requirement}'."
            )
            return []

    lines = ['<div class="scpi-command-block" markdown="1">\n\n']

    # Normalize name representation for the sub-header
    display_name = (
        command_name.replace("ieee_core.", "*")
        if command_name.startswith("ieee_core.")
        else command_name.lower()
    )
    lines.append(f"#### {display_name}")
    lines.append("")

    # Format syntax routing protocols
    if "handler_scpi_set" in cmd_cmd:
        scpi_syntax = command_name.upper().replace(".", ":")
        if scpi_syntax.startswith("IEEE_CORE:"):
            scpi_syntax = scpi_syntax.replace("IEEE_CORE:", "*")
        lines.append(f"- SCPI Syntax: `{scpi_syntax}`")
    if "handler_scpi_query" in cmd_cmd:
        scpi_syntax = command_name.upper().replace(".", ":")
        if scpi_syntax.startswith("IEEE_CORE:"):
            scpi_syntax = scpi_syntax.replace("IEEE_CORE:", "*")
        lines.append(f"- SCPI Syntax: `{scpi_syntax}?`")

    if "shell_" in cmd_cmd:
        lines.append(f"- Shell Hook: `{cmd_cmd['shell_']}`")
    elif "shell" in cmd_cmd:
        lines.append(f"- Shell Hook: `{cmd_cmd['shell']}`")
    lines.append("")

    # Performance and Determinism traits
    if "duration" in cmd_data:
        lines.append(DURATION_BADGES[cmd_data["duration"]])
    if "blocking" in cmd_data:
        if cmd_data["blocking"] in ["Y", "yes", True]:
            lines.append(
                '<span style="background-color: #ffebee; color: #c62828; border: 1px solid #ffcdd2; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Blocking</span>'
            )
        else:
            lines.append(
                '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">Non-Blocking</span>'
            )
    lines.append("")

    # Core description block
    lines.append(cmd_data["description"])
    lines.append("")

    # Parameter Verification Tables
    lines.append("##### Arguments / Returns")
    lines.append("")
    if cmd_data["args"]:
        lines.append("| Argument | Description |")
        lines.append("| :--- | :--- |")
        for arg_name, arg_description in cmd_data["args"].items():
            lines.append(f"| `{arg_name}` | {arg_description} |")
    else:
        lines.append("*This command does not take any arguments.*")
    lines.append("")

    if cmd_data["returns"]:
        lines.append("| Returns | Description |")
        lines.append("| :--- | :--- |")
        for arg_name, arg_description in cmd_data["returns"].items():
            lines.append(f"| `{arg_name}` | {arg_description} |")
    else:
        lines.append("*This command does not return any parameters.*")
    lines.append("")

    # Optional Hardware Plots / Diagrams
    add_header = True
    if "image" in cmd_data:
        lines.append("##### Additional Information")
        lines.append("")
        add_header = False
        lines.append(f"![{cmd_data['image']['name']}]({cmd_data['image']['path']})")

    # Optional Configuration Matrix / Registers Tables
    if "table" in cmd_data:
        if add_header:
            lines.append("##### Additional Information")
            lines.append("")
            add_header = False
        lines.append(cmd_data["table"]["name"])
        lines.append("")
        lines.append(f"| {'|'.join(cmd_data['table']['array'][0])} |")
        lines.append(f"| {':-- |'*len(cmd_data['table']['array'][0])}")
        for array_line in cmd_data["table"]["array"][1:]:
            lines.append(f"| {'|'.join(array_line)} |")
    lines.append("")

    # Industrial Admonition / Callout Blocks
    alert_types = ["note", "tip", "important", "warning", "caution"]
    for alert in alert_types:
        if alert in cmd_data:
            if add_header:
                lines.append("##### Additional Information")
                lines.append("")
                add_header = False

            style = ALERT_STYLES[alert]
            lines.append(
                f'<div style="background-color: {style["bg"]}; border-left: 4px solid {style["border"]}; padding: 12px; margin: 15px 0; border-radius: 4px;">'
            )
            lines.append(
                f'  <strong style="color: {style["border"]}; display: block; margin-bottom: 6px;">{style["title"]}</strong>'
            )
            for line in cmd_data[alert].split("\n"):
                lines.append(f"  {line}<br>")
            lines.append("</div>\n")
            lines.append("")

    # Bus Exchange Examples
    if "ex_command" in cmd_data and "ex_return" in cmd_data:
        lines.append("##### Bus Transfer Examples")
        lines.append("")
        if "ex_comment" in cmd_data:
            lines.append(cmd_data["ex_comment"])
        lines.append("Command string:")
        lines.append(f"`{cmd_data['ex_command']}`")
        lines.append("")
        lines.append("Device transmission:")
        lines.append(f"`{cmd_data['ex_return']}`")
        lines.append("")

    if "epilog" in cmd_data:
        lines.append(cmd_data["epilog"])

    lines.append("</div>\n\n---")
    lines.append("")
    lines.append("")
    return lines


if __name__ == "__main__":
    # 1. Load firmware definition maps
    with open(COMMAND_PATH, "rb") as f:
        commands = tomllib.load(f)

    # 2. Scrape documentation descriptors
    nested_docs = dict()
    doc_files = pathlib.Path(DOC_PATH).glob("**.toml")
    for doc_file in doc_files:
        with open(doc_file, "rb") as f:
            nested_docs.update(tomllib.load(f))

    # --- NOUVELLE LOGIQUE D'APLATISSEMENT DE LA DOC ---
    # On utilise une logique similaire à get_flat_keys mais adaptée aux structures de doc
    def flatten_doc_keys(data, prefix=""):
        flat_doc = {}
        for key, value in data.items():
            current_key = f"{prefix}.{key}" if prefix else key

            # Si le dictionnaire contient 'description', c'est que c'est une feuille de doc
            if isinstance(value, dict) and "description" not in value:
                flat_doc.update(flatten_doc_keys(value, current_key))
            else:
                flat_doc[current_key] = value
        return flat_doc

    docs = flatten_doc_keys(nested_docs)
    # --------------------------------------------------

    # Perform static validation check for missing descriptors
    # (Le reste de ton script reste strictement identique)
    flat_commands_list = list(get_flat_keys(commands))
    diffs = set(flat_commands_list) - set(docs.keys())
    if len(diffs) > 0:
        print("[MISMATCH] Found undocumented firmware commands :")
        for diff in sorted(diffs):
            print(f"  - {diff}")

    # --- ROUTING FILTER MATRIX ---
    flat_commands_list = list(get_flat_keys(commands))
    categorical_commands = {}

    for command in flat_commands_list:
        parts = command.split(".")
        base_prefix = parts[0].lower()

        # Filtering Layer: Isolate infrastructure utilities from hardware features
        if base_prefix.startswith("*") or base_prefix == "ieee" or "ieee_core" in parts:
            category = "ieee_core"
        elif base_prefix in UNIX_STANDARD_COMMANDS:
            category = "unix_cli"
        elif base_prefix in ["system", "core", "shell", "debug"]:
            category = "shell_generic"
        else:
            category = base_prefix

        if category not in categorical_commands:
            categorical_commands[category] = []
        categorical_commands[category].append(command)

    # Sort categories alphabetically
    raw_categories = sorted(list(categorical_commands.keys()))

    # Enforce priority ordering: Appendices are systematically pushed to the bottom
    appendices_order = ["ieee_core", "unix_cli", "shell_generic"]
    for app_category in appendices_order:
        if app_category in raw_categories:
            raw_categories.remove(app_category)
            raw_categories.append(app_category)

    # --- MARKDOWN COMPILATION ---
    os.makedirs(os.path.dirname(OUTPUT_PATH), exist_ok=True)
    with open(OUTPUT_PATH, "w+", encoding="utf-8") as f:
        f.write("# Programming Reference Manual\n\n")
        f.write(
            "Complete technical API documentation for the EtherBench platform. "
            "Includes SCPI sub-systems syntax and direct low-level serial shell interactions.\n\n"
        )

        # Inject standard style safety guards for WeasyPrint Paged Media
        f.write("""<style>
.scpi-command-block {
    page-break-before: avoid !important;
    break-inside: avoid;
    display: block;
    margin-bottom: 20px;
}
.scpi-command-block:first-of-type {
    page-break-before: avoid !important;
    break-before: avoid !important;
}
</style>\n\n---\n\n""")

        for category in raw_categories:
            category_title = CATEGORY_TITLES.get(
                category, f"{category.capitalize()} Sub-System"
            )

            # Generate Level 2 Header - Mandatory hook for with-pdf TOC compilation
            f.write(f"## {category_title}\n\n")

            cmds_in_cat = categorical_commands[category]
            cmds_in_cat.sort(key=str.lower)

            for command in cmds_in_cat:
                doc = docs.get(command, {})
                cmd = get_nested_command_config(commands, command)
                cmd_lines = generate_doc(command, doc, cmd)
                for line in cmd_lines:
                    f.write(f"{line}\n")

    print(f"[SUCCESS] Exported structured documentation to: {OUTPUT_PATH}")
