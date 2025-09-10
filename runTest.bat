@echo off
REM A custom command-line script for testing C++ programs in Windows CMD.

REM USAGE: test.bat <executable_file> <input_file.txt>
REM FIRST PARAM: executable
REM SECOND PARAM: input file - Defaults to test.txt

REM Set the executable name, defaulting to "a.exe" if not provided
if "%1"=="" (
    echo Error: No executable file specified.
    echo Usage: %0 ^<executable_file^> ^<optional_input_file.txt^>
    exit /b 1
) else (
    set "EXECUTABLE=%1"
)

REM Set the input file name
if "%2"=="" (
    set "INPUT_NAME=test.txt"
) else (
    set "INPUT_NAME=%2"
)

REM Check if executable file exists
if not exist %EXECUTABLE% (
    echo Error: Executable file not found
    exit /b 1
)

echo %INPUT_NAME%
set "INPUT_FILE=text_in/%INPUT_NAME%"
echo %INPUT_FILE%

REM Create a output file name
set OUTPUT_FILE=%INPUT_FILE:.txt=_output.txt%
set OUTPUT_FILE=%OUTPUT_FILE:in=out%

echo %OUTPUT_FILE%

REM Check if input file exists
if not exist %INPUT_FILE% (
    echo Error: Input file not found
    if "%2"=="" (
        echo Default value for input file is 'test.txt'
    )
    exit /b 1
)


echo --- Running test with input from: %INPUT_FILE% ---

REM Run the test itself
"%EXECUTABLE%" < "%INPUT_FILE%" > "%OUTPUT_FILE%"

REM Check the exit status of the previous command
if errorlevel 1 (
    echo Test could not run
) else (
    echo Test completed
    echo Output saved to: %OUTPUT_FILE%
)