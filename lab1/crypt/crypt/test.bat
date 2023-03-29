@echo off

set Program="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% crypt crypt.exe crypted.exe 256
if NOT ERRORLEVEL 1 goto err

%PROGRAM% crypt crypt.exe crypted.exe asd
if NOT ERRORLEVEL 1 goto err

%PROGRAM% cdrypt crypt.exe crypted.exe 25
if NOT ERRORLEVEL 1 goto err


%PROGRAM% crypt crypt.exe crypted.exe 25 || goto err

%PROGRAM% decrypt crypted.exe decrypted.exe 25 || goto err

decrypted.exe crypt crypt.exe crypted2.exe 25 ||  goto err
fc crypted.exe crypted2.exe || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1