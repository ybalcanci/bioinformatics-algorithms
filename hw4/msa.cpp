#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <map>

using namespace std;
vector<vector<double>> getProfile(vector<string> sequences);
vector<string> msa(vector<string> sequences, string mainSequence, int gap, int match, int mismatch)
{
	vector<vector<double>> profile = getProfile(sequences);
	map<char, int> charMap;
	charMap['A'] = 0, charMap['C'] = 1, charMap['G'] = 2, charMap['T'] = 3, charMap['-'] = 4;

	int profileLength = profile[0].size();
	int sequenceLength = mainSequence.size();

	double table[sequenceLength + 1][profileLength + 1];
	char directionTable[sequenceLength + 1][profileLength + 1];

	// Basic values in the tables.
	table[0][0] = 0;

	// Fill in the 0th columns
	for (int i = 1; i < sequenceLength + 1; i++)
	{
		table[i][0] = table[i - 1][0] + gap;
		directionTable[i][0] = 'u';
	}

	// Fill in the 0th rows
	for (int j = 1; j < profileLength + 1; j++)
	{
		table[0][j] = table[0][j - 1] + gap;
		directionTable[0][j] = 'l';
	}

	// Fill in the tables
	for (int i = 1; i < sequenceLength + 1; i++)
	{
		for (int j = 1; j < profileLength + 1; j++)
		{
			double matchingRate = profile[charMap[mainSequence.at(i - 1)]][j - 1];
			double profileBlankPunishment = profile[charMap['-']][j - 1];
			double diagonalExtra = matchingRate * match + (1 - matchingRate) * mismatch;
			double leftExtra = gap;
			double upExtra = profileBlankPunishment * match + (1 - profileBlankPunishment) * mismatch;

			if (table[i - 1][j - 1] + diagonalExtra >= table[i][j - 1] + leftExtra && table[i - 1][j - 1] + diagonalExtra >= table[i - 1][j] + upExtra)
			{
				table[i][j] = table[i - 1][j - 1] + diagonalExtra;
				directionTable[i][j] = 'd';
			}
			else if (table[i][j - 1] + leftExtra >= table[i - 1][j - 1] + diagonalExtra && table[i][j - 1] + leftExtra >= table[i - 1][j] + upExtra)
			{
				table[i][j] = table[i][j - 1] + leftExtra;
				directionTable[i][j] = 'l';
			}
			else
			{
				table[i][j] = table[i - 1][j] + upExtra;
				directionTable[i][j] = 'u';
			}
		}
	}
	/*
	// print tables
	for(int i = 0; i < sequenceLength + 1; i++){
		for(int j = 0; j < profileLength + 1; j++)
			cout << setw(5) << table[i][j];
		printf("\n");
	}
	
	for(int i = 0; i < sequenceLength + 1; i++){
		for(int j = 0; j < profileLength + 1; j++)
			printf("%*c",4,directionTable[i][j]);
		printf("\n");
	}
*/

	// Backtracking
	vector<string> newSequences(sequences.size() + 1, "");
	int i = sequenceLength, j = profileLength;
	while (i >= 1 || j >= 1)
	{
		if (directionTable[i][j] == 'd')
		{
			for (int k = 0; k < sequences.size(); k++)
			{
				newSequences[k].insert(0, 1, sequences[k].at(j - 1));
			}
			newSequences[sequences.size()].insert(0, 1, mainSequence.at(i - 1));
			i--;
			j--;
		}
		else if (directionTable[i][j] == 'u')
		{
			for (int k = 0; k < sequences.size(); k++)
			{
				newSequences[k].insert(0, 1, '-');
			}
			newSequences[sequences.size()].insert(0, 1, mainSequence.at(i - 1));
			i--;
		}
		else if (directionTable[i][j] == 'l')
		{
			for (int k = 0; k < sequences.size(); k++)
			{
				newSequences[k].insert(0, 1, sequences[k].at(j - 1));
			}
			newSequences[sequences.size()].insert(0, 1, '-');
			j--;
		}
		else
		{
			cout << "val: " << directionTable[i][j] << ", i: " << i << ", j: " << j << endl;
			cout << "Error while backtracking." << endl;
		}
	}

	return newSequences;
}