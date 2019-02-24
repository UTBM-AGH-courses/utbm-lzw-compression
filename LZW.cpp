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


void getTheDicoSize(ifstream & inputStream, int & dicoSize)
{
    if (inputStream.good())
    {
        string sLine;
        getline(inputStream, sLine);
        cout << "dico  size : " + sLine << endl;
        dicoSize = atoi(sLine.c_str());
    }
}

void printTheOutPutString(vector<string> & outputString, map<string, int> & lzw, int & gain, int & loss)
{
    cout << "output string : ";
    for (auto const& x : outputString)
    {
        if(x.size() > 1) {
            cout << "<";
            cout << lzw[x] ;
            cout << ">";
            gain += CHAR_SIZE*(x.size()) - DICO_BLOCK_SIZE;
        }
        else {
            cout << x ;
            loss += DICO_BLOCK_SIZE - CHAR_SIZE;
        }
    }
    cout << endl;
}


void printTheDico(map<string, int> & lzw)
{
    cout << "dico : " << endl;
    for(auto it = lzw.cbegin(); it != lzw.cend(); ++it)
    {
        std::cout << it->first << " : " << it->second << endl;
    }
}

void addEOFCode(vector<string> & outputString, map<string, int> & lzw) 
{
    string eof = "eof";
    lzw[eof] = 256;
    outputString.push_back(eof);
}


int main()
{
    // init the dictionary
    map<string, int> lzw;
    //dico size & ASCII code
    int dicoSize, asciiCode = 258;
    int gain = 0, loss = 0, inputLength = 0;
    //open the input file
    ifstream inputStream;
    inputStream.open(INPUT_FILE,ios_base::in);
    //open the output file
    ofstream outputStream;
    outputStream.open(OUTPUT_FILE, ofstream::out | ofstream::trunc);


    //char read from the output file
    char c;
    //new entry for the dico & waiting code
    string p = "",  w = "";
    vector<string> outputString ;

    // get the dico size
    getTheDicoSize(inputStream, dicoSize);
    

    while (inputStream.get(c)) {
        p = w + c;
        auto it = lzw.find(p); 
        //if there is an existing entry for p in the dico
        if(!(it == lzw.end()) || p.size() <= 1) 
        {
            w = p; 
        }
        else 
        {
            outputString.push_back(w);            
            lzw[p] = asciiCode;
            w = c;          
            asciiCode++;
        }
        inputLength += CHAR_SIZE;
    }      

    inputStream.close();

    string test = "slkdfjh";
    outputStream << test;

    outputString.push_back(w);
    addEOFCode(outputString, lzw);
    printTheOutPutString(outputString, lzw, gain, loss);
    printTheDico(lzw);

    return 0;
}
