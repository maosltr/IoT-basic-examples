#include "dds/dds.hpp"

// flags

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

            std::cout << "=== [Publisher] subscriber joined for the topic '" << topic_name << "'" << std::endl;
            pubmatched = true;
        }
        else if (status.total_count_change() == 0)
        {

            std::cout << "=== [Publisher] subscriber left " << std::endl;
            pubmatched = false;
        }
    }
};