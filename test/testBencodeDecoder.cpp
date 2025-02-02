#include <iostream>
#include <cassert>
#include "../include/BencodeDecoder.hpp"

void testBencodeDecoder(){
    using namespace bencode;

    // Test case 1: Decoding an integer
    {
        std::string encoded = "i42e"; // 42
        Decoder decoder(encoded);
        Value result = decoder.decode();
        assert(boost::get<int>(result) == 42);
        std::cout << "Test 1 Passed!" << std::endl;
    }

    //Test case 2: Decoding a string
    {
        std::string encoded = "5:hello"; //"hello"
        Decoder decoder(encoded);
        Value result = decoder.decode();
        assert(boost::get<std::string>(result) == "hello");
        std::cout << "Test 2 Passed!" << std::endl;
    }

    //Test case 3: Decoding a list
    {
        std::string encoded = "l5:helloi123ee"; //["hello", 123]
        Decoder decoder(encoded);
        Value result = decoder.decode();

        ValueVector list = boost::get<ValueVector>(result);
        assert(boost::get<std::string>(list[0]) == "hello");
        assert(boost::get<int>(list[1]) == 123);
        std::cout << "Test 3 Passed!" << std::endl;
    }

    //Test case 4: Decoding a dictionary
    {
        std::string encoded = "d3:fooi42e3:bar5:helloe"; // {"foo": 42, "bar": "hello"}
        Decoder decoder(encoded);
        Value result = decoder.decode();

        ValueDict dict = boost::get<ValueDict>(result);
        assert(boost::get<int>(dict["foo"]) == 42);
        assert(boost::get<std::string>(dict["bar"]) == "hello");
        std::cout << "Test 4 Passed!" << std::endl;
    }

    std::cout << "All test passed successfully!\n";
    
}

int main(){
    testBencodeDecoder();
    return 0;
}