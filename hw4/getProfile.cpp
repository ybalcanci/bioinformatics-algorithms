#include <string>
#include <bits/stdc++.h>

using namespace std;

vector<vector<double>> getProfile(vector<string> sequences)
{
	vector<vector<double>> profile(5, vector<double>(sequences[0].length()));
	double numSequences = (double)sequences.size();
	for (int i = 0; i < sequences[0].length(); i++)
	{
		int numA = 0, numC = 0, numG = 0, numT = 0, numEmpty = 0;
		for (int j = 0; j < numSequences; j++)
		{
			switch (sequences[j].at(i))
			{
			case 'A':
				numA++;
				break;

			case 'C':
				numC++;
				break;

			case 'G':
				numG++;
				break;

			case 'T':
				numT++;
				break;

			case '-':
				numEmpty++;
				break;

			default:
				break;
			}
		}
		profile[0][i] = numA / numSequences;
		profile[1][i] = numC / numSequences;
		profile[2][i] = numG / numSequences;
		profile[3][i] = numT / numSequences;
		profile[3][i] = numEmpty / numSequences;
	}

	return profile;
}