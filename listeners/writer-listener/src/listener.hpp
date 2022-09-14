#include "dds/dds.hpp"

// flags

// data writer listener for a specific topic
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
class PubListener :
                  public virtual dds::pub::PublisherListener
   {
   public:
       virtual void on_offered_deadline_missed (
           dds::pub::AnyDataWriter& writer,
           const dds::core::status::OfferedDeadlineMissedStatus& status)
       {
           std::cout << "on_offered_deadline_missed" << std::endl;
       }
  
       virtual void on_offered_incompatible_qos (
           dds::pub::AnyDataWriter& writer,
           const dds::core::status::OfferedIncompatibleQosStatus& status)
       {
           std::cout << "on_offered_incompatible_qos" << std::endl;
       }
  
       virtual void on_liveliness_lost (
           dds::pub::AnyDataWriter& writer,
           const dds::core::status::LivelinessLostStatus& status)
       {
           std::cout << "on_liveliness_lost" << std::endl;
       }
  
       virtual void on_publication_matched (
           dds::pub::AnyDataWriter& writer,
           const dds::core::status::PublicationMatchedStatus& status)
       {
           std::cout << "on_publication_matched" << std::endl;
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
