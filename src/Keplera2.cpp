
#include <iostream>

#include "SDLWrap.h"

using namespace std;

int main(int argc, char* args[])
{
	//Open the log files
	cout << "Attempting to open log files..." << endl;

	string fileO = "Keplera2";
	string outFile = fileO + ".log";
	string errFile = fileO + "-error.log";
	freopen(outFile.c_str(), "w", stdout);
	freopen(errFile.c_str(), "w", stderr);

	bool initSuccess = sdl::initSDL();

	try {
		if (initSuccess) {
			
		}
		else {
			cout << "SDL wrapper failed to init SDL, exiting..." << endl;
		}
	}
	catch (const std::exception& e) {
		cout << "Error detected: " << e.what() << endl;
	}
	catch (...) {
		cout << "Error detected: unkown" << endl;
	}

	cout << "Terminating SDL" << endl;

	sdl::terminateSDL();

	return 0;
}
