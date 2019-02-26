#include <map>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <math.h>

#define CHAR_SIZE 8
#define INPUT_FILE "input.txt"          //  File you want to compress
#define OUTPUT_FILE "output.txt"        //  Compressed file
#define EOF_CODE "256"                  //  End Of File code
#define EO_DICO_CODE "257"            
#define ASCII_STARTING_CODE 258         //  Starting code for the dictionnary

using namespace std;

void getTheDicoSize(ifstream & inputStream, int & dicoSize);
void generateTheOutputFile(ofstream & outputStream, string & outputString, map<string, int> & lzw, int &gain, int &loss, int & inputLength, int & dicoSize);
void concatNextBlock(const string & block, string & outputString, const int & dicoSize, int & gain, int & loss, const map<string, int> & lzw);
int main();

