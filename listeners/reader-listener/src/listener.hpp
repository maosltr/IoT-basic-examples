#include "dds/dds.hpp"

// data writer listener for a specific topic (source: \include\ddscxx\dds\pub\DataWriterListener.hpp)
class DwListener : public virtual dds::pub::DataWriterListener<HelloWorldData::Msg>
{
public:
    bool pubmatched = false;

    virtual void on_offered_deadline_missed(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        std::cout << "=== [Publisher] on_offered_deadline_missed" << std::endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        std::cout << "=== [Publisher] on_offered_incompatible_qos" << std::endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        std::cout << "=== [Publisher] on_liveliness_lost" << std::endl;
    }

    virtual void on_publication_matched(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        std::cout << "=== [Publisher] on_publication_matched" << std::endl;
        const std::string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            std::cout << "=== [Publisher - data writer listener] subscriber joined for the topic '" << topic_name << "'" << std::endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            std::cout << "=== [Publisher - data writer listener] subscriber left " << std::endl;
            pubmatched = false;
        }
    }
};

// publisher listener for any topic (source: include\ddscxx\dds\pub\PublisherListener.hpp)
class PubListener : public virtual dds::pub::PublisherListener
{
public:
    bool pubmatched = false;
    virtual void on_offered_deadline_missed(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        std::cout << "on_offered_deadline_missed" << std::endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        std::cout << "on_offered_incompatible_qos" << std::endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        std::cout << "on_liveliness_lost" << std::endl;
    }

    virtual void on_publication_matched(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        std::cout << "=== [Publisher] on_publication_matched" << std::endl;
        const std::string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            std::cout << "=== [Publisher - publisher listener] subscriber joined for the topic '" << topic_name << "'" << std::endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            std::cout << "=== [Publisher - publisher listener] subscriber left " << std::endl;
            pubmatched = false;
        }
    }
};

// domain participant listener for any topic (source: include\ddscxx\dds\domain\DomainParticipantListener.hpp)
class DpListener : public virtual dds::domain::DomainParticipantListener
{
public:
    bool pubmatched = false;
    virtual void on_inconsistent_topic(
        dds::topic::AnyTopic &topic,
        const dds::core::status::InconsistentTopicStatus &status)
    {
        std::cout << "on_inconsistent_topic" << std::endl;
    }

    virtual void on_offered_deadline_missed(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        std::cout << "on_offered_deadline_missed" << std::endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        std::cout << "on_offered_incompatible_qos" << std::endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        std::cout << "on_liveliness_lost" << std::endl;
    }

    virtual void on_publication_matched(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        std::cout << "=== [Publisher] on_publication_matched" << std::endl;
        const std::string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            std::cout << "=== [Publisher - domain participant listener] subscriber joined for the topic '" << topic_name << "'" << std::endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            std::cout << "=== [Publisher - domain participant listener] subscriber left " << std::endl;
            pubmatched = false;
        }
    }

    virtual void on_requested_deadline_missed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        std::cout << "on_requested_deadline_missed" << std::endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        std::cout << "on_requested_incompatible_qos" << std::endl;
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "on_sample_rejected" << std::endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "on_liveliness_changed" << std::endl;
    }

    virtual void on_data_available(
        dds::sub::AnyDataReader &reader)
    {
        std::cout << "on_data_available" << std::endl;
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "on_subscription_matched" << std::endl;
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "on_sample_lost" << std::endl;
    }

    virtual void on_data_on_readers(
        dds::sub::Subscriber &subs)
    {
        std::cout << "on_data_on_readers" << std::endl;
    }
};

// data reader listener for a specific topic (source: \include\ddscxx\dds\sub\DataReaderListener.hpp)
class DrListener : public virtual dds::sub::DataReaderListener<HelloWorldData::Msg>
{
public:
    bool submatched = false;
    bool data_available = false;
    virtual void on_requested_deadline_missed(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        std::cout << "on_requested_deadline_missed" << std::endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        std::cout << "on_requested_incompatible_qos" << std::endl;
    }

    virtual void on_sample_rejected(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "on_sample_rejected" << std::endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "on_liveliness_changed" << std::endl;
    }

    virtual void on_data_available(
        dds::sub::DataReader<HelloWorldData::Msg> &reader)
    {
        std::cout << "=== [Subscriber] on_data_available" << std::endl;
        data_available = true;
    }

    virtual void on_subscription_matched(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "=== [Subscriber] on_subscription_matched" << std::endl;
        const std::string topic_name = reader.topic_description().name();

        if (status.total_count_change() == 1)
        {

            std::cout << "=== [Subscriber - data reader listener] publisher joined for the topic '" << topic_name << "'" << std::endl;
            submatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            std::cout << "=== [Subscriber - data reader listener] publisher left " << std::endl;
            submatched = false;
        }
    }

    virtual void on_sample_lost(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "on_sample_lost" << std::endl;
    }
};

// subscriber listener for aany topic (source: \include\ddscxx\dds\sub\SubscriberListener.hpp)
class SubListener : public virtual dds::sub::SubscriberListener
{
public:
    bool submatched = false;
    virtual void on_requested_deadline_missed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        std::cout << "on_requested_deadline_missed" << std::endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        std::cout << "on_requested_incompatible_qos" << std::endl;
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        std::cout << "on_sample_rejected" << std::endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        std::cout << "on_liveliness_changed" << std::endl;
    }

    virtual void on_data_available(
        dds::sub::AnyDataReader &reader)
    {
        std::cout << "on_data_available" << std::endl;
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        std::cout << "=== [Subscriber] on_subscription_matched" << std::endl;
        const std::string topic_name = reader.topic_description().name();
 
        std::cout << "=== [Subscriber - subscriber listener] " << status.current_count() << " publisher(s) for the topic '" << topic_name << "'" << std::endl;
        std::thread::id this_id = std::this_thread::get_id(); 
        std::cout << "=== [Subscriber - subscriber listener] " << this_id << std::endl;
       
        // source: \include\ddscxx\dds\core\status\detail\TStatusImpl.hpp
        if (status.current_count() != 0)
        {
            submatched = true;
        }
        else if (status.current_count() == 0)
        {
            submatched = false;
        }
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        std::cout << "on_sample_lost" << std::endl;
    }

    virtual void on_data_on_readers(
        dds::sub::Subscriber &subs)
    {
        std::cout << "on_data_on_readers" << std::endl;
    }
};
