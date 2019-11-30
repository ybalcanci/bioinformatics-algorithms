#include <iomanip>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

void writeToFile(vector<string> sequences, string fileName)
{
	ofstream myfile;
	myfile.open(fileName);
	for (int i = 0; i < sequences.size(); i++)
	{
		myfile << sequences[i] << endl;
	}
	myfile.close();
}