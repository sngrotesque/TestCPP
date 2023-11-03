import subprocess
import sys

def run(cmd :str):
    return subprocess.call(cmd, shell=True)

if len(sys.argv) < 2:
    exit(f'python {sys.argv[0]} [input file]')

ProgramName  = 'g++'
InputFile    = sys.argv[1]
LibraryFiles = ' '.join(['lib/crypto.cpp', 'lib/baselib.cpp', 'lib/network.cpp'])
GppArgs      = ' '.join(['-O3', '-lws2_32'])
OutputFile   = 'main.exe'

if not run(f'{ProgramName} {InputFile} {LibraryFiles} {GppArgs} -o {OutputFile}'):
    run(f'.\{OutputFile}')
