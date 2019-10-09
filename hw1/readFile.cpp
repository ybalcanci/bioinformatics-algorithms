#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string readFile(std::ifstream& in) {
    stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
