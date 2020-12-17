#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

//---------------------------------------------------------------------------------------------
// Program: runclcmd.c
// Purpose: Run IBM i system CL command
// Parms: Formatted IBM i CL command line  
// 
// Building this program: gcc -o runclcmd runclcmd.c
//
//https://stackoverflow.com/questions/36804759/how-to-copy-argv-to-a-new-variable
//https://stackoverflow.com/questions/19194254/how-can-i-copy-the-contents-of-argv-into-a-c-style-string
//https://www.guru99.com/c-strings.html
//---------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{

  // Local Variables   
  int rtnsys=0;
  int exitcode=0;
  char dashes[]="-------------------------------------------------------";  
  char exitmessage[5000]="";
  char commandline[5000];

  // Parameters
  // arg[0] = programname
  // arg[1] = cl command (delimited with double quotes)

  // Print messages to stdout for console
  printf("%s\n",dashes);
  printf("Start of runclcmd\n");

  // Make sure single parm passed. Args are programname=arg[0], clcommand=arg[1]
  if (argc < 2) {
     printf("A single parm is need with a CL command surrounded by double quotes.\n");
     exit(2);
  }
  // If more than 1 parm passed, exit.  
  else if (argc > 2) {
     printf("Only a single CL command is needed surrounded by double quotes.\n");
     exit(2);
  }  
  
  // Build CL system command
  strcpy(commandline,"system \"");
  strcat(commandline,argv[1]);
  strcat(commandline,"\"");
  
  // Print command before running it
  printf("About to run command: %s\n",commandline);
  
  // Run the system command line
  rtnsys=system(commandline);
         
  // Exit with appropriate return code     
  if (rtnsys==0) {
     // Print success info and set exit code 
     //fprintf(stdout,"System command ran successfully. Return code:%d\n", rtnsys); Puts output to stdout
     printf("System command ran successfully. Return code:%d\n", rtnsys);
     strcpy(exitmessage,"System command ran successfully.");
     exitcode=0;
  } else {
     // Print error info and set error exit code 
     //fprintf(stderr,"System command failed. Return code:%d\n", rtnsys); - Puts output to stderr
     printf("System command failed. Return code:%d\n", rtnsys);
     sprintf(exitmessage, "System command failed. Return message: %s", strerror( rtnsys ));
     exitcode=99;
  }       
  
  // Send feedback to the IBM i stdout log so it can be placed in 
  // the IBM i caller joblog or consumed by a CL or RPG program if desired
  printf("SystemReturnCode:%d\n",rtnsys);
  printf("ExitCode:%d\n",exitcode);
  printf("ExitMessage:%s\n",exitmessage);
  printf("End of runclcmd\n");
  printf("%s\n",dashes);
  
  // Exit with the appropriate exit code.
  exit(exitcode);
       
}
