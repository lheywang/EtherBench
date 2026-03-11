#!/usr/bin/env python3
import sys
import argparse
import itertools
import tomllib


def get_scpi_forms(word):
    """
    Ensure we're getting a nice SCPI formatted command
    """
    word = word.lower()

    # Common questions
    if word.startswith("*"):
        return [word]

    # Rule for the short form
    if len(word) <= 4:
        short_form = word
    else:
        if word[3] in "aeiou":
            short_form = word[:3]
        else:
            short_form = word[:4]

    return list(set([short_form, word]))


def generate_scpi_permutations(path_list, is_query):
    """
    Generate all variations of a single command form (long, short, and mix (which are not in spec, but make life easier))
    """
    forms_per_part = [get_scpi_forms(p) for p in path_list]
    combinations = itertools.product(*forms_per_part)

    results = []
    for c in combinations:
        cmd_string = ":".join(c)
        if is_query:
            cmd_string += "?"
        results.append(cmd_string)

    return results


def extract_commands(node, current_path, scpi_entries, shell_entries):
    """
    Extract all commands
    """
    if isinstance(node, dict):
        is_leaf = False

        if "handler_scpi_query" in node:
            is_leaf = True
            perms = generate_scpi_permutations(current_path, is_query=True)
            for p in perms:
                scpi_entries[p] = node["handler_scpi_query"]

        if "handler_scpi_set" in node:
            is_leaf = True
            perms = generate_scpi_permutations(current_path, is_query=False)
            for p in perms:
                scpi_entries[p] = node["handler_scpi_set"]

        if "shell" in node and "handler_shell" in node:
            is_leaf = True
            shell_entries[node["shell"]] = node["handler_shell"]

        reserved_keys = [
            "handler_scpi_query",
            "handler_scpi_set",
            "shell",
            "handler_shell",
        ]
        for key, value in node.items():
            if key not in reserved_keys and isinstance(value, dict):
                extract_commands(
                    value, current_path + [key], scpi_entries, shell_entries
                )


def write_gperf_file(filepath, struct_name, header_file, commands_dict):
    with open(filepath, "w") as f:
        f.write("%{\n")
        f.write('#include "commands/gperf.h"\n\n')
        f.write(f'#include "{header_file}"\n\n')
        f.write("%}\n\n")
        f.write(f"struct {struct_name};\n\n")
        f.write("%%\n")
        for cmd, handler in commands_dict.items():
            f.write(f"{cmd}, {handler}\n")
        f.write("%%\n")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", required=True)
    parser.add_argument("--out-scpi", required=True)
    parser.add_argument("--out-shell", required=True)
    args = parser.parse_args()

    with open(args.input, "rb") as f:
        data = tomllib.load(f)

    scpi_entries = {}
    shell_entries = {}

    # Démarrage de la récursion
    for key, value in data.items():
        if isinstance(value, dict):
            extract_commands(value, [key], scpi_entries, shell_entries)

    write_gperf_file(
        args.out_scpi, "scpi_command_entry", "commands/parser_scpi.h", scpi_entries
    )

    write_gperf_file(
        args.out_shell, "shell_command_entry", "commands/parser_shell.h", shell_entries
    )


if __name__ == "__main__":
    main()
