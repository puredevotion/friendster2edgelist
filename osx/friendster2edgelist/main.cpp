//
//  main.cpp
//  friendster
//
//  Created by Thijs Baars on 19-02-13.
//  Copyright (c) 2013 Webbed Intelligence. All rights reserved.
//
#include <unistd.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <errno.h>

using std::cin; using std::cout; using std::endl; using std::string;
using std::setprecision; using std::streamsize;
using namespace std;

int main() {
	 //// Current Dir
	 // get dir. if not argv[0], then input the dir path
	 //
	 char cCurrentPath[FILENAME_MAX];
	 if (!getcwd(cCurrentPath, sizeof(cCurrentPath))) {return errno;}
	 
	 // ask for a file
	 // count all files in dir.
	 // ask for prefix (default friends-)
	 // ask for default postfix (______.txt)
Start:
	 cout << "executing this from the same dir as the friends files?" << endl;
	 cout << "current dir.: " << cCurrentPath <<endl;
	 getchar();
	 
	 string line;
	 ifstream myfile;int k;
	 for(k=0;k<124;k++){
		  string fileName="friends-";
		  
		  stringstream ss; ss << setw(3) << setfill('0') << k;
		  fileName = fileName+ss.str()+"______.txt";
		  
		  myfile.open(fileName);
		  cout << "opening " + fileName +"..." << endl;
		  if (myfile.is_open()) {
				// count # of lines
				int c = count(istreambuf_iterator<char>(myfile), istreambuf_iterator<char>(), '\n') + 1;
				
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
								
								while(comma!=string::npos) {				// there are comma's left...
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
	 getchar();
	 return 0;
}