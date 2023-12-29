# gccsamples
This repository is a place for C samples created with gcc for IBM i and Linux

# grepsrclib.cpp - Scan selected IBM i library source members for selected string
Build command:    
```g++ grepsrclib.cpp -o grepsrclib```

Parameters:   
```
-l Source library name pattern to scan
-f Source file name pattern to scan
-m Source member name pattern to scan
-s String value to scan for (case insensitive)
```
Sample usage to scan QCLSRC in QGPL library:   
```grepsrclib -l "QGPL" -f "QCLSRC" -m "*" -s "monmsg"```
