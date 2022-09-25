#include "dds/dds.hpp"
#include "Data.hpp"
#include "listener.hpp"

using namespace org::eclipse::cyclonedds;
using namespace std;

// only applications in the same partition can communicate with each other
struct {
  const char *swc1 = "p1";
  const char *swc2 = "p2";
  const char *swc3 = "p1";
  const char *swc4 = "p2";
} partitions;

// swc1
class Publisher1
{
public:
    void init();
    int publish();
    dds::pub::qos::PublisherQos pQos;

private:
    shared_ptr<dds::pub::DataWriter<HelloWorldData::Msg>>
        writer_;
};

void Publisher1::init()
{
    std::cout << "=== [Publisher] Publish a random world periodically." << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());
    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

   
    pQos = participant.default_publisher_qos();
    pQos << dds::core::policy::Partition(partitions.swc1);

    dds::pub::Publisher publisher(participant, pQos);
    writer_ = make_shared<dds::pub::DataWriter<HelloWorldData::Msg>>(dds::pub::DataWriter<HelloWorldData::Msg>(publisher, topic));
}

// swc2
class Publisher2
{
public:
    void init();
    int publish();
    dds::pub::qos::PublisherQos pQos;


private:
    shared_ptr<dds::pub::DataWriter<HelloWorldData::Msg>> writer_;
};

void Publisher2::init()
{
    std::cout << "=== [Publisher] Publish a random world periodically." << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());

    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

    pQos = participant.default_publisher_qos();
    pQos << dds::core::policy::Partition(partitions.swc2);

    dds::pub::Publisher publisher(participant, pQos);
    writer_ = make_shared<dds::pub::DataWriter<HelloWorldData::Msg>>(dds::pub::DataWriter<HelloWorldData::Msg>(publisher, topic));
}

// swc3 (Subscriber Listener & Data Reader QoS & Subscriber QoS)
class Subscriber_subscriber_listener
{
public:
    void init();
    int subscribe();

    SubListener sublistener;
    dds::core::status::StatusMask mask;
    dds::sub::qos::DataReaderQos drQos;
    dds::sub::qos::SubscriberQos sQos;

private:
    shared_ptr<dds::sub::DataReader<HelloWorldData::Msg>> reader_;
};

void Subscriber_subscriber_listener::init()
{
    
    std::cout << "=== [Subscriber] Subscribe using a subscriber listener" << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());

    sQos = participant.default_subscriber_qos();
    sQos << dds::core::policy::Partition(partitions.swc3);


    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");

    // (@ref: State.hpp)
    mask << dds::core::status::StatusMask::subscription_matched();
    // mask << dds::core::status::StatusMask::data_available();
    dds::sub::Subscriber subscriber(participant,
                                    //participant.default_subscriber_qos(),
                                    sQos,
                                    &sublistener,
                                    mask);

    // (@ref: DataReaderQos.hpp & TCorePolicy.hpp && TSubscriberImpl.hpp)
    drQos = subscriber.default_datareader_qos();
    drQos << dds::core::policy::Reliability::Reliable()
          << dds::core::policy::Durability::Volatile()
          << dds::core::policy::History::KeepAll();
    //<< dds::core::policy::ResourceLimits(10, 1, 1);

    reader_ = make_shared<dds::sub::DataReader<HelloWorldData::Msg>>(dds::sub::DataReader<HelloWorldData::Msg>(subscriber, topic, drQos));
};

// swc4 (Data Reader Listener & Topic QoS & Subscriber QoS)
class Subscriber_data_reader_listener
{
public:
    void init();
    int subscribe();

    DrListener drlistener;
    dds::core::status::StatusMask mask;
    dds::topic::qos::TopicQos tQos;
    dds::sub::qos::SubscriberQos sQos;

private:
    shared_ptr<dds::sub::DataReader<HelloWorldData::Msg>> reader_;
};

void Subscriber_data_reader_listener::init()
{

    std::cout << "=== [Subscriber] Subscribe using a data reader listener" << std::endl;
    dds::domain::DomainParticipant participant(domain::default_id());

    sQos = participant.default_subscriber_qos();
    sQos << dds::core::policy::Partition(partitions.swc4);

    dds::sub::Subscriber subscriber(participant, sQos);

    // (@ref: TopicQos.hpp & TCorePolicy.hpp && TDomainParticipantImpl.hpp)
    tQos = participant.default_topic_qos();
    tQos << dds::core::policy::Reliability::Reliable()
          << dds::core::policy::Durability::Volatile()
          << dds::core::policy::History::KeepAll();

    dds::topic::Topic<HelloWorldData::Msg> topic(participant, "random_world");//, tQos);

    

    // (source: ..\include\ddscxx\dds\core\status\State.hpp)
    mask << dds::core::status::StatusMask::subscription_matched();
    // mask << dds::core::status::StatusMask::data_available();
    //  mask << dds::core::status::StatusMask::all();

    reader_ = make_shared<dds::sub::DataReader<HelloWorldData::Msg>>(dds::sub::DataReader<HelloWorldData::Msg>(subscriber, topic, subscriber.default_datareader_qos(), &drlistener, mask));
};
