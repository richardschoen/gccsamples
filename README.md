# gccsamples
This repository is a place for C and C++ samples created with gcc for IBM i and Linux

# grepsrclib.cpp - Scan selected IBM i library source members for selected string
Build command:    
```g++ grepsrclib.cpp -o grepsrclib```   
If you want the program to reside with the other packages from open source package management, copy the compiled object to the ```/QOpenSys/pkgs/bin``` directory. The final object path will be: ```/QOpenSys/pkgs/bin/grepsrclib```     

Parameters:   
```
-l Source library name pattern to scan
-f Source file name pattern to scan
-m Source member name pattern to scan
-s String value to scan for (case insensitive)
```

Sample usage to scan QCLSRC in QGPL library:   
```grepsrclib -l "QGPL" -f "QCLSRC" -m "*" -s "monmsg"```

# parmtest1.cpp - Command line parameter test program
This program is a good example of passing parameters to a command line C++ program.   

Build command:    
```g++ parmtest1.cpp -o parmtest1```   

Parameters:   
```
--file  - Input file name
--outputfile - Output file name
```

Sample usage:   
```parmtest1 --file "/tmp/input.txt" -outputfile "/tmp/output.txt"```
