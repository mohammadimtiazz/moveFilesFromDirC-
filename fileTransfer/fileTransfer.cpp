// fileTransfer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream> 

using namespace std;



// Chck specfc fle extension
bool has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}





int main()
{
	string line;
	int result;
	ifstream inFile("D:/Eyelock/CrossMatching/Novetta/dirNames.txt");		// here the folder pathname will be read from 
	//"D:\Eyelock\CrossMatching\Novetta\dirNames.txt"
	int index = 0;
	while(getline(inFile, line))
	{
		//output directory
		string copyDir = "D:/Eyelock/CrossMatching/Novetta/sorted";

		char currentDir[500];
		char outputDir[500];
		//print reading path from txt
		cout << line.length() << endl;

		line.erase(line.begin());		//erase first "
		line.erase(line.end()-1);		//erase last "


		strcpy(currentDir, line.c_str());	//cast string to char
		strcat(currentDir, "/");			// put slash sign

		strcpy(outputDir, copyDir.c_str());
		strcat(outputDir, "/");

		//print the modified directory
		cout << currentDir << endl;
		
		DIR *dir = opendir(currentDir);

		// if directory doesn't exist
		if(!dir)
		{
			return 1;
		}

		dirent *entry;
		while((entry = readdir(dir))!=NULL) // if exist 
		{
			if(has_suffix(entry->d_name, ".pgm"))	// if find extension
			{
				cout << entry->d_name << endl;
				strcat(currentDir, entry->d_name);	//add the extension name in the current diectory
				
				char buffer[500];
				itoa (index,buffer,10);
				strcat(outputDir, buffer);			// addd a number for sorting uses
				strcat(outputDir, entry->d_name);	//add the extension name in the output diectory

				// print output directory
				cout << outputDir << endl;

				result= rename( currentDir , outputDir );	// move to the new path using rename function

				if ( result == 0 )
					puts ( "File successfully renamed" );
				else
					perror( "Error renaming file" );

				// restrt
				memset(currentDir, 0 , 500);
				memset(outputDir, 0 , 500);

				// put back the original current and output directory
				strcpy(currentDir, line.c_str());
				strcat(currentDir, "/");

				strcpy(outputDir, copyDir.c_str());
				strcat(outputDir, "/");
			}
		}
		index++;
		closedir(dir);

	}

}
