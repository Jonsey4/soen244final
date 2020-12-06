@echo Running Code Patterns...
@if exist Txx.txt del Txx.txt
@cmHost T01.exe > Txx.txt
@cmHost T02.exe >> Txx.txt
@cmHost T03.exe >> Txx.txt
@cmHost T04.exe >> Txx.txt
@cmHost T05.exe >> Txx.txt
@cmHost T06.exe >> Txx.txt
@cmHost T07.exe >> Txx.txt
@cmHost T08.exe >> Txx.txt
@cmHost T09.exe >> Txx.txt
@cmHost T10.exe >> Txx.txt
@cmHost T11.exe >> Txx.txt
@cmHost T12.exe >> Txx.txt
@echo ST01:
@cmHost ST01.exe >> Txx.txt
@echo ST01:
@cmHost ST02.exe >> Txx.txt
type Txx.txt
@echo on
@echo Checking test result...
@a Txx.txt
pause