#pragma once
#include <string>
#include <vector>
#include "Song.h"

class CD {
public:
    CD(const std::string& name);
    std::string getName() const;
    int getSongCount() const;
    void addSong(const Song& song);
    const std::vector<Song>& getSongs() const;

private:
    std::string name;
    std::vector<Song> songs;
};
