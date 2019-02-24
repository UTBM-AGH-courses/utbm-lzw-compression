
#include "LZW.hpp"

void getTheDicoSize(ifstream & inputStream, int & dicoSize)
{
    if (inputStream.good())
    {
        string sLine;
        getline(inputStream, sLine);
        dicoSize = atoi(sLine.c_str());
    }
}

void generateTheOutputFile(ofstream & outputStream, vector<string> & outputString, map<string, int> & lzw, int &gain, int &loss, int & inputLength)
{
    outputStream << "output string : ";
    for (auto const& x : outputString)
    {
        if(x.size() > 1 && x.compare("eof") != 0) {
            outputStream << "<";
            outputStream << lzw[x] ;
            outputStream << ">";
            gain += (CHAR_SIZE*(x.size()) - DICO_BLOCK_SIZE);
        }
        else if(x.compare("eof") != 0)
        {
            outputStream << x ;
            loss += (DICO_BLOCK_SIZE - CHAR_SIZE);
        }
    }
    outputStream << "<" + to_string(lzw["eof"]) + ">";
    outputStream << endl;
    outputStream << "gain : " + to_string(gain) + "\n";
    outputStream << "loss : " + to_string(loss) + "\n";
    outputStream << "theorical size : " + to_string(inputLength) + "\n";
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
    //char read from the output file
    char c;
    //open the input file
    ifstream inputStream;
    inputStream.open(INPUT_FILE,ios_base::in);
    //open the output file
    ofstream outputStream;
    outputStream.open(OUTPUT_FILE, ofstream::out | ofstream::trunc);

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
    outputString.push_back(w);

    addEOFCode(outputString, lzw);
    generateTheOutputFile(outputStream, outputString, lzw, gain, loss, inputLength);

    return 0;
}
