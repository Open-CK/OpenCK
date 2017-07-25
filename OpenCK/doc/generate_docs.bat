@ECHO OFF
REM This will only worked with doxygen installed.
REM Install it here: http://www.stack.nl/~dimitri/doxygen/
WHERE doxygen doxyfile
IF %ERRORLEVEL% NEQ 0 ECHO Doxygen not found!
pause
