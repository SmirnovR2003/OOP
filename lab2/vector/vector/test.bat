@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"
goto ok
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% < Empty.txt > %OUT%
if NOT ERRORLEVEL 1 goto err
fc Empty-out.txt %OUT% || goto err

%PROGRAM% < NormalTest1.txt > %OUT%
fc NormalTest1-out.txt %OUT% || goto err

%PROGRAM% < NormalTest2.txt > %OUT%
fc NormalTest2-out.txt %OUT% || goto err

%PROGRAM% < NotNormalTest.txt > %OUT%
fc NotNormalTest-out.txt %OUT% || goto err

:ok
echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1