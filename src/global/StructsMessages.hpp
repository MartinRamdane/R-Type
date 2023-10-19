/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** StructsMessages
*/

#ifndef STRUCTSMESSAGES_HPP_
#define STRUCTSMESSAGES_HPP_
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "serialize_tuple.h"
struct SpriteConfig
{
    int id;
    std::tuple <float, float> pos;
    std::string path;
    std::tuple<float, float> scale;
    std::string spriteJsonFileName;
    std::string spriteConfigJsonObjectName;
    float speed;
    std::string direction;
    int damage;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & id & pos & path & scale & spriteJsonFileName &
            spriteConfigJsonObjectName & speed & direction & damage;
    }
};

struct MoveConfig
{
    int id;
    std::tuple <float, float> pos;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & id & pos;
    }
};

struct WindowConfig
{
    std::string title;
    int width;
    int height;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & title & width & height;
    }
};

struct StringConfig
{
    std::string str;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & str;
    }
};

struct ActionConfig
{
    std::string id;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & id;
    }
};

struct InstanceConfig
{
    int id;
    int instanceId;
    int port;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & id & instanceId & port;
    }
};

template <typename T>
class StructsMessages {
public:
    StructsMessages() = default;
    ~StructsMessages() = default;
    std::vector<uint8_t> serialize(const T& data) {
        std::ostringstream oss;
        boost::archive::binary_oarchive oa(oss);
        oa << data;

        std::string serializedData = oss.str();
        return std::vector<uint8_t>(serializedData.begin(), serializedData.end());
    }

    T deserialize(const std::vector<uint8_t>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        boost::archive::binary_iarchive ia(iss);

        T deserializedData;
        ia >> deserializedData;

        return deserializedData;
    }   

protected:
private:
};

#endif /* !STRUCTSMESSAGES_HPP_ */
