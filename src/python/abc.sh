#!/bin/sh
#
# Setup the ABC/Py environment and run the ABC/Py executable
# (ABC/Py stands for ABC with embedded Python)
#
# ABC/Py expects the following directory structure
#
# abc_root/
#   bin/
#     abc - this script
#     abc_exe - the ABC executable
#   lib/
#     pythonXX.zip - The Python standard library, where XX is the Python version (26 for Python 2.6, etc.)
#     *.so - Python extensions
#             

# usage: abspath <dir>
# get the absolute path of <dir>
abspath()
{
    cwd="$(pwd)"
    cd "$1"
    echo "$(pwd)"
    cd "${cwd}"
}

self=$0

self_dir="$(dirname "${self}")"
self_dir="$(abspath "${self_dir}")"

abc_root="$(dirname "${self_dir}")"

abc_exe="${abc_root}/bin/abc_exe"

PYTHONHOME="${abc_root}"
export PYTHONHOME

PYTHONPATH="${abc_root}/lib/python_library.zip":"${abc_root}/lib":"${PYTHONPATH}"
export PYTHONPATH

exec "${abc_exe}" "$@"
