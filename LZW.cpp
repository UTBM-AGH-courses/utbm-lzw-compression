
#include "LZW.hpp"

void getTheDicoSize(ifstream & inputStream, int & dicoSize)             //Get the size of the dictionnary
{
    if (inputStream.good())
    {
        string sLine;
        getline(inputStream, sLine);
        dicoSize = atoi(sLine.c_str());
    }
}

void generateTheOutputFile(ofstream & outputStream, string & outputString, map<string, int> & lzw, int &gain, int &loss, int & inputLength, int & dicoSize)
{
    outputStream << "output string : " + outputString + "\n";                   //Write different info resulting from the compression on output.txt
    outputStream << "gain : " + to_string(gain) + "\n";
    outputStream << "loss : " + to_string(loss) + "\n";
    outputStream << "theorical size : " + to_string(inputLength) + "\n";
}

void concatNextBlock(const string & block, string & outputString, const int & dicoSize, int & gain, int & loss, map<string, int> & lzw) 
{
    if(block.size() > 1) 
    {
        outputString += "<" + to_string(lzw[block]) + ">";
        gain += (CHAR_SIZE*(block.size()) - log2(dicoSize));
    }
    else 
    {
        outputString += block;
        loss += (log2(dicoSize) - CHAR_SIZE);
    } 
}


int main()
{
    // init the dictionary
    map<string, int> lzw;

    //  dico size & ASCII code
    int dicoSize, asciiCode = ASCII_STARTING_CODE;
    int gain = 0, loss = 0, inputLength = 0;

    //  char read from the output file
    char c;

    //  new entry for the dico & waiting code
    string p = "",  w = "", outputString = "";

    //open the input file
    ifstream inputStream;
    inputStream.open(INPUT_FILE,ios_base::in);
    //open the output file
    ofstream outputStream;
    outputStream.open(OUTPUT_FILE, ofstream::out | ofstream::trunc);

    // get the dico size
    getTheDicoSize(inputStream, dicoSize);
    
    while (inputStream.get(c)) {                    //  While there's still something to read
        if(lzw.size() == dicoSize)                 //   For the first data we have to compress
        {
            lzw.clear();
            asciiCode = ASCII_STARTING_CODE;
            outputString += "<257>";

        }
        p = w + c;                                  
        auto it = lzw.find(p); 
        //if there is an existing entry for p in the dico
        if(!(it == lzw.end()) || p.size() <= 1) 
        {
            w = p;
        }
        else    
        {
            concatNextBlock(w, outputString, dicoSize, gain, loss, lzw);
            lzw[p] = asciiCode;
            w = c;    
            asciiCode++;            
        }
        inputLength += log2(dicoSize);
    }      
    concatNextBlock(w, outputString, dicoSize, gain, loss, lzw);
    inputStream.close();                                       
    outputString += "<256>";                                    //  End Of File code
    generateTheOutputFile(outputStream, outputString, lzw, gain, loss, inputLength, dicoSize);

    return 0;
}
