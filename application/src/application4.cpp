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
#include "init.hpp"
//#include "listener.hpp"

using namespace org::eclipse::cyclonedds;
using namespace std;

int Subscriber_data_reader_listener::subscribe()
{
    try
    {

        auto reader = *reader_;

        int topics_counter = 0;
        while (topics_counter < 100)
        {

            dds::sub::LoanedSamples<HelloWorldData::Msg> samples;

            /* Try taking samples from the reader. */
            samples = reader.take();

            dds::sub::LoanedSamples<HelloWorldData::Msg>::const_iterator it;
            for (it = samples.begin(); it != samples.end(); ++it)
            {

                const HelloWorldData::Msg &msg = it->data();
                const dds::sub::SampleInfo &info = it->info();
                if (info.valid())
                {

                    // Use sample data and meta information.

                    std::thread::id this_id = std::this_thread::get_id();
                    std::cout << "== [Application4" << "/s" << msg.counter() << "] | " << msg.message() << " | " << getpid() << "/" << this_id << std::endl;

                    // std::cout << "=== [Subscriber] read sample " << msg.counter()
                    //           << " (" << msg.userID() << ", " + msg.message() << ")" << std::endl;
                    topics_counter++;
                }
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

int main()
{

    Subscriber_data_reader_listener application4;
    application4.init();
    application4.subscribe();
    return 0;
}
