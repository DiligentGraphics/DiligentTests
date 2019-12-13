set ERROR=0
C:\projects\build\DiligentTests\DiligentCoreTests\%CONFIGURATION%\DiligentCore_Tests.exe
if %ERRORLEVEL% NEQ 0 (
	set ERROR=%ERRORLEVEL%
)

@echo Error level : %ERRORLEVEL%
@echo Error: %ERROR%

C:\projects\build\DiligentTests\DiligentCoreTests\%CONFIGURATION%\DiligentCore_Tests.exe --gtest_filter=FactorialTest.Zero
if %ERRORLEVEL% NEQ 0 (
	set ERROR=%ERRORLEVEL%
)

@echo Error level : %ERRORLEVEL%
@echo Error: %ERROR%

exit /B %ERROR%
