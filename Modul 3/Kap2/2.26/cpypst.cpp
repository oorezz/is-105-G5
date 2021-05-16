//importing the needed header files 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
// importing library for basic input/ output services
#include <iostream>

// both cout and cin are defined inside of std for use
using namespace std;

/*defining main function
since we want to return a number to check 
if everything works fine
we define a int main() function */
int main(int argc, char *argv[]) {
	
   //defining variables for the names of the files
   
   string inputFile, outputFile;
   int inputFD, outputFD;     
    ssize_t bytesRd, bytesWr; //storing the bytes read and written
    int bufferSize = 32768;  //buffersize 2^15
    char buffer[bufferSize];  
    char filenameOut[256], filenameIn[256];
 

   //Make sure the file used for input is present in the current working directory
   //Acquire input file name, write prompt to screen and accept input
   cout << "First we need a file to copy from (ex: input.txt)" << endl;
   cout << "Enter the name of the input file" << endl;
   cin >> inputFile;
   //Acquire output file name, write prompt to screen , accept input
   cout << "Then we need another file as destination of copied data (ex: output.txt)" << endl; 
   cout << "Enter the name of the input file" << endl;
   cin >> outputFile;
   //converting string to char
   strcpy(filenameIn, inputFile.c_str());
   strcpy (filenameOut, outputFile.c_str());
	
    
    /* Open the input file, if file doesn't exist, abort */
    inputFD = open (filenameIn, O_RDONLY);    
    if (inputFD == -1) {
        perror ("Error while opening Input File");
        return 2;

    }
    //Create output file only if it doesn't exist
    outputFD = open(filenameOut, O_WRONLY | O_CREAT, 0644);
    if(outputFD == -1){
        perror("Error while opening Output File");
        return 3;
    }

    //Read from input file and write to output file until read fails 
    while((bytesRd = read (inputFD, &buffer, bufferSize)) > 0){
        bytesWr = write (outputFD, &buffer, (ssize_t) bytesRd);
        if(bytesWr != bytesRd){
            perror("Error in writing");
            return 4;

        }else {
          //Write completion message to screen
          cout<<"File copied correctly";
		} 
    }

     /* Close the file descriptors. */
    close (inputFD);
    close (outputFD);
    
    //Terminate normally
    return 0;

}