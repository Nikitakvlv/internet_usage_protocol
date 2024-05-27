#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

bool sortByUsage(const InternetUsage& a, const InternetUsage& b) {
    return (a.end_time > b.end_time);
}

bool sortByProgram(const InternetUsage& a, const InternetUsage& b) {
    if (a.program != b.program) {
        return a.program < b.program;
    } else {
        return (a.received_bytes + a.sent_bytes) > (b.received_bytes + b.sent_bytes);
    }
}

void filterAndSortData(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<InternetUsage> data;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        InternetUsage entry;
        iss >> entry.start_time >> entry.end_time >> entry.received_bytes >> entry.sent_bytes >> entry.program;
        if (entry.program == "Skype" && entry.start_time > "08:00:00") {
            data.push_back(entry);
        }
    }
    file.close();
    std::sort(data.begin(), data.end(), sortByUsage);
    std::cout << "Sorted by usage time:" << std::endl;
    for (const auto& entry : data) {
        std::cout << entry.start_time << " - " << entry.end_time << ", Program: " << entry.program << std::endl;
    }
    std::sort(data.begin(), data.end(), sortByProgram);
    std::cout << "Sorted by program and usage:" << std::endl;
    for (const auto& entry : data) {
        std::cout << "Program: " << entry.program << ", Bytes: " << (entry.received_bytes + entry.sent_bytes) << std::endl;
    }
}
