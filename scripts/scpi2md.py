#
# Convert the source EtherBenchFirmware commands into the nicely markdown formatted source
#
import tomllib
import pathlib
import os

COMMAND_PATH = "EtherBenchFirmware/tasks/parser/config/commands.toml"
DOC_PATH = "data/commands"
OUTPUT_PATH = "docs/programming/generated/scpi_reference.md"

DURATION_BADGES = {
    "very fast": '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">⚡ Very fast (&lt;10µs)</span>',
    "fast": '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">🚀 Fast (&lt;100µs)</span>',
    "normal": '<span style="background-color: #f5f5f5; color: #424242; border: 1px solid #e0e0e0; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">⏱️ Normal</span>',
    "slow": '<span style="background-color: #fff3e0; color: #ef6c00; border: 1px solid #ffcc80; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">⚠️ Slow</span>',
    "very slow": '<span style="background-color: #ffebee; color: #c62828; border: 1px solid #ffcdd2; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">🛑 Very slow</span>',
}

ALERT_STYLES = {
    "warning": {"bg": "#ffebee", "border": "#c62828", "title": "⚠️ WARNING"},
    "caution": {"bg": "#fff3e0", "border": "#ef6c00", "title": "⚡ CAUTION"},
    "important": {"bg": "#e8eaf6", "border": "#3f51b5", "title": "💎 IMPORTANT"},
    "note": {"bg": "#f5f5f5", "border": "#616161", "title": "📝 NOTE"},
    "tip": {"bg": "#e8f5e9", "border": "#2e7d32", "title": "💡 TIP"},
}


def get_flat_keys(data, prefix=""):
    flat_keys = set()
    for key, value in data.items():
        # On construit le chemin de la clé actuelle (ex: "file.cd")
        current_key = f"{prefix}.{key}" if prefix else key

        # Si la valeur est un sous-dictionnaire ET qu'elle ne contient pas
        # directement un handler (ce qui signifierait que c'est la commande elle-même),
        # alors on continue de creuser récursivement.
        if (
            isinstance(value, dict)
            and "handler_scpi_set" not in value
            and "handler_scpi_query" not in value
            and "handler_shell" not in value
            and "shell" not in value
        ):
            flat_keys.update(get_flat_keys(value, current_key))
        else:
            # C'est une commande finale, on l'ajoute
            flat_keys.add(current_key)

    return flat_keys


