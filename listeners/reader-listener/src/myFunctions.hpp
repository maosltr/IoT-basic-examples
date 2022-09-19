#include <time.h>

// functions that returns a random word from a dictionary.
std::string random_message(std::string dict)

{
    std::string message;
    std::fstream myFile;
    myFile.open(dict);
    srand(time(NULL));
    int randomline = 1 + (rand() % 450000);
    int linenumber = 0;

    while (linenumber != randomline)
    {
        getline(myFile, message);

        linenumber++;
    }

    message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());

    return message;
};
