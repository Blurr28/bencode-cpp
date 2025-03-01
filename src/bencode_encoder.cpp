#include "../include/bencode_encoder.hpp"
#include "../include/bencode_type.hpp"

namespace bencode {
    
    std::string Encoder::encode(const Value& value) {
        struct EncoderVisitor : public boost::static_visitor<std::string> {
            Encoder& encoder;
            explicit EncoderVisitor(Encoder& enc) : encoder(enc) {}

            std::string operator()(int val) const {
                return encoder.encodeInteger(val);
            }

            std::string operator()(const std::string& str) const {
                return encoder.encodeString(str);
            }

            std::string operator()(const ValueVector& list) const {
                return encoder.encodeList(list);
            }

            std::string operator()(const ValueDict& dict) const {
                return encoder.encodeDictionary(dict);
            }
        };

        return boost::apply_visitor(EncoderVisitor(*this), value);
    }

    std::string Encoder::encodeInteger(int value) {
        return "i" + std::to_string(value) + "e";
    }

    std::string Encoder::encodeString(const std::string& value) {
        return std::to_string(value.size()) + ":" + value;
    }

    std::string Encoder::encodeList(const ValueVector& list) {
        std::string result = "l";
        for (const auto& item : list){
            result += encode(item);
        }
        result += "e";
        return result;
    }

    std::string Encoder::encodeDictionary(const ValueDict& dict) {
        std::string result = "d";
        for (const auto& pair : dict) {
            result += encodeString(pair.first);
            result += encode(pair.second);
        }
        result += "e";
        return result;
    }
}