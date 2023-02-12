@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"

%Program% 12312312345.txt %OUT% 1231234 0 || goto err
fc %OUT% 12312312345-out.txt || goto err

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1