@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%Program% 12312312345.txt %OUT% 1231234 0 || goto err
fc %OUT% 12312312345-out.txt || goto err

%Program% mama.txt %OUT% ma mama || goto err
fc %OUT% mama-out.txt || goto err

%Program% Empty.txt %OUT% 1231234 0 || goto err
fc %OUT% Empty-out.txt || goto err


echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1