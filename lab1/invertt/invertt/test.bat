@echo off

set Program="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%Program% unCorrectMatrix.txt > %OUT% 
if NOT ERRORLEVEL 1 goto err

%Program% matrixWithZeroDeterminant.txt > %OUT% 
if NOT ERRORLEVEL 1 goto err

%Program% testMatrix.txt > %OUT%  || goto err
fc %OUT% testMatrix-out.txt || goto err

%Program% testMatrix1.txt > %OUT%  || goto err
fc %OUT% testMatrix1-out.txt || goto err

%Program% testMatrix2.txt > %OUT%  || goto err
fc %OUT% testMatrix2-out.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1