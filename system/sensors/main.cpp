#include "sensor.h"
#include "gps.h"
#include "radar.h"

#include <chrono>
using namespace std;

int main() {
    GPS gps(1, 1, "Hz");
    Radar radar(2, 25, "Hz");

    gps.getStatus();
    radar.getStatus();

    gps.setStatus(STATUS::ACTIVE);
    radar.setStatus(STATUS::ACTIVE);

    GPSReading reading1(
        34.6, -12.4, 56.2,
        4, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), 1.2,
        0.34, FIX_TYPE::ThreeD
    );

    GPSReading reading2 (
        -78.5, 27.3, 0,
        2, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), 0.85,
        0.68, FIX_TYPE::TwoD
    );

    gps.update(reading1);
    gps.update(reading2);

    Target target1 = Target(12.3, 25.3, 13.4);
    Target target2 = Target(34.3, 15.7, 11.5);
    vector<Target> targets1 = {target1, target2};
    Scan scan1 = Scan(targets1, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    Target target3 = Target(29.3, 7.6, 49.6);
    vector<Target> targets2 = {target3};
    Scan scan2 = Scan(targets2, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    radar.update(scan1);
    radar.update(scan2);

    vector<Sensor*> sensors = {&radar, &gps};
    for (Sensor* sensorPtr : sensors) {
        sensorPtr->readData();
    }

    return 0;
}
