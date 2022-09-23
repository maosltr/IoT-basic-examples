
#include "dds/dds.hpp"
#include "listener.hpp"
using namespace org::eclipse::cyclonedds;
using namespace std;

// publisher
class Publisher
{
public:
    void init();
    int publish();

private:
    shared_ptr<dds::pub::DataWriter<HelloWorldData::Msg>> writer_;
};

void Publisher::init()
{
    std::cout << "=== [Publisher] Publish a random world periodically." << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());
    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");
    dds::pub::Publisher publisher(participant);
    writer_ = make_shared<dds::pub::DataWriter<HelloWorldData::Msg>>(dds::pub::DataWriter<HelloWorldData::Msg>(publisher, topic));
}

// subscriber // data reader listener
class Subscriber_data_reader_listener
{
public:
    void init();
    int subscribe();

    DrListener drlistener;
    dds::core::status::StatusMask mask;

private:
    shared_ptr<dds::sub::DataReader<HelloWorldData::Msg>> reader_;
};

void Subscriber_data_reader_listener::init()
{

    std::cout << "=== [Subscriber] Subscribe using a data reader listener" << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());
    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");
    dds::sub::Subscriber subscriber(participant);

    // (source: ..\include\ddscxx\dds\core\status\State.hpp)
    mask << dds::core::status::StatusMask::subscription_matched();
    // mask << dds::core::status::StatusMask::data_available();
    //  mask << dds::core::status::StatusMask::all();

    reader_ = make_shared<dds::sub::DataReader<HelloWorldData::Msg>>(dds::sub::DataReader<HelloWorldData::Msg>(subscriber, topic, subscriber.default_datareader_qos(), &drlistener, mask));
};

// subscriber // subscriber listener
class Subscriber_subscriber_listener
{
public:
    void init();
    int subscribe();

    SubListener sublistener;
    dds::core::status::StatusMask mask;

private:
    shared_ptr<dds::sub::DataReader<HelloWorldData::Msg>> reader_;
};

void Subscriber_subscriber_listener::init()
{

    std::cout << "=== [Subscriber] Subscribe using a subscriber listener" << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());
    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");
    // (source: ..\include\ddscxx\dds\core\status\State.hpp)
    mask << dds::core::status::StatusMask::subscription_matched();
    // mask << dds::core::status::StatusMask::data_available();
    dds::sub::Subscriber subscriber(participant,
                                    participant.default_subscriber_qos(),
                                    &sublistener,
                                    mask);

    reader_ = make_shared<dds::sub::DataReader<HelloWorldData::Msg>>(dds::sub::DataReader<HelloWorldData::Msg>(subscriber, topic));
};