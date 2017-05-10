#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()

{

string info = "/n" +username;
	info.append("/t/t"+score+"/n");

	ofstream writer("Leaderboard.txt",ios::app);// ensures existing content wont be overwritten

		if (!writer)
		{
			cout << "ERROR OPENING FILE!" << endl;
			return -1;
		}//if

	writer << info << endl;
	writer.close();
	system("PAUSE");
	return 0;
}