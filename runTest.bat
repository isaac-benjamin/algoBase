@echo off
REM A custom command-line script for testing C++ programs in Windows CMD.

REM USAGE: test.bat <executable_file> <input_file.txt>
REM FIRST PARAM: executable
REM SECOND PARAM: input file - Defaults to test.txt

REM check for compare flag "-c"

set comp=%1

if defined comp (
    if "%comp%"=="-c" (
        set comp=1
        shift
    )
)

REM Set the executable name
if "%1"=="" (
    echo Error: No executable file specified.
    echo Usage: runTest ^<executable_file^> ^<optional_input_file.txt^>
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

REM file location setting
set "BASE_NAME=%INPUT_NAME:.txt=%"

set "INPUT_FOLDER=text_in"
set "OUTPUT_FOLDER=text_out"
set "EXPECTED_FOLDER=text_expected"

REM set input, expected, output
set "INPUT_FILE=%INPUT_FOLDER%\%INPUT_NAME%"
set "OUTPUT_FILE=%OUTPUT_FOLDER%\%BASE_NAME%_output.txt"
if not x%BASE_NAME:input=%==x%BASE_NAME% (
    set "EXPECTED_FILE=%EXPECTED_FOLDER%\%INPUT_NAME:input=answer%"
) else (
    set "EXPECTED_FILE=%EXPECTED_FOLDER%\%BASE_NAME%_expected.txt"
) 

REM Check if input file exists
if not exist %INPUT_FILE% (
    echo Error: Input file not found
    if "%2"=="" (
        echo Default value for input file is 'test.txt'
    )
    exit /b 1
)

REM file to compare is not provided in variables! 
REM        BUT if flag is checked command WILL check if it exists or error otherwise

if not exist %EXPECTED_FILE% (
    echo Compare flag was checked but a file to compare does not exist
    echo file should be: test_exepected/^<input^>_expected.txt
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

    REM compare if the flag is set
    if %comp%==1 (
        echo --- comparing expected to output ---
        fc "%OUTPUT_FILE%" "%EXPECTED_FILE%" > nul 
        if errorlevel 2 (
            echo There was a problem comparing %EXPECTED_FILE% and %OUTPUT_FILE%
        ) else if errorlevel 1 (
            echo Comparison Failed: 
            echo     %EXPECTED_FILE% and %OUTPUT_FILE% are NOT identical
        ) else (
            echo Comparison successful:
            echo     %EXPECTED_FILE% and %OUTPUT_FILE% are identical!
        )
    )
)
