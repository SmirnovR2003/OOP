@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err


::%Program% fillWithBarrier.txt %OUT% || goto err
::fc %OUT% fillWithBarrier-out.txt || goto err

%Program% fillWithoutBarrier.txt %OUT% || goto err
fc %OUT% fillWithoutBarrier-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1