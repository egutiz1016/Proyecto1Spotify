#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "CD.h"
#include "Song.h"
#include "Utils.h"

int main() {
    std::vector<CD> cds;
    std::vector<Song> playbackQueue;

    while (true) {
        std::cout << "\nMenú Principal:" << std::endl;
        std::cout << "1. Cargar Respaldos" << std::endl;
        std::cout << "2. Ver Lista de CDs" << std::endl;
        std::cout << "3. Agregar Canción a la Cola de Reproducción" << std::endl;
        std::cout << "4. Ver Cola de Reproducción" << std::endl;
        std::cout << "5. Reproducción Actual" << std::endl;
        std::cout << "6. Reproducir Siguiente" << std::endl;
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Consumir el salto de línea

        switch (choice) {
        case 1: {
            std::string folderPath;
            std::cout << "Ingrese la ruta de la carpeta de respaldos: ";
            std::getline(std::cin, folderPath);
            loadBackups(folderPath, cds);
            break;
        }
        case 2: {
            if (cds.empty()) {
                std::cout << "No hay CDs cargados." << std::endl;
            }
            else {
                std::cout << "Lista de CDs:" << std::endl;
                int index = 1;
                for (const CD& cd : cds) {
                    std::cout << index << ". " << cd.getName() << " (" << cd.getSongCount() << " canciones)" << std::endl;
                    index++;
                }
            }
            break;
        }
        case 3: {
            if (cds.empty()) {
                std::cout << "No hay CDs cargados. Primero, cargue los respaldos." << std::endl;
            }
            else {
                int cdIndex, songIndex;
                std::cout << "Seleccione un CD para agregar una canción a la cola de reproducción:" << std::endl;
                int cdCount = cds.size();
                for (int i = 0; i < cdCount; i++) {
                    std::cout << i + 1 << ". " << cds[i].getName() << std::endl;
                }
                std::cin >> cdIndex;

                // Validar la selección de CD
                if (cdIndex <= 0 || cdIndex > cdCount) {
                    std::cout << "Selección de CD no válida." << std::endl;
                    break;
                }

                const std::vector<Song>& songs = cds[cdIndex - 1].getSongs();
                std::cout << "Seleccione una canción para agregar a la cola de reproducción:" << std::endl;
                int songCount = songs.size();
                for (int i = 0; i < songCount; i++) {
                    std::cout << i + 1 << ". " << songs[i].getName() << " - " << songs[i].getArtist() << " (" << songs[i].getDuration() << ")" << std::endl;
                }
                std::cin >> songIndex;

                // Validar la selección de canción
                if (songIndex <= 0 || songIndex > songCount) {
                    std::cout << "Selección de canción no válida." << std::endl;
                    break;
                }

                playbackQueue.push_back(songs[songIndex - 1]);
                std::cout << "Canción agregada a la cola de reproducción." << std::endl;
            }
            break;
        }
        case 4: {
            displayQueue(playbackQueue);
            break;
        }
        case 5: {
            if (playbackQueue.empty()) {
                std::cout << "Reproducción en Pausa." << std::endl;
            }
            else {
                const Song& currentSong = playbackQueue[0];
                std::cout << "Reproducción Actual:" << std::endl;
                std::cout << "Nombre: " << currentSong.getName() << std::endl;
                std::cout << "Artista: " << currentSong.getArtist() << std::endl;
                std::cout << "Duración: " << currentSong.getDuration() << std::endl;
            }
            break;
        }
        case 6: {
            if (!playbackQueue.empty()) {
                const Song& nextSong = playbackQueue[0];
                std::cout << "Reproduciendo siguiente canción:" << std::endl;
                std::cout << "Nombre: " << nextSong.getName() << std::endl;
                std::cout << "Artista: " << nextSong.getArtist() << std::endl;
                std::cout << "Duración: " << nextSong.getDuration() << std::endl;
                playbackQueue.erase(playbackQueue.begin()); // Eliminar la canción reproducida
            }
            else {
                std::cout << "La cola de reproducción está vacía. Agregue canciones antes de reproducir siguiente." << std::endl;
            }
            break;
        }
        case 7: {
            std::cout << "¡Hasta luego!" << std::endl;
            return 0;
        }
        default:
            std::cout << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
            break;
        }
    }

    return 0;
}
