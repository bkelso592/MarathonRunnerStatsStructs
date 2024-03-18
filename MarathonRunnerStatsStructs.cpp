#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

struct Runner {
    std::string name;
    std::vector<int> milesPerDay;
    int totalMiles;
    double avgMiles;
};

// Function prototypes
void readData(std::vector<Runner>& runners);
void calculateStats(std::vector<Runner>& runners);
void outputResults(const std::vector<Runner>& runners);

void readData(std::vector<Runner>& runners) {
    std::ifstream inputFile("Text.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        exit(1);
    }

    while (!inputFile.eof()) {
        Runner runner;
        inputFile >> runner.name;
        for (int j = 0; j < 7; ++j) {
            int miles;
            inputFile >> miles;
            runner.milesPerDay.push_back(miles);
        }
        runners.push_back(runner);
    }

    inputFile.close();
}

void calculateStats(std::vector<Runner>& runners) {
    for (Runner& runner : runners) {
        runner.totalMiles = 0;
        for (int miles : runner.milesPerDay) {
            runner.totalMiles += miles;
        }
        runner.avgMiles = static_cast<double>(runner.totalMiles) / runner.milesPerDay.size();
    }
}

void outputResults(const std::vector<Runner>& runners) {
    std::cout << std::left << std::setw(10) << "Runner";
    for (int i = 1; i <= 7; ++i) {
        std::cout << std::left << std::setw(8) << "Day " << i;
    }
    std::cout << std::left << std::setw(10) << "Total";
    std::cout << std::left << std::setw(10) << "Avg" << std::endl;

    for (const Runner& runner : runners) {
        std::cout << std::left << std::setw(10) << runner.name;
        for (int miles : runner.milesPerDay) {
            std::cout << std::left << std::setw(8) << miles;
        }
        std::cout << std::left << std::setw(10) << runner.totalMiles;
        std::cout << std::left << std::setw(10) << std::fixed << std::setprecision(2) << runner.avgMiles << std::endl;
    }
}

int main() {
    std::vector<Runner> runners;
    readData(runners);
    calculateStats(runners);
    outputResults(runners);
    return 0;
}