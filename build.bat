@echo off

set PROGRAM_NAME="g++"
set INPUT_NAME="main.cpp"

set LIBFILE1="lib/crypto.cpp"
set LIBFILE2="lib/baselib.cpp"
set LIBFILE3="lib/network.cpp"

set GPP_ARGS="-O3"
set OUTPUT_NAME="main.exe"

%PROGRAM_NAME% %INPUT_NAME% %LIBFILE1% %LIBFILE2% %LIBFILE3% %GPP_ARGS% -o %OUTPUT_NAME% && %OUTPUT_NAME%
