#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

//---------------------------------------------------------------------------------------------
// Program: pingi.c
// Purpose: Run IBM i PING system CL command from PASE
// Parms: 
// 1.) Host name or IP address  
// 
// Building this program: gcc -o pingi pingi.c
//---------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{

  // Local Variables   
  int rtnsys=0;
  int exitcode=0;
  char dashes[]="-------------------------------------------------------";  
  char exitmessage[5000]="";
  char commandline[5000];

  // Make sure single parm passed. Args are programname=arg[0], clcommand=arg[1]
  if (argc < 2) {
     printf("A single host name or IP is needed.\n");
     exit(2);
  }
  // If more than 1 parm passed, exit.  
  else if (argc > 2) {
     printf("Only a single host name or IP address is needed.\n");
     exit(2);
  }  
  
  // Build CL system command
  strcpy(commandline,"system \" ping '");
  strcat(commandline,argv[1]);
  strcat(commandline,"'\"");
  
  // Run the system command line
  rtnsys=system(commandline);
         
  // Exit with appropriate return code     
  if (rtnsys==0) {
     printf("PING ran successfully. Return code:%d\n", rtnsys);
     exit(0);
  } else {
     printf("PING failed failed. Return code:%d\n", rtnsys);
     exit(99);
  }       
       
}
