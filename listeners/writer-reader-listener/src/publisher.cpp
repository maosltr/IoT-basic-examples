/*
 * Copyright(c) 2006 to 2020 ZettaScale Technology and others
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License v. 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
 * v. 1.0 which is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
 */
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

#include "listener.hpp"

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

        /* a Mask is needed for the datawriter listener */
        dds::core::status::StatusMask mask;
        // mask << dds::core::status::StatusMask::publication_matched();
        mask << dds::core::status::StatusMask::all();

        /* create a listener */
        DwListener dwlistener;

        /* Now, the writer can be created to publish a HelloWorld message. */
        dds::pub::DataWriter<HelloWorldData::Msg> writer(publisher, topic, publisher.default_datawriter_qos(), &dwlistener, mask);

        /* For this example, we'd like to have a subscriber to actually read
         * our message. This is not always necessary. Also, the way it is
         * done here is just to illustrate the easiest way to do so. It isn't
         * really recommended to do a wait in a polling loop, however.
         * Please take a look at Listeners and WaitSets for much better
         * solutions, albeit somewhat more elaborate ones. */

        // pick a random message to publish

        std::string message;
        std::fstream myFile;
        myFile.open("../data/words.txt");

        int counter = 0;
        bool publish = true;
        while (publish && counter < 30)
        {
            int randomline = 1 + (rand() % 1000);
            int linenumber = 0;

            while (linenumber != randomline)
            {
                getline(myFile, message);

                linenumber++;
            }
            message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());

            /* Create a message to write. */
            HelloWorldData::Msg msg(1, message, counter);

            /* Write the message if publication matched. */

            if (dwlistener.pubmatched)
            {
                std::cout << "=== [Publisher] Write sample " << counter << " (1, " << message << ")" << std::endl;
                writer.write(msg);
                counter++;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
