
#include "dds/dds.hpp"
#include "listener.hpp"
using namespace org::eclipse::cyclonedds;


// init publisher
dds::pub::DataWriter<HelloWorldData::Msg> init_publisher()
{
    std::cout << "=== [Subscriber] Create writer." << std::endl;

    dds::domain::DomainParticipant participant(domain::default_id());
    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");
    dds::pub::Publisher publisher(participant);
    dds::pub::DataWriter<HelloWorldData::Msg> writer(publisher, topic);

    return writer;
};


