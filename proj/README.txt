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

    - Independently testing BSL: We can run testBslXtoa.bat. Done successfully, we will see the LED on the arduino blinking and output from putty:
            Test xtoa
            123456789ABCDEF
            123456789ABCDEF
    
    - Independently testing HAL
            Test Out:<2
            Bools: [T|F|T|T]
            Ints:  [-1|-2147483648|2147483647|4294967295|FFFFFFFF]
            Bools: [T|F|T|T]
            Ints:  [-1|-2147483648|2147483647|4294967295|FFFFFFFF]

    - Intependently testing Stack: Run testVMOperandStack.bat. Success will look like this:
            Test VM Operand Stack:
            [ ][ 2 1 ][ 3 ][ 3 3 ][ 9 ][ 8 9 ][ 1 ][ ]
            [ ][ 2 1 ][ 3 ][ 3 3 ][ 9 ][ 8 9 ][ 1 ][ ]

TASK 4: Go into admin0 and choose a binary test to run. Back out and run the task4.bat + putty to get the output of that hardcoded test