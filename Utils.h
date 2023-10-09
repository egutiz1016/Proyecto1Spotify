#pragma once
#include <string>
#include <vector>
#include "CD.h"

void loadBackups(const std::string& folderPath, std::vector<CD>& cds);
void displayQueue(const std::vector<Song>& playbackQueue);
