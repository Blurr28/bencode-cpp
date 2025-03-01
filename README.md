# Bencode Library

A lightweight C++ library for encoding and decoding data in the **Bencode** format, commonly used in BitTorrent applications.

## Features
- Decode bencoded integers, strings, lists, and dictionaries.
- Encode C++ data structures into bencoded format.
- Fully recursive parsing and encoding.
- Header-only library for easy integration.

## Installation
Clone the repository:

```bash
git clone https://github.com/yourusername/bencode-lib.git
cd bencode-lib
```

## Usage
Include the library in your project:

```cpp
#include "bencode_decoder.hpp"
#include "bencode_encoder.hpp"
```

### Decoding Example
```cpp
#include "bencode_decoder.hpp"
#include <iostream>

int main() {
    std::string data = "4:spam";
    bencode::Decoder decoder(data);
    bencode::Value result = decoder.decode();
    std::cout << boost::get<std::string>(result) << std::endl; // Output: spam
}
```

### Encoding Example
```cpp
#include "bencode_encoder.hpp"
#include <iostream>

int main() {
    bencode::Value value = std::string("spam");
    bencode::Encoder encoder;
    std::string encoded = encoder.encode(value);
    std::cout << encoded << std::endl; // Output: 4:spam
}
```

## Dependencies
- Boost C++ Libraries

## License
This project is licensed under the GPL.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.


---

