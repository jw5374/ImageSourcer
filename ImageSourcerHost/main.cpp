// Taken from https://stackoverflow.com/questions/26582584/chrome-native-host-in-c-cannot-communicate-with-chrome
// Probably needs cleanup or something

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string oneLine = "";

	ofstream logs;
	logs.open("logs.txt", ios::app);
	bool terminate = false;

    while (1){
        unsigned int length = 0;

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
        for (int i = 0; i < 4; i++)
        {
            unsigned int read_char = getchar();
			if(read_char == -1) { // chrome sends signal -1 when closed, so we check to close the host process
				logs << "closed\n" << flush;
				terminate = true;
				break;
			}
            length = length | (read_char << i*8);
        }

		if(terminate) {
			break;
		}

        //read the json-message
        string msg = "";
        for (int i = 0; i < length; i++)
        {
            msg += getchar();
        }

        string message = "{\"text\":\"This is a response message\"}";
        // Collect the length of the message
        unsigned int len = message.length();

        // Now we can output our message
        if (msg == "{\"text\":\"#STOP#\"}"){
            message = "{\"text\":\"EXITING...\"}";
            len = message.length();

            logs   << char(len>>0)
                        << char(len>>8)
                        << char(len>>16)
                        << char(len>>24);

            logs << message;
            break;
        }
        
        // return stdin message
        len = length;
        logs   << char(len>>0)
                    << char(len>>8)
                    << char(len>>16)
                    << char(len>>24);

        logs << msg + "\n" << flush;

        // return response message
        // cout    << char(len>>0)
        //          << char(len>>8)
        //          << char(len>>16)
        //          << char(len>>24);
        //  
        // cout << message << flush;
    }
    logs.close();
    return 0;
}
