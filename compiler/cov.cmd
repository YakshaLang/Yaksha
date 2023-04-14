REM Run coverage & generate html report using Docker & gcovr
docker build -t yaksha .
CALL :NORMALIZEPATH ".\bin\coverage"
SET LOCAL_PATH=%RETVAL%
CALL :NORMALIZEPATH ".\bin\fuzz"
SET FUZZ_PATH=%RETVAL%
docker run -v "%LOCAL_PATH%:/coverage" -v "%FUZZ_PATH%:/fuzz" --rm -it --entrypoint /app/scripts/code-coverage.sh yaksha

:: Reference https://stackoverflow.com/a/33404867/1355145
:: ========== FUNCTIONS ==========
EXIT /B

:NORMALIZEPATH
  SET RETVAL=%~f1
  EXIT /B