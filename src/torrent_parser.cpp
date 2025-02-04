#include "../include/torrent_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <openssl/sha.h>

namespace torrent {

    TorrentParser::TorrentParser(const std::string& file_path) : file_path(file_path) {
        std::ifstream file(file_path, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open torrent file: " + file_path);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        file.close();

        bencode::Decoder decoder(buffer.str());
        decoded_data = decoder.decode();

        parse();
    }

    void TorrentParser::parse() {
        if (decoded_data.type() != typeid(bencode::ValueDict)) {
            throw std::runtime_error("Invalid torrent file format. Expected dictionary at root.");
        }

        const bencode::ValueDict& root_dict = boost::get<bencode::ValueDict>(decoded_data);

        auto it = root_dict.find("announce");
        if (it != root_dict.end()) {
            announce = boost::get<std::string>(it->second);
        }

        it = root_dict.find("announce-list");
        if (it != root_dict.end()) {
            const bencode::ValueVector& tracker_list = boost::get<bencode::ValueVector>(it->second);
            for (const auto& tracker : tracker_list) {
                announce_list.push_back(boost::get<std::string>(tracker));
            }
        }

        it = root_dict.find("info");
        if (it != root_dict.end()) {
            const bencode::ValueDict& info_dict = boost::get<bencode::ValueDict>(it->second);

            auto name_it = info_dict.find("name");
            if (name_it != info_dict.end()) {
                name = boost::get<std::string>(name_it->second);
            }

            auto piece_length_it = info_dict.find("piece length");
            if (piece_length_it != info_dict.end()) {
                piece_length = boost::get<int>(piece_length_it->second);
            }

            auto pieces_it = info_dict.find("pieces");
            if (pieces_it != info_dict.end()) {
                std::string pieces_str = boost::get<std::string>(pieces_it->second);
                for (size_t i = 0; i < pieces_str.size(); i += 20) {
                    pieces.push_back(pieces_str.substr(i, 20));
                }
            }

            auto files_it = info_dict.find("files");
            if (files_it != info_dict.end()) {
                is_multi_file = true;
                const bencode::ValueVector& files_list = boost::get<bencode::ValueVector>(files_it->second);
                for (const auto& file_entry : files_list) {
                    const bencode::ValueDict& file_info = boost::get<bencode::ValueDict>(file_entry);
                    std::string file_name = boost::get<std::string>(file_info.at("path"));
                    int file_length = boost::get<int>(file_info.at("length"));
                    files.push_back({file_name, file_length});
                }
            } else {
                is_multi_file = false;
                auto length_it = info_dict.find("length");
                if (length_it != info_dict.end()){
                    int length = boost::get<int>(length_it->second);
                    files.push_back({name, length});
                }
            }

        } else {
            throw std::runtime_error("Missing 'info' dictionary in torrent.");
        }

        info_hash = calculate_info_hash();
    }

    std::string TorrentParser::calculate_info_hash(){
        //serialize
        const bencode::ValueDict& root_dict = boost::get<bencode::ValueDict>(decoded_data);
        const bencode::ValueDict& info_dict = boost::get<bencode::ValueDict>(root_dict.at("info"));

        //std::string info_bencoded = bencode::Encoder::encode(info_dict);
        //Encoder needs to be implemented before this
    }

    std::string TorrentParser::getAnnounce() const {
        return announce;
    }

    std::vector<std::string> TorrentParser::getAnnounceList() const {
        return announce_list;
    }

    std::string TorrentParser::getName() const {
        return name;
    }

    int TorrentParser::getPieceLength() const {
        return piece_length;
    }

    std::vector<std::pair<std::string, int>> TorrentParser::getFiles() const {
        return files;
    }
}