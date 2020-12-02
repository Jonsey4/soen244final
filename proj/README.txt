TASK 0/1/2: To complete and demonstrate this task, compile cmHost.exe and then run runtests.bat. this will result in 12 passed tests. 
    - It demonstrates aunit's successful build and use as well as the proper compilation/"port" of the vm on the host

TASK 3: Here we added UART functionality to bsl_COut.cmHost
    - Ensure youre on the right COM port in Putty. The testBslXtoa batch file has been hard coded with COM4, but switch if needed
    - Putty > Connection > Serial
        Baud 9600
        Data bits: 8
        Stop bits: 1
        Parity: None
        Flow Control: None
    - Putty > Terminal 
        Select Implicit CR in every LF

    - Independently testing BSL: We can run testBslXtoa.bat from within ./vmfiles. Done successfully, we will see the LED on the arduino blinking and output from putty:
            Test xtoa
            123456789ABCDEF
            123456789ABCDEF
    
    - Independently testing HAL

    - Intependently testing Stack