#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

struct InternetUsage {
    std::string start_time;
    std::string end_time;
    int received_bytes;
    int sent_bytes;
    std::string program;
};

void filterAndSortData(const std::string& filename);

#endif // UTILS_H
