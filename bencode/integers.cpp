#include "integers.h"
#include <stdexcept>
#include <string>

int decode_integers(string str) {
  string bencoded = str;
  int integer_value;
  if (bencoded.length() < 3) {
    cerr << "error: Invalid bencode" << endl;
    return 0;
  }

  size_t end_delimiter_pos = bencoded.find("e");
  size_t start_delimiter_pos = bencoded.find("i");

  if (end_delimiter_pos != string::npos &&
      start_delimiter_pos != string::npos &&
      start_delimiter_pos < end_delimiter_pos) {
    try {
      integer_value =
          stoi(bencoded.substr(start_delimiter_pos + 1, end_delimiter_pos));
    } catch (const invalid_argument &e) {
      cerr << "error: Invalid integer value" << endl;
      return 0;
    } catch (const out_of_range &e) {
      cerr << "error: Integer out of range" << endl;
      return 0;
    }
  } else {
    cerr << "error: Invalid bencode format" << endl;
  }

  return integer_value;
}

string encode_integers(int integer_value) {
  return "i" + to_string(integer_value) + "e";
}
