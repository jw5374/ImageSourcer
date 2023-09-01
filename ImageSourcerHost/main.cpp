// Taken from https://stackoverflow.com/questions/26582584/chrome-native-host-in-c-cannot-communicate-with-chrome
// Probably needs cleanup or something

#include <exception>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <memory>
#include <stdint.h>
#include <string>

/**
 * This was a pain and I'd probably need some help understanding why the compiled executable needs the compiler in the system path to successfully run
 * The library apparently brings in something else from the standard library even though it's just a single header file
 * If the compiler is not in system path, program will exit with code 0xc0000139 which apparently means compiled file is misconfigured/missing dll's??
 * Working around by simply compiling a static binary
 * Only other result for this problem: https://stackoverflow.com/questions/71632731/error-when-trying-to-run-code-using-nlohmann-json-library-in-visual-studio-code
 **/
#include "nlohmann/json.hpp" // from https://github.com/nlohmann/json

using namespace std;

using json = nlohmann::json;

int main() {
	_setmode(_fileno(stdin),_O_BINARY); // from bkdc answer https://stackoverflow.com/questions/20220668/communication-between-native-app-and-chrome-extension

	ofstream logs;
	logs.open("logs.txt", ios::app);
	bool terminate = false;
	logs << "Starting... \n" << flush;

	try {
		while(1) {
			if(cin.peek() == -1) {
				logs << "Closing... " << endl;
				break;
			}

			//read the first four bytes (=> Length)
			/*for (int i = 0; i < 4; i++)
			{
				int read_char = getchar();
				length += read_char * (int) pow(2.0, i*8);
				string s = to_string((long long)read_char) + "\n";
				fwrite(s.c_str(), sizeof(char), s.size(), f);
				fflush(f);
			}*/

			//Neat way!
			uint32_t length;
			cin.read(reinterpret_cast<char*>(&length), 4); // we can read specific number of bytes from istream without writing loop
			logs << length << endl;

			// read the json-message (we can do something with this msg now)
			char* msg = new char[length+1];
			cin.read(msg, length);
			msg[length] = '\0';

			// parsing json
			// more docs at: https://json.nlohmann.me/api/basic_json/
			// or visit the repository README
			json msgJson = json::parse(msg);

			// Chrome extension background.js has the json format in message
			logs << setw(4) << msgJson << endl; // for formatted json
			logs << msgJson["imgUrl"] << endl;

			// Instantiate message and length
			string message;
			uint32_t len;

			// Now we can output our message
			if (strcmp(msg, "{\"text\":\"#STOP#\"}") == 0) {
				message = "{\"text\":\"EXITING...\"}";
				len = message.length();
				cout.write(reinterpret_cast<char*>(&len), 4); 
				cout.write(reinterpret_cast<char*>(&message), len); 
				cout.flush(); // stdout for chrome response

				logs << message << endl;
				break;
			}

			// return stdin message
			// this would have encoded the 4byte length information for response: logs << char(len>>0) << char(len>>8) << char(len>>16) << char(len>>24);
			len = length;
			cout.write(reinterpret_cast<char*>(&len), 4); 
			cout.write(msg, len); 
			cout.flush(); // stdout for chrome response

			logs << msg << endl;
		}
	} catch (exception &e) {
		logs << "exception: " + string(e.what()) << endl;
	}
    logs.close();
    return 0;
}