def generate_doc(command_name: str, cmd_data: dict, cmd_cmd: dict) -> list:

    requirements = ["description", "args", "returns"]
    for requirement in requirements:
        if requirement not in cmd_data.keys():
            print(f"WARNING : {command_name} is missing a required key ({requirement})")
            return []

    # Now, generate the doc
    lines = ['<div class="scpi-command-block" markdown="1">\n\n']

    # Add command name
    lines.append(f"## {command_name}")
    lines.append("")

    # Add the calling names (if applicable, and as uppercase with : separating.)
    if "handler_scpi_set" in cmd_cmd or "handler_scpi_query" in cmd_cmd:
        lines.append(f"- SCPI: {command_name.upper().replace(".", ":")}")
    if "shell" in cmd_cmd:
        lines.append(f"- shell: {cmd_cmd["shell"]}")
    lines.append("")

    # Add the performances information:
    if "duration" in cmd_data:
        lines.append(DURATION_BADGES[cmd_data["duration"]])
    if "blocking" in cmd_data:
        if cmd_data["blocking"] in ["Y", "yes", True]:
            lines.append(
                '<span style="background-color: #ffebee; color: #c62828; border: 1px solid #ffcdd2; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">🔒 Blocking</span>'
            )
        else:
            lines.append(
                '<span style="background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7; padding: 2px 6px; border-radius: 4px; font-size: 0.8em; font-weight: bold;">🔓 Non-Blocking</span>'
            )
    lines.append("")

    # Add the description:
    lines.append(cmd_data["description"])
    lines.append("")

    # Add arguments / returns table
    lines.append("### Arguments / Returns")
    lines.append("")
    if cmd_data["args"]:
        lines.append("| Argument | Description |")
        lines.append("| :--- | :--- |")
        for arg_name, arg_description in cmd_data["args"].items():
            lines.append(f"| `{arg_name}` | {arg_description} |")
    else:
        lines.append("*This command does not take any arguments*")
    lines.append("")

    if cmd_data["returns"]:
        lines.append("| Returns | Description |")
        lines.append("| :--- | :--- |")
        for arg_name, arg_description in cmd_data["returns"].items():
            lines.append(f"| `{arg_name}` | {arg_description} |")
    else:
        lines.append("*This command does not return anything*")
    lines.append("")

    # Add optionnal images
    add_header = True
    if "image" in cmd_data:
        lines.append("### Additionnal infos")
        lines.append("")
        add_header = False
        lines.append(f"![{cmd_data["image"]["name"]}]({cmd_data['image']["path"]})")

    # Add an optionnal table
    if "table" in cmd_data:
        if add_header:
            lines.append("### Additionnal infos")
            lines.append("")
            add_header = False
        lines.append(cmd_data["table"]["name"])
        lines.append("")
        lines.append(f"| {"|".join(cmd_data["table"]["array"][0])} |")
        lines.append(f"| {":-- |"*len(cmd_data["table"]["array"][0])}")
        for array_line in cmd_data["table"]["array"][1:]:
            lines.append(f"| {"|".join(array_line)} |")
    lines.append("")

    # Add the remarks:
    alert_types = ["note", "tip", "important", "warning", "caution"]
    for alert in alert_types:
        if alert in cmd_data:
            if add_header:
                lines.append("### Additionnal infos")
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

    if "ex_command" in cmd_data and "ex_return" in cmd_data:
        lines.append("### Examples")
        lines.append("")
        if "ex_comment" in cmd_data:
            lines.append(cmd_data["ex_comment"])

        lines.append("Command :")
        lines.append(f"`{cmd_data["ex_command"]}`")
        lines.append("")
        lines.append("Return :")
        lines.append(f"`{cmd_data["ex_return"]}`")
        lines.append("")

    # Add the epilog
    if "epilog" in cmd_data:
        lines.append(cmd_data["epilog"])

    lines.append("</div>\n\n---")
    lines.append("")
    lines.append("")

    return lines


if __name__ == "__main__":
    # First, load the config (from one submodule).
    commands = dict()
    with open(COMMAND_PATH, "rb") as f:
        commands = tomllib.load(f)

    # Then, load the commands (may be on different folders)
    docs = dict()
    doc_files = pathlib.Path(DOC_PATH).glob("**.toml")
    for doc_file in doc_files:
        with open(doc_file, "rb") as f:
            docs.update(tomllib.load(f))

    # Compute the diff, to check the undocumented commands: (The commands may be nested, the docs are NOT)
    diffs = get_flat_keys(commands) - set(docs)
    if len(diffs) > 0:
        print("Some commands are missing documentation :")
        for diff in diffs:
            print(f"- {diff}")

    # Sorting the commands, to get a cleaner view
    ord_commands = list(get_flat_keys(commands))
    ord_commands.sort(key=str.lower)

    # Generating the doc for each. We're passing the whole ressource and the target element
    lines = []
    for command in ord_commands:
        # fetch elements
        doc = docs.get(command, {})
        cmd = commands.get(command, {})
        lines.extend(generate_doc(command, doc, cmd))

    # Write to file
    os.makedirs(os.path.dirname(OUTPUT_PATH), exist_ok=True)
    with open(OUTPUT_PATH, "w+") as f:
        f.write("# Programming reference:\n")
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
.pdf-admonition {
    background-color: #fff3e0;
    border-left: 4px solid #ef6c00;
    padding: 10px;
    margin: 15px 0;
    border-radius: 4px;
}
.pdf-admonition-title {
    font-weight: bold;
    color: #ef6c00;
    margin-bottom: 5px;
}
</style>

""")
        f.write("---\n\n")
        for line in lines:
            f.write(f"{line}\n")

    print(f"Wrote the file")

# Elements lists:
# Required :
#   description:
#   args : dict
#   returns : dict
#
# Optionnal
#   duration: Timings
#   blocking: Y/N
#   image: Insert an image
#   note:
#   tip:
#   important:
#   warning:
#   caution:
#   ex_command:
#   ex_return:
#   ex_comment:
#   epilog
#   table
