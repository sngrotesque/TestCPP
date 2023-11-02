import subprocess

def run(cmd :str):
    return subprocess.call(cmd, shell=True)

ProgramName  = 'g++'
InputFile    = 'main.cpp'
LibraryFiles = ' '.join(['lib/crypto.cpp', 'lib/baselib.cpp', 'lib/network.cpp'])
GppArgs      = ' '.join(['-O3', '-lws2_32'])
OutputFile   = 'main.exe'

print(run(f'{ProgramName} {InputFile} {LibraryFiles} {GppArgs} -o {OutputFile}'))
print(run(f'.\{OutputFile}'))
