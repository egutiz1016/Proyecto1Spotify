#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "CD.h"
#include "Song.h"

namespace fs = std::filesystem;

void loadBackups(const std::string& folderPath, std::vector<CD>& cds) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_directory()) {
            continue; // Ignorar carpetas
        }

        std::string filename = entry.path().filename().string();
        std::string filepath = entry.path().string();
        std::ifstream file(filepath);

        if (file) {
            std::string cdName = filename.substr(0, filename.find_last_of("."));
            CD cd(cdName);

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string name, artist, duration;
                if (std::getline(iss, name, '|') &&
                    std::getline(iss, artist, '|') &&
                    std::getline(iss, duration)) {
                    Song song(name, artist, duration);
                    cd.addSong(song);
                }
                else {
                    std::cerr << "Error en el formato de línea en el archivo: " << filename << std::endl;
                }
            }

            if (cd.getSongCount() > 0) {
                cds.push_back(cd);
                std::cout << "CD cargado: " << cdName << " (" << cd.getSongCount() << " canciones)" << std::endl;
            }
            else {
                std::cerr << "El archivo no contiene canciones válidas: " << filename << std::endl;
            }

            file.close();
        }
        else {
            std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        }
    }
}

void displayQueue(const std::vector<Song>& playbackQueue) {
    if (playbackQueue.empty()) {
        std::cout << "La cola de reproducción está vacía." << std::endl;
    }
    else {
        std::cout << "Cola de Reproducción:" << std::endl;
        int index = 1;
        for (const Song& song : playbackQueue) {
            std::cout << index << ". " << song.getName() << " - " << song.getArtist() << " (" << song.getDuration() << ")" << std::endl;
            index++;
        }
    }
}
