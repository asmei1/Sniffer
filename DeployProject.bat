@SET currentdir=%cd%
@ECHO OFF
@SET source=%currentdir%\
@SET dest=%currentdir%\Bin

ClS
ECHO  *************
ECHO  *  SNIFFER  *
ECHO  *************
ECHO  Curent dir %currentdir%
ECHO  And push to %dest%

ECHO Clean bin folder
rmdir /S /Q %dest%

Mkdir %dest%

ECHO Copying
@SET execPath="%source%x64\Release\Sniffer.exe"
ECHO %execPath%
xcopy %source%x64\Release\Sniffer.exe %dest%

ECHO *WINDEPLOYQ**

Cd %dest%

REM CALL  "C:\Qt\5.12.6\msvc2017_64\bin\windeployqt.exe  -force  Sniffer.exe"
REM C:\Qt\5.12.6\msvc2017_64\bin\windeployqt.exe  -force Sniffer.exe

C:\Qt\5.12.6\msvc2017_64\bin\windeployqt.exe  -force -no-translations Sniffer.exe


REM CD %dest%
CD %currentdir%
ECHO ***********
ECHO  FINISHED 
ECHO ***********
Pause
REM exit