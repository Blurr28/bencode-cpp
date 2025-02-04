#ifndef TORRENT_PARSER_H
#define TORRENT_PARSER_H

#include <string>
#include <vector>
#include <map>
#include "bencode_decoder.hpp"

namespace torrent {
    
    class TorrentParser {
    private:
        std::string file_path;
        bencode::Value decoded_data;

        //parsed metadata
        std::string announce;
        std::vector<std::string> announce_list;
        std::string info_hash;
        std::string name;
        int piece_length;
        std::vector<std::string> pieces;
        bool is_multi_file;
        std::vector<std::pair<std::string, int>> files;

        void parse();
        std::string calculate_info_hash();
    
    public:
        explicit TorrentParser(const std::string& file_path);

        std::string getAnnounce() const;
        std::vector<std::string> getAnnounceList() const;
        std::string getInfoHash() const;
        std::string getName() const;
        int getPieceLength() const;
        std::vector<std::string> getPieces() const;
        bool isMultiFile() const;
        std::vector<std::pair<std::string, int>> getFiles() const;

    };
}

#endif