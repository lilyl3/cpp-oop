#include "radar.h"
#include "sensor.h"

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

Scan::Scan(const vector<Target>& targets, time_t timestamp) : targets(targets), timestamp(timestamp){}
Scan::~Scan() {}

Radar::Radar(int id, int data_rate, std::string units) : Sensor(id, data_rate, units) {}

void Radar::readData() {
    for (Scan& scan : data) {
        cout << "Timestamp: " << scan.timestamp << endl;
        for (Target& target : scan.targets) {
            cout << "(Range, angle, velocity): " << target.range << ", " << target.angle << ", " << target.velocity << endl;
        }
        cout << endl;
    }
}

void Radar::update(const Scan& scan) {
    data.push_back(scan);
}