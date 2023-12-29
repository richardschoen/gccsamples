//---------------------------------------------------------------
// Program: grepsrclib.cpp
// Desc: Scan selected IBM i library source members for selected string
// Build command: g++ grepsrclib.cpp -o grepsrclib
//
// Parameters:
// -l Source library name pattern to scan
// -f Source file name pattern to scan
// -m Source member name pattern to scan
// -s String value to scan for (case insensitive)
//
// Returns:
// Stdout results from system command call. Can be piped to a file if desired via piping (Ex: > /tmp/grespsrclib.txt)
//
// Links:
// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
// Get STDOUT
// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
// Get stdin and stdout
// https://pstreams.sourceforge.net/
// Check file exists
// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
// g++ Catching exceptions
// https://stackoverflow.com/questions/315948/c-catching-all-exceptions
//---------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

/**
 * Get the size of a file.
 * @return The filesize, or 0 if the file does not exist.
 */
size_t getFileSize(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;   
}
//---------------------------------------------------------------
// Function: exec
// Parameters:
// cmd = system command line to run
// Returns:
// Stdout results from system command call
// Links:
// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
// System:
// https://en.cppreference.com/w/cpp/utility/program/system
// File size
// https://en.cppreference.com/w/cpp/filesystem/file_size
//---------------------------------------------------------------
std::string exec(const char* cmd) {
    char buffer[1024];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        result = "exec error occurred";
        throw;
    }
    pclose(pipe);
    return result;
}

// Function: exit_with_usage 
// Desc: exit program and display command line options
void exit_with_usage(FILE* f, const char* argv0, int rc) {
    fprintf(f, "usage: %s [-l \"srclibrary pattern\"] [-f \"srcfile pattern\"] [-m \"srcmember pattern\"] [-s \"searchforvalue\"]\n", argv0);
    fprintf(f, "Note: Make sure parameter values are delimited with double quotes as shown above.\n", argv0);
    fprintf(f, "Example: Note: Make sure parameter values are delimited with double quotes as shown above.\n", argv0);
    exit(rc);
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);

    return buf;
}

