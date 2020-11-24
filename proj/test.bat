@echo off
echo Running programs:
if exist Txx.txt del Txx.txt
@TestOne        > Txx.txt

type Txx.txt
@echo on
@echo Testing...
@a Txx.txt
pause