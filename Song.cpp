#include "Song.h"

Song::Song(const std::string& name, const std::string& artist, const std::string& duration)
    : name(name), artist(artist), duration(duration) {}

std::string Song::getName() const {
    return name;
}

std::string Song::getArtist() const {
    return artist;
}

std::string Song::getDuration() const {
    return duration;
}