int main(int argc, char** argv) {

  string  programname = argv[0];
  string  srclibrary  = "";
  string  srcfile     = "";
  string  srcmember   = "";
  string  searchfor   = "";  
  string tempdir = "/tmp";
  string tempprefix = "tmpgrepsrclib_";
  string outputfile = "";
  string  qshcmd = "/QOpenSys/usr/bin/qsh";
  string  grepcmd = qshcmd + " -c \'/usr/bin/grep -i -n \"" + 
          searchfor + "\" /QSYS.LIB/" + 
          srclibrary + ".LIB/" + 
          srcfile + ".FILE/" + 
          srcmember + ".MBR\'" + " > " + outputfile;
  int rtnsys=0; 
  char cmdbuf[255];   
  bool found1=false;
  FILE *in_file;
  string results="";
  int rtnremove=0;
  int filesize=0;
  time_t now = time(0);
  char *date = ctime(& now);
  string dashes="-------------------------------------------------------------------------";

  // Handle command line options
  // -l library, -f file, -m member, -s searchforvalue
  int opt;
  int opterrcount=0;
  while ((opt = getopt(argc, argv, "hl:f:m:s:")) != -1) {
        switch (opt) {
        case 'h':
            exit_with_usage(stdout, argv[0], 0);
        case 'l': /* ctl */
            srclibrary = optarg;
            break;
        case 'f':
            srcfile = optarg;
            break;
        case 'm':
            srcmember = optarg;
            break;
        case 's':
            searchfor = optarg;
            break;
        default:
            exit_with_usage(stderr, argv[0], 1);
        }
   } 

   // Check expected parm values to make sure they all have options specified.
   if (srclibrary == "") {
       std::cout << "Source library pattern not specified. Ex: -l \"QGPL\""<< std::endl;
       opterrcount++;
   }
   if (srcfile == "") {
       std::cout << "Source file pattern not specified. Ex: -f \"QCLSRC\""<< std::endl;
       opterrcount++;
   }
   if (srcmember == "") {
       std::cout << "Source member pattern not specified. Ex: -m \"*\" = All Members"<< std::endl;
       opterrcount++;
   }
   if (srcmember == "a.out") { // An asterisk with no double quotes was specified if we get a.out as value
       srcmember="*" ;// Set to all members if blanks
   }
   if (searchfor == "") {
       std::cout << "Search for value not specified. Ex: -s \"monmsg\""<< std::endl;
       opterrcount++;
   }

   // Exit if any errors on option checking
   if (opterrcount>0){
     exit(EXIT_FAILURE);
   }

  // Let's do some grep work. 

  // Build temp output file name
  outputfile = tempdir + "/" + tempprefix + currentDateTime() + ".txt";
  std::cout << "Output file: " + outputfile << std::endl;
  
  // Build grep command line
  grepcmd = qshcmd + " -c \'/usr/bin/grep -i -n \"" + 
            searchfor + "\" /QSYS.LIB/" + 
            srclibrary + ".LIB/" + 
            srcfile + ".FILE/" + 
            srcmember + ".MBR\'" + " > " + outputfile;

  // Check for QSH command existence
  if (in_file = fopen(qshcmd.data(), "r")) {
     fclose(in_file);
  } else {
     std::cout << "QShell command interpreter not found at: " + qshcmd << std::endl;
     exit(99);
  }

  // Remove existing temporary output file if it's found
  if (in_file = fopen(outputfile.data(), "r")) {
     fclose(in_file);
     rtnremove=remove(outputfile.data());
  } else {
     // Do nothing if file doesn't exist. We're ready to run grep and create the file. 
  }

  // Output parameters to stdout
  std::cout << dashes << std::endl;  
  std::cout << programname + " - Searching source library via grep" << std::endl;
  std::cout << "Parameters" << std::endl;
  std::cout << "Library:" + srclibrary << std::endl;
  std::cout << "File:" + srcfile << std::endl;
  std::cout << "Member:" + srcmember << std::endl;
  std::cout << "SearchFor:" + searchfor << std::endl;
  std::cout << "Grep command:" + grepcmd << std::endl;
  
  // Copy string command line to command line character buffer via c_str()
  strcpy(cmdbuf, grepcmd.c_str()); 
  
  // Run the grep system command now
  // exec will return stdout from the system command as results string
  std::cout << "Source Library Grep Starting" << std::endl;
  rtnsys=std::system(cmdbuf); // executes the UNIX command to output file

  // Get the file size and output stdout from file contents if more than 0 bytes  
  filesize=getFileSize(outputfile.c_str());
  if (filesize>0) {
     std::cout << std::ifstream(outputfile).rdbuf() << std::endl;
  } else { // Return no data message if none found.
    std::cout << "No data returned from grep command." << std::endl;
    std::cout << "Most likely the search string wasn't found in any source members." << std::endl;
  } 

  // Output return code from grep command call
  std::cout << "grep return code:" + std::to_string(rtnsys)  << std::endl;

  // Remove existing temporary output file if it's found
  if (in_file = fopen(outputfile.data(), "r")) {
     fclose(in_file);
     std::cout << "Removing temp file:" + outputfile  << std::endl;
     rtnremove=remove(outputfile.data());
  } else {
     // Do nothing if file doesn't exist. We're ready to run grep and create the file. 
  }

  // Output the stdout result buffer from the exec command
  // TODO - Possibly write to file
  //std::cout << results << std::endl;

  // If any errors on grep command, exit with failure, otherwise success.
  if (rtnsys!=0) {
     std::cout << "Source Library Grep Completed with Errors" << std::endl;
     std::cout << dashes << std::endl;  
     return EXIT_FAILURE;
  } else{
     std::cout << "Source Library Grep Completed Normally" << std::endl;
     std::cout << dashes << std::endl;  
     return EXIT_SUCCESS;
  }
  
}

