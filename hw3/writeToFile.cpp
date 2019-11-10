#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

//https://stackoverflow.com/questions/35251635/fasta-reader-written-in-c
int writeToFile(string sequence1Name, string sequence1, string sequence2Name, string sequence2, int score, string fileName) {
	int sequence1Length = sequence1.size();
	int sequence2Length = sequence2.size();
	
	ofstream myfile;
	myfile.open (fileName);
	myfile << "Score = " << score << endl;
	myfile << left;
	for(int i = 0; i < ceil(max(sequence1Length, sequence2Length) / 60.0); i++){
		myfile << endl;
		myfile << setw(25) << sequence1Name << ( sequence1Length > i*60 ? sequence1.substr(i * 60, 60) : "" )<< endl;
		myfile << setw(25) << sequence2Name << ( sequence2Length > i*60 ? sequence2.substr(i * 60, 60) : "" ) << endl;
	}
	myfile.close();
	return 0;
}