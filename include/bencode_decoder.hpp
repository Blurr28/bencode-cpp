#ifndef BENCODE_DECODER_H
#define BENCODE_DECODER_H

#include "bencode_type.hpp"
#include <stdexcept>
#include <sstream>

namespace bencode {

    class Decoder {
    public:
        explicit Decoder(const std::string& data) : input(data), pos(0) {}

        Value decode();

    private:
        std::string input;
        size_t pos;

        Value decodeValue();
        int decodeInteger();
        std::string decodeString();
        ValueVector decodeList();
        ValueDict decodeDictionary();
    };
}

#endif