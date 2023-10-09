#include "CD.h"

CD::CD(const std::string& name) : name(name) {}

std::string CD::getName() const {
    return name;
}

int CD::getSongCount() const {
    return songs.size();
}

void CD::addSong(const Song& song) {
    songs.push_back(song);
}

const std::vector<Song>& CD::getSongs() const {
    return songs;
}
