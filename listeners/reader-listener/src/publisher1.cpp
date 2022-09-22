#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <algorithm>
/* Include the C++ DDS API. */
#include "dds/dds.hpp"

/* Include data type and specific traits to be used with the C++ DDS API. */
#include "Data.hpp"
#include "init.cpp"

#include "myFunctions.hpp"

using namespace org::eclipse::cyclonedds;
using namespace std;



int main()
{
    try
    {
        std::cout << "=== [Publisher] Create writer." << std::endl;
        dds::pub::DataWriter<HelloWorldData::Msg>  writer =  init_publisher();
      

        // pick a random message to publish

        std::fstream myFile;
        myFile.open("../data/words.txt");

        int counter = 1;
        const int userID = 1;
        bool publish = true;
        while (publish && counter != 20)
        {
            // pick a random message to publish
            std::string message = random_message("../data/words.txt");

            /* Create a message to write. */
            HelloWorldData::Msg msg(userID, message, counter);

            /* Write the message. */
            std::cout << "=== [Publisher] Write sample " << counter << " (" << userID << ", " << message << ")" << std::endl;
            writer.write(msg);
            std::thread::id this_id = std::this_thread::get_id();
            std::cout << "=== [Publisher] " << this_id << std::endl;
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }

    catch (const dds::core::Exception &e)
    {
        std::cerr << "=== [Publisher] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "=== [Publisher] Done." << std::endl;

    return EXIT_SUCCESS;
}
