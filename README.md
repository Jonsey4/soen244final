README.txt

This file describes how to run our tests
- make sure to run our final-form VM 'f_vmFlash.bat' to flash the arduino with a proper version of Cm
- navigate to proj/hostSL directory
- use commands 'dotnet build' and 'dotnet run <test-file.exe>' to run tests using the MODIFIED host loader
- d to download, wait, then r to run 

- With the modifieds loader, all tests, new and old, 8 bytes or not, should be functional.

Additional testing can be accomplished with respective .bat file
- task4.bat will run a test into the serial port, hard coded if the appropriate array has been defined in admin0.c. 
- task5.bat compiles the vm with the loader attached.
