@ECHO OFF
REM This will only worked with doxygen installed.
REM Install it here: http://www.stack.nl/~dimitri/doxygen/
where doxygen >nul 2>&1 && doxygen doxyfile || echo Doxygen not found
pause
