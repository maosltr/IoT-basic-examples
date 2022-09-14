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
#include "myFunctions.hpp"

/* Include data type and specific traits to be used with the C++ DDS API. */
#include "Data.hpp"

#include "listener.hpp"

using namespace org::eclipse::cyclonedds;

int main()
{
    try
    {
        std::cout << "=== [Publisher] Create writer." << std::endl;

        /* create a domain participant listener */
        DpListener dplistener;

        /* a Mask is needed for the domain participant listener */
        dds::core::status::StatusMask mask;
        mask << dds::core::status::StatusMask::publication_matched();

        /* First, a domain participant is needed.
         * Create one on the default domain. */
        dds::domain::DomainParticipant participant(domain::default_id());

        /* To publish something, a topic is needed. */
        dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

        /* A writer also needs a publisher. */
        dds::pub::Publisher publisher(participant, participant.default_publisher_qos(), &dplistener, mask);

        /* Now, the writer can be created to publish a HelloWorld message. */
        dds::pub::DataWriter<HelloWorldData::Msg> writer(publisher, topic);

        /* For this example, we'd like to have a subscriber to actually read
         * our message. This is not always necessary. Also, the way it is
         * done here is just to illustrate the easiest way to do so. It isn't
         * really recommended to do a wait in a polling loop, however.
         * Please take a look at Listeners and WaitSets for much better
         * solutions, albeit somewhat more elaborate ones. */

        int counter = 0;
        bool publish = true;
        while (publish && counter < 30)
        {
            // pick a random message to publish
            std::string message = random_message("../data/words.txt");

            /* Create a message to write. */
            HelloWorldData::Msg msg(1, message, counter);

            /* Write the message if publication matched. */
            if (dplistener.pubmatched)
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
