/*
 * Copyright(c) 2006 to 2021 ZettaScale Technology and others
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
        std::cout << "=== [Subscriber] Create reader." << std::endl;

        /* First, a domain participant is needed.
         * Create one on the default domain. */
        dds::domain::DomainParticipant participant(domain::default_id());

        /* To subscribe to something, a topic is needed. */
        dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

        /* A reader also needs a subscriber. */
        dds::sub::Subscriber subscriber(participant);

        /* Now, the reader can be created to subscribe to a HelloWorld message. */
        dds::sub::DataReader<HelloWorldData::Msg> reader(subscriber, topic);

        /* Poll until a message has been read.
         * It isn't really recommended to do this kind wait in a polling loop.
         * It's done here just to illustrate the easiest way to get data.
         * Please take a look at Listeners and WaitSets for much better
         * solutions, albeit somewhat more elaborate ones. */
        std::cout << "=== [Subscriber] Wait for message." << std::endl;
        bool poll = true;
        int polling_counter = 0;
        while (poll && polling_counter < 5)
        {

            /* For this example, the reader will return a set of messages (aka
             * Samples). There are other ways of getting samples from reader.
             * See the various read() and take() functions that are present. */
            dds::sub::LoanedSamples<HelloWorldData::Msg> samples;

            /* Try taking samples from the reader. */
            samples = reader.take();
            dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator it;
            for (it = samples.begin(); it != samples.end(); ++it)
            {
                const HelloWorldData::Msg &msg = it->data();
                // Use sample data and meta information.
                std::cout << "=== [Subscriber] read sample " << msg.counter()
                          << " (" << msg.userID() << ", " + msg.message() << ")" << std::endl;
                polling_counter++;
            }
        }
    }
    catch (const dds::core::Exception &e)
    {
        std::cerr << "=== [Subscriber] DDS exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        std::cerr << "=== [Subscriber] C++ exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "=== [Subscriber] Done." << std::endl;

    return EXIT_SUCCESS;
}
