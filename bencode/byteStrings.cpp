#include "byteStrings.h"

string decode_byte_string(string str) {
  string bencoded = str;
  string byteString;
  int length;
  size_t colon_index = bencoded.find(":");

  if (colon_index != string::npos) {
    length = stoi(bencoded.substr(0, colon_index));
    byteString = bencoded.substr(colon_index + 1, bencoded.size());

    if (byteString.length() < length) {
      cerr << "error: Specified length is more than byteString length" << endl;
      return "";
    } else {
      byteString = byteString.substr(0, length);
    }
  } else {
    cerr << "error: Invalid bencoded string!" << endl;
  }

  return byteString;
}

string encode_byte_string(string str) {
  string byteString = str;
  string bencode;
  size_t length = byteString.size();

  if (length > 0) {
    bencode = to_string(length) + ":" + byteString;
  } else {
    cerr << "error: Empty byte string!" << endl;
  }

  return bencode;
}
