set ERROR=0
C:\projects\build\DiligentTests\DiligentCoreTests\%CONFIGURATION%\DiligentCore_Tests.exe || ERROR=%ERRORLEVEL%
exit /B %ERROR%
