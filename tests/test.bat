@echo off
setlocal
set ROOT=%~dp0..
set BIN=%ROOT%\bin\lru.exe
if not exist "%BIN%" (
  echo Binary not found. Run: mingw32-make
  exit /b 1
)
type "%~dp0sample.in" | "%BIN%" > "%~dp0actual.out"
fc "%~dp0expected.out" "%~dp0actual.out"
if errorlevel 1 (
  echo Tests FAILED
  exit /b 1
) else (
  echo All tests passed.
)
del "%~dp0actual.out"
endlocal
