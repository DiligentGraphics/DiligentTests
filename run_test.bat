set ERROR=0
C:\projects\build\DiligentTests\DiligentCoreTests\%CONFIGURATION%\DiligentCore_Tests.exe
if %ERRORLEVEL% NEQ 0 (
	set ERROR=%ERRORLEVEL%
)

@echo Error level : %ERRORLEVEL%
exit /B %ERROR%
