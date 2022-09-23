#include "dds/dds.hpp"

using namespace std;

// data writer listener for a specific topic (source: \include\ddscxx\dds\pub\DataWriterListener.hpp)
class DwListener : public virtual dds::pub::DataWriterListener<HelloWorldData::Msg>
{
public:
    bool pubmatched = false;

    virtual void on_offered_deadline_missed(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        cout << "=== [Publisher] on_offered_deadline_missed" << endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        cout << "=== [Publisher] on_offered_incompatible_qos" << endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        cout << "=== [Publisher] on_liveliness_lost" << endl;
    }

    virtual void on_publication_matched(
        dds::pub::DataWriter<HelloWorldData::Msg> &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        cout << "=== [Publisher] on_publication_matched" << endl;
        const string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            cout << "=== [Publisher - data writer listener] subscriber joined for the topic '" << topic_name << "'" << endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            cout << "=== [Publisher - data writer listener] subscriber left " << endl;
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
        cout << "on_offered_deadline_missed" << endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        cout << "on_offered_incompatible_qos" << endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        cout << "on_liveliness_lost" << endl;
    }

    virtual void on_publication_matched(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        cout << "=== [Publisher] on_publication_matched" << endl;
        const string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            cout << "=== [Publisher - publisher listener] subscriber joined for the topic '" << topic_name << "'" << endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            cout << "=== [Publisher - publisher listener] subscriber left " << endl;
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
        cout << "on_inconsistent_topic" << endl;
    }

    virtual void on_offered_deadline_missed(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedDeadlineMissedStatus &status)
    {
        cout << "on_offered_deadline_missed" << endl;
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::OfferedIncompatibleQosStatus &status)
    {
        cout << "on_offered_incompatible_qos" << endl;
    }

    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::LivelinessLostStatus &status)
    {
        cout << "on_liveliness_lost" << endl;
    }

    virtual void on_publication_matched(
        dds::pub::AnyDataWriter &writer,
        const dds::core::status::PublicationMatchedStatus &status)
    {
        cout << "=== [Publisher] on_publication_matched" << endl;
        const string topic_name = writer.topic_description().name();

        if (status.total_count_change() == 1)
        {

            cout << "=== [Publisher - domain participant listener] subscriber joined for the topic '" << topic_name << "'" << endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            cout << "=== [Publisher - domain participant listener] subscriber left " << endl;
            pubmatched = false;
        }
    }

    virtual void on_requested_deadline_missed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedDeadlineMissedStatus &status)
    {
        cout << "on_requested_deadline_missed" << endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        cout << "on_requested_incompatible_qos" << endl;
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        cout << "on_sample_rejected" << endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        cout << "on_liveliness_changed" << endl;
    }

    virtual void on_data_available(
        dds::sub::AnyDataReader &reader)
    {
        cout << "on_data_available" << endl;
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        cout << "on_subscription_matched" << endl;
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        cout << "on_sample_lost" << endl;
    }

    virtual void on_data_on_readers(
        dds::sub::Subscriber &subs)
    {
        cout << "on_data_on_readers" << endl;
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
        cout << "on_requested_deadline_missed" << endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        cout << "on_requested_incompatible_qos" << endl;
    }

    virtual void on_sample_rejected(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        cout << "on_sample_rejected" << endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        cout << "on_liveliness_changed" << endl;
    }

    virtual void on_data_available(
        dds::sub::DataReader<HelloWorldData::Msg> &reader)
    {
        cout << "=== [Subscriber] on_data_available" << endl;
        data_available = true;
    }

    virtual void on_subscription_matched(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        const string topic_name = reader.topic_description().name();
        thread::id this_id = this_thread::get_id();

        if (status.current_count_change() == 1)
        {

            cout << "== [DR-Listener] New publisher joined | " << topic_name << endl;
            cout << "== [DR-Listener] " << getpid() << "/" << this_id << endl;
        }
        else if (status.current_count_change() == -1)
        {

            cout << "== [DR-Listener] One publisher left | " << topic_name << endl;
            cout << "== [DR-Listener] " << getpid() << "/" << this_id << endl;
        }
    }

    virtual void on_sample_lost(
        dds::sub::DataReader<HelloWorldData::Msg> &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        cout << "on_sample_lost" << endl;
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
        cout << "on_requested_deadline_missed" << endl;
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::RequestedIncompatibleQosStatus &status)
    {
        cout << "on_requested_incompatible_qos" << endl;
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleRejectedStatus &status)
    {
        cout << "on_sample_rejected" << endl;
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::LivelinessChangedStatus &status)
    {
        cout << "on_liveliness_changed" << endl;
    }

    virtual void on_data_available(
        dds::sub::AnyDataReader &reader)
    {
        cout << "on_data_available" << endl;
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SubscriptionMatchedStatus &status)
    {
        const string topic_name = reader.topic_description().name();
        thread::id this_id = this_thread::get_id();

        if (status.current_count_change() == 1)
        {

            cout << "== [S-Listener] New publisher joined | " << topic_name << endl;
            cout << "== [S-Listener] " << getpid() << "/" << this_id << endl;
        }
        else if (status.current_count_change() == -1)
        {

            cout << "== [S-Listener] One publisher left | " << topic_name << endl;
            cout << "== [S-Listener] " << getpid() << "/" << this_id << endl;
        }
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader &reader,
        const dds::core::status::SampleLostStatus &status)
    {
        cout << "on_sample_lost" << endl;
    }

    virtual void on_data_on_readers(
        dds::sub::Subscriber &subs)
    {
        cout << "on_data_on_readers" << endl;
    }
};
