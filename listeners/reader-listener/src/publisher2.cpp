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

#include "myFunctions.hpp"

using namespace org::eclipse::cyclonedds;

int main()
{
    try
    {
        std::cout << "=== [Publisher] Create writer." << std::endl;

        /* First, a domain participant is needed.
         * Create one on the default domain. */
        dds::domain::DomainParticipant participant(domain::default_id());

        /* To publish something, a topic is needed. */
        dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

        /* A writer also needs a publisher. */
        dds::pub::Publisher publisher(participant);

        /* Now, the writer can be created to publish a HelloWorld message. */
        dds::pub::DataWriter<HelloWorldData::Msg> writer(publisher, topic);

        /* For this example, we'd like to have a subscriber to actually read
         * our message. This is not always necessary. Also, the way it is
         * done here is just to illustrate the easiest way to do so. It isn't
         * really recommended to do a wait in a polling loop, however.
         * Please take a look at Listeners and WaitSets for much better
         * solutions, albeit somewhat more elaborate ones. */

        // pick a random message to publish

        
        std::fstream myFile;
        myFile.open("../data/words.txt");

        int counter = 1;
        const int userID = 2;
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
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(2100));
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
