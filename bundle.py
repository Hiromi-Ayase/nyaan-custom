#!/usr/bin/env python3
"""Expand local C++ includes using only the Python standard library."""

import argparse
import hashlib
from pathlib import Path
import re
import sys

INCLUDE = re.compile(r'^\s*#\s*include\s*([<"])([^">]+)[">]')
PRAGMA_ONCE = re.compile(r'^\s*#\s*pragma\s+once\s*(?://.*)?$')


def bundle(source, include_dirs):
    active = set()

    def expand(path):
        path = path.resolve()
        lines = path.read_text(encoding="utf-8").splitlines()
        once = any(PRAGMA_ONCE.fullmatch(line) for line in lines)
        if path in active:
            if once:
                return []
            raise ValueError(f"Cyclic include without #pragma once: {path}")

        active.add(path)
        output = []
        if once:
            # Each occurrence retains its guard, including occurrences inside #if.
            # Skipping an already seen file would break a first include under #if 0.
            identity = str(
                path.relative_to(include_dirs[0])
                if path.is_relative_to(include_dirs[0])
                else path
            )
            guard = "NYAAN_BUNDLED_" + hashlib.sha256(identity.encode()).hexdigest().upper()
            output.extend([f"#ifndef {guard}", f"#define {guard}"])

        for line in lines:
            if PRAGMA_ONCE.fullmatch(line):
                continue
            match = INCLUDE.match(line)
            if match:
                delimiter, name = match.groups()
                directories = ([path.parent] if delimiter == '"' else []) + include_dirs
                included = next(
                    (directory / name for directory in directories if (directory / name).is_file()),
                    None,
                )
                if included is not None:
                    output.extend(expand(included))
                    continue
                if delimiter == '"':
                    raise FileNotFoundError(f"Include not found: {name} (from {path})")
            output.append(line)

        if once:
            output.append(f"#endif  // {guard}")
        active.remove(path)
        return output

    return "\n".join(expand(source)) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("-I", dest="include_dirs", type=Path, action="append", default=[])
    args = parser.parse_args()
    directories = [Path(__file__).resolve().parent, Path.cwd()]
    directories.extend(directory.resolve() for directory in args.include_dirs)
    try:
        result = bundle(args.source, directories)
    except (OSError, ValueError) as error:
        parser.exit(1, f"bundle failed: {error}\n")
    # Match the submission mode of the previous bundler without deleting code.
    sys.stdout.write("#ifndef NDEBUG\n#define NDEBUG\n#endif\n" + result)


if __name__ == "__main__":
    main()
