/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>

#include <ctime>
#include <windows.h>

int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	//char framefoldername[2048] = {"."};
	char framefoldername[2048] = {"c:\\temp"};
	char framefilenameprefix[2048] = {"frame"};
	char framefilenameext[2048] = {"jpg"};
	if(argc>1)
	{
		//first argument 
		strcpy_s(framefoldername, 2048-1, argv[1]);
	}
	if(argc>2)
	{
		//second argument 
		strcpy_s(framefilenameprefix, 2048-1, argv[2]);
	}
	if(argc>3)
	{
		//second argument 
		strcpy_s(framefilenameext, 2048-1, argv[3]);
	}

	/////////////////////////////////////////////
	//execute cmd line to get all frame filenames
	/////////////////////////////////////////////
	string path = framefoldername;
	string quote;
	quote = "\"";
	path = path + "\\" + framefilenameprefix + "*." + framefilenameext;
	string command = "DIR " + quote + path + quote + " /S /B /O:N > filenames.txt";
	//system("DIR *.wav /S /B /O:N > filenames.txt");
	system(command.c_str());

	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> filenames;
	ifstream ifs("filenames.txt");
	string temp;
	while(getline(ifs,temp))
		filenames.push_back(temp);

	int count = filenames.size();

	//////////////////////////////////////////////////////////
	//browse throught filenames and call spipitchdetection.exe
	//////////////////////////////////////////////////////////
	string cmdbuffer;
	char pCharBuffer[64];

	vector<string>::iterator it;	
	int i=0;
	for ( it=filenames.begin() ; it < filenames.end(); it++ )
	{
		i++;
		sprintf_s(pCharBuffer, 64-1, "%06d", i);

		cout << *it << endl; //*it is a frame filename
		cmdbuffer = "rename " + quote + *it + quote + " " + quote + framefilenameprefix + pCharBuffer + "." + framefilenameext + quote;
		cout << cmdbuffer << endl;
		system(cmdbuffer.c_str()); 

		cout << endl << "remaining number of files = " << count-i << endl;
	}	
	return 0;
}