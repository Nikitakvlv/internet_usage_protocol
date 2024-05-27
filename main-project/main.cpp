#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "utils.h"

int main() {
    std::vector<InternetSession> sessions;
    std::ifstream infile("data/input.txt");

    if (!infile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        InternetSession session;
        if (!(iss >> session.start.hours >> session.start.minutes >> session.start.seconds
            >> session.end.hours >> session.end.minutes >> session.end.seconds
            >> session.bytesReceived >> session.bytesSent)) {
            break;
        }
        std::getline(iss, session.program);
        sessions.push_back(session);
    }
    infile.close();

    // Ôèëüòðàöèÿ ïî ïðîãðàììå Skype
    auto skypeSessions = filterByProgram(sessions, "Skype");

    // Ôèëüòðàöèÿ ïî âðåìåíè
    Time threshold(8, 0, 0);
    auto after8Sessions = filterByStartTime(sessions, threshold);

    // Ñîðòèðîâêà
    auto sortedByUsageTime = sessions;
    insertionSort(sortedByUsageTime, usageTimeDescending);

    auto sortedByProgram = sessions;
    quickSort(sortedByProgram, programAscending);

    // Âûâîä ðåçóëüòàòîâ
    std::cout << "Sessions using Skype:\n";
    printSessions(skypeSessions);

    std::cout << "\nSessions after 8:00:00:\n";
    printSessions(after8Sessions);

    std::cout << "\nSessions sorted by usage time descending:\n";
    printSessions(sortedByUsageTime);

    std::cout << "\nSessions sorted by program name ascending:\n";
    printSessions(sortedByProgram);

    return 0;
}
