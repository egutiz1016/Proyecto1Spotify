#pragma once
#include <string>

class Song {
public:
    Song(const std::string& name, const std::string& artist, const std::string& duration);
    std::string getName() const;
    std::string getArtist() const;
    std::string getDuration() const;

private:
    std::string name;
    std::string artist;
    std::string duration;
};
