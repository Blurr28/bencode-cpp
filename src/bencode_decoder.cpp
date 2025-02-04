#include "../include/bencode_decoder.hpp"

namespace bencode {

    Value Decoder::decode() {
        return decodeValue();
    }

    Value Decoder::decodeValue(){
        if (pos >= input.size()) throw std::runtime_error("Unexpected end of input\n");

        char c = input[pos];
        if (c == 'i') return decodeInteger();
        if (c == 'l') return decodeList();
        if (c == 'd') return decodeDictionary();
        if (std::isdigit(c)) return decodeString();

        throw std::runtime_error("Invalid Bencode format\n");
    }

    int Decoder::decodeInteger(){
        if (input[pos] != 'i') throw std::runtime_error("Expected 'i' for integer\n"); 
        pos++;

        size_t end = input.find('e', pos);
        if (end == std::string::npos) throw std::runtime_error("Missing 'e' for integer\n");

        int value = std::stoi(input.substr(pos, end - pos));
        pos = end + 1;
        return value;
    }

    std::string Decoder::decodeString() {
        size_t colon = input.find(':', pos);
        if (colon == std::string::npos) throw std::runtime_error("Invalid string format\n");

        int len  = std::stoi(input.substr(pos, colon - pos));
        pos = colon + 1;

        if (pos + len > input.size()) throw std::runtime_error("String exceeds input length\n");

        std::string str = input.substr(pos, len);
        pos += len;
        return str;
    }

    ValueVector Decoder::decodeList() {
        if (input[pos] != 'l') throw std::runtime_error("Expected 'l' for list\n");
        pos++;

        ValueVector list;
        while (input[pos] != 'e'){
            list.push_back(decodeValue());
        }
        pos++;
        return list;
    }

    ValueDict Decoder::decodeDictionary(){
        if (input[pos] != 'd') throw std::runtime_error("Expected 'd' for dictionary\n");
        pos++;

        ValueDict dict;
        while (input[pos] != 'e'){
            std::string key = decodeString();
            Value value = decodeValue();
            dict[key] = value;
        }
        pos++;
        return dict;
    }
}