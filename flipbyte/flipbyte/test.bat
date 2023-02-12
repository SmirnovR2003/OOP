@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 256
if NOT ERRORLEVEL 1 goto err

%PROGRAM% -1
if NOT ERRORLEVEL 1 goto err

%PROGRAM% abc
if NOT ERRORLEVEL 1 goto err


%Program% 6 > %OUT%|| goto err
fc %OUT% 6-out.txt || goto err

%Program% 0 > %OUT%|| goto err
fc %OUT% 0-out.txt || goto err

%Program% 1 > %OUT%|| goto err
fc %OUT% 1-out.txt || goto err

%Program% 255 > %OUT%|| goto err
fc %OUT% 255-out.txt || goto err

:ok
echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1