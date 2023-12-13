// Aaron Squire and Eric Markstein
// 3/19/23
// This translation unit is the header file for the FileReader class
#ifndef __FILEREADER_H__
#define __FILEREADER_H__


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

class FileReader { 
    private:
        map<string,double> inputs;
    
    public:
        FileReader(string fileName);
        double get(string key);
};

#endif
