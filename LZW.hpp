#include <map>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

#define MAP_SIZE 4096
#define CHAR_SIZE 8
#define DICO_BLOCK_SIZE 12
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

using namespace std;

void getTheDicoSize(ifstream & inputStream, int & dicoSize);
void generateTheOutputFile(ofstream & outputStream, vector<string> & outputString, map<string, int> & lzw, int &gain, int &loss, int & inputLength);
void addEOFCode(vector<string> & outputString, map<string, int> & lzw);
int main();

