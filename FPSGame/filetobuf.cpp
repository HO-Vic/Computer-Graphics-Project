#pragma once
#include "filetobuf.h"
using namespace std;
char* filetobuf(const string filename)
{
	ifstream inFile(filename, ios::binary);
	vector<char> buf;
	buf.resize(0);
	char temp;
	while (inFile >> noskipws >> temp) {
		buf.push_back(temp);
	}
	buf.push_back(0);
	inFile.close();
	char* resultC = new char[buf.size()];
	for (int i = 0; i < buf.size(); i++)
		resultC[i] = buf[i];
	return resultC;
}
