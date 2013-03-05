// friendster2edgelist.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <direct.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <shlwapi.h>

using std::cin; using std::cout; using std::endl; using std::string;
using std::setprecision; using std::streamsize;
using namespace std;

string getCurrentDir() {
	// create a buffer larger than the allowed max. pathname
	char executablePath[MAX_PATH+1];

	// get the executable path with a buffer of MAX_PATH characters.
	DWORD result = ::GetModuleFileNameA(nullptr, executablePath, MAX_PATH);

	// If the function returned 0, something went wrong
	if(result == 0) {
		throw std::runtime_error("GetCurrentDir() failed" + errno);
	}

	// cut the executable name and return the path, as a standard string
	string::size_type pos = string(executablePath).find_last_of( "\\/" );
	return string(executablePath).substr(0, pos);
}

int main() {
	// ask for a file
	string prefixFilename="friends-";
	string fileName, fileDir;
Start:
	cout << "Where are your Friendster text files located?" << endl;
	cout << "current directory: " << getCurrentDir() << endl;
	cout << "if in the same directory, press enter" << endl;
	cout << "otherwise, type relative or absolute path" << endl;
	cin >> fileDir;

	// set the path... if no entry than use currentDir
	if(fileDir.empty()) {fileDir = getCurrentDir();}
	
	string line;
	ifstream myfile;int k;

	for(k=0;k<124;k++){
		stringstream ss; 
		ss << setw(3) << setfill('0') << k; 

		fileName = prefixFilename+ss.str()+"______.txt";

		myfile.open(fileName);
		cout << "opening " + fileName +"..." << endl;
		if (myfile.is_open()) { 
			// count # of lines
			int c = std::count(std::istreambuf_iterator<char>(myfile), std::istreambuf_iterator<char>(), '\n') + 1;

			cout << fileName + " successfully opened; has " << c << " lines" << endl; 

			ofstream newFile ("edgelist\\"+fileName);
			cout << "\n created new file in the cleaned dir... \n" << endl;
			if (newFile.is_open())
			{
				while ( myfile.good())
				{
					getline (myfile,line);
					size_t friendsPriv;size_t notFound;size_t oneFriend;

					friendsPriv = line.find("private");
					oneFriend = line.find(",");
					notFound = line.find("notfound");
					char lastitem = line[line.size()-1]; string nofriends = string(1, lastitem); string edgeLine;

					if((nofriends == ":") ||  friendsPriv != string::npos || notFound != string::npos || oneFriend == string::npos){}
					else {
						size_t posIn, posOut, firstComma, comma, prevComma; string nodeIn, nodeOut; int n=0;
						// get node-from
						posIn = line.find(":");
						int posInt = int(posIn);  
						nodeIn = line.substr(0,posInt); 

						// get nodes-to
						comma = line.find_first_of(",");
						posOut = comma;
						prevComma = comma;
						firstComma = posOut;

						while(comma!=string::npos) {		// there are comma's left...
							int commaPosition = int(comma);	// and located at this position 

							if(n==0){
								nodeOut = line.substr(posInt+1,int(firstComma)-posInt-1);
							}
							if(n>0){
								nodeOut = line.substr(prevComma+1,commaPosition-prevComma-1);
							}

							edgeLine = nodeIn+"  "+nodeOut;
							cout << edgeLine << endl;
							newFile << edgeLine << endl;

							prevComma = commaPosition;
							comma = line.find_first_of(",", comma+1);
							n++;
						}
						nodeOut = line.substr(prevComma+1,prevComma-line.size());
						edgeLine = nodeIn+"  "+nodeOut;
						cout << edgeLine << endl;
						newFile << edgeLine << endl;
					}
				}
			}
			else cout << "Unable to open file (not good)" << endl;

			myfile.close();
			newFile.close();
			cout << "edge list creation successful!" << endl;
		}
		else {
			cout << "Unable to open file" << endl;
			goto Start;
		}
	}
	system("PAUSE");
	return 0;
	}