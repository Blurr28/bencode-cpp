#ifndef BENCODE_ENCODER_HPP
#define BENCODE_ENCODER_HPP

#include "bencode_type.hpp"
#include <sstream>

namespace bencode {
    class Encoder {
    public: 
        std::string encode(const Value& value);

    private:
        std::string encodeInteger(int value);
        std::string encodeString(const std::string& value);
        std::string encodeList(const ValueVector& list);
        std::string encodeDictionary(const ValueDict& dict);
    };
}

#endif