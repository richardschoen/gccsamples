//---------------------------------------------------------------
// Program: parmtest1.cpp
// Desc: Command line parameter test progra,
// Build command: g++ parmtest1.cpp -o parmtest1
//
// Parameters:
// -h or --h - Display comand line app help.
// --file - Input file name.
// --outputfile - Output file name.
//
// How to test sample:
// parmtest1 (with no parms) - Shows no parameters specified error
// parmtest1 -h - Shows command line parameter help
// parmtest1 --file "/tmp/input.txt" -  No output file name specified. Parm: --outputfile
// parmtest1 --outputfile "/tmp/output.txt" -  No input file name specified. Parm: --file
// parmtest1 --file "/tmp/input.txt" --outputfile "/tmp/output.txt" - All good. Let's do some work.
//
// Links:
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
//---------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//-----------------------------------------------------------------------
// Function: getCmdOption
// Desc: Get command option.
// Parms:
// begin - first command line argument
// end - end of command line
// option - command option to find. Ex: --f or --file or --o or --outputfile
// Returns:
// Return parameter option or 0 if no value returned.
//-----------------------------------------------------------------------
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

//-----------------------------------------------------------------------
// Function: cmdOptionExists
// Desc: See if command line options exists in command line.
// Parms:
// begin - first command line argument
// end - end of command line
// option - command option to find. Ex: --f or --file or --o or --outputfile
// Returns:
// True=Command line option exists. False=Command line option not found.
//-----------------------------------------------------------------------
bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

//-----------------------------------------------------------------------
// Function: main
// Desc: Main program processing
//-----------------------------------------------------------------------
int main(int argc, char * argv[])
{

    string programname=argv[0];
    string programdesc="Parameter test app";
    string parmfilename="";
    string parmoutputfile="";
    int errorcount=0;

   try {

          // If no parms passed, bail out
          if (argc<=1) {
            // Display no parameters message.
            std::cout << argv[0] << " - No parameters specified."  << std::endl <<  
            "Run: " << programname << " -h or " << 
            programname <<  " --h to see valid parms." << std::endl;
            // Exit program with error
            return(EXIT_FAILURE);
          }

          // Output command line option help. if --h or -h 
          // specified anywhere in command line.
          if(cmdOptionExists(argv, argv+argc, "--h") || 
            cmdOptionExists(argv, argv+argc, "--H") ||
            cmdOptionExists(argv, argv+argc, "-h") || 
            cmdOptionExists(argv, argv+argc, "-H")) {
          
            // Display command line option help
            std::cout << argv[0] << " -  " << programdesc << std::endl;
            std::cout << "Available parameters:" << std::endl;
            std::cout << "--file - Input file name (Required)" << std::endl;
            std::cout << "--outputfile - Output file name (Required)" << std::endl;

            // Exit after displaying command line help.
            return(EXIT_SUCCESS);

          }

          // Process command line and look for parms 

          char * filename = getCmdOption(argv, argv + argc, "--file");

          // If file name was located, process file parm 
          if (filename)
          {
            parmfilename=filename; // Move parm to string field.
            std::cout << "Input file name specified:" << parmfilename << std::endl;
          } else { // Parm not specified
            std::cout << "No input file name specified. Parm: --file" << std::endl;
            errorcount++; // Add to parm error count.
          }

          char * outputfile = getCmdOption(argv, argv + argc, "--outputfile");

          // If file name was located, process file parm 
          if (outputfile)
          {
            parmoutputfile=outputfile; // Move parm to string field.
            std::cout << "Output file name specified:" << parmoutputfile << std::endl;
          } else { // Parm not specified
            std::cout << "No output file name specified. Parm: --outputfile" << std::endl;
            errorcount++; // Add to parm error count.
          }

          // If any parameter errors, bail out now.
          if (errorcount>0) {
              std::cout << "At least one parameter error occurred." << std::endl;
              // Exit program with error
              return(EXIT_FAILURE);
          }

          // Now we have all of our parameters. Let's do some work.

          // For this example we output a simple message as our work.
          std::cout << "Let's do some work now." << std::endl;

          // Exit program normally
          return (EXIT_SUCCESS);

   } catch (std::exception& ex) {
       // Output error
       cerr << ex.what() << std::endl; 
       // Exit program with error
       return(EXIT_FAILURE);
   }

} 
  
