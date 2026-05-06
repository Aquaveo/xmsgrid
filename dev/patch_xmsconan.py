"""Patch the generated xms_conan2_file.py to fix python_version propagation.

In Conan 2, ``self.options[dep_name]`` returns the (initially empty) consumer-
side override proxy, not the dependency's actual options. The ``if 'python_version'
in self.options[dep_name]:`` guard in xmsconan 2.12.1 therefore always evaluates
False, and the xmscore.python_version override from the consumer never fires —
so xmsgrid built for Python 3.10 ends up linking xmscore's Python 3.13 binary
(LNK1104: cannot open file 'python313.lib').

Replace the dead guard with a try/except so the assignment actually runs. Drop
this workaround once xmsconan upstream is fixed.
"""
import pathlib
import sys

OLD = """            if 'python_version' in self.options[dep_name]:
                self.options[dep_name].python_version = dep_opts.get(
                    'python_version', self.options.python_version
                )"""

NEW = """            try:
                self.options[dep_name].python_version = dep_opts.get(
                    'python_version', self.options.python_version
                )
            except Exception:
                pass"""

path = pathlib.Path("xms_conan2_file.py")
src = path.read_text()
if NEW in src:
    print("xms_conan2_file.py already patched")
    sys.exit(0)
if OLD not in src:
    print("xms_conan2_file.py format changed; remove this workaround", file=sys.stderr)
    sys.exit(1)
path.write_text(src.replace(OLD, NEW))
print("patched xms_conan2_file.py")
