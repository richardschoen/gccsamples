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

# pingi.c - Ping using IBM i PING CL command.
This program is a good example of calling the PING CL command from a c program. 

```Useful since PASE does not have a ping command.```

Build command:    
```gcc pingi.c -o pingi```   

Parameters:   
```
parm1 = host name or IP address to ping.
```

Sample usage:   
```pingi "8.8.8.8"```   

Results:   
```
TCP3204: Verifying connection to host system 8.8.8.8.
TCP3215: PING reply 1 from 8.8.8.8 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 2 from 8.8.8.8 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 3 from 8.8.8.8 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 4 from 8.8.8.8 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 5 from 8.8.8.8 took 11 ms. 256 bytes. TTL 60.
TCP3211: Round-trip (in milliseconds) min/avg/max = 11/11/11.
TCP3210: Connection verification statistics: 5 of 5 successful (100 %).
PING ran successfully. Return code:0
```

```pingi "8.8.8.9"```   

Results:   
```
TCP3204: Verifying connection to host system 8.8.8.9.
TCP3206: No response from host within 1 seconds for connection verification 1.
TCP3206: No response from host within 1 seconds for connection verification 2.
TCP3206: No response from host within 1 seconds for connection verification 3.
TCP3206: No response from host within 1 seconds for connection verification 4.
TCP3206: No response from host within 1 seconds for connection verification 5.
TCP3210: Connection verification statistics: 0 of 5 successful (0 %).
PING ran successfully. Return code:0
```

```pingi "google.com"```

Results:   
```
TCP3203: Verifying connection to host system google.com at address 108.177.122.138.
TCP3215: PING reply 1 from 108.177.122.138 took 12 ms. 256 bytes. TTL 60.
TCP3215: PING reply 2 from 108.177.122.138 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 3 from 108.177.122.138 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 4 from 108.177.122.138 took 11 ms. 256 bytes. TTL 60.
TCP3215: PING reply 5 from 108.177.122.138 took 11 ms. 256 bytes. TTL 60.
TCP3211: Round-trip (in milliseconds) min/avg/max = 11/11/12.
TCP3210: Connection verification statistics: 5 of 5 successful (100 %).
PING ran successfully. Return code:0
```
