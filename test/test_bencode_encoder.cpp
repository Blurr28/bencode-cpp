#include "../include/bencode_encoder.hpp"
#include <iostream>

int main() {
    bencode::Encoder encoder;

    bencode::ValueDict dict;
    dict["announce"] = std::string("http://tracker.com/announce");
    dict["length"] = 1234;

    bencode::ValueVector list;
    list.push_back(1);
    list.push_back(std::string("file.txt"));
    list.push_back(dict);

    bencode::Value root = list;

    std::string encoded = encoder.encode(root);
    std::cout << encoded << std::endl;

    return 0;
}