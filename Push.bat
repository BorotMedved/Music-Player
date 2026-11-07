@echo off

set /p cN="Commit: "

git add .

git commit -m "%cN%"

git push -u origin main

echo.
exit /b