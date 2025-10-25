#ifndef RADAR_H
#define RADAR_H

#include "sensor.h"
#include <vector>
#include <ctime>

struct Target {
    double range;       // distance from target
    double angle;
    double velocity;

    Target (
        double range, double angle, double velocity
    ) : range(range), angle(angle), velocity(velocity) {}
};

class Scan {
public:
    std::vector<Target> targets;
    time_t timestamp;

    Scan(const std::vector<Target>&, time_t);
    ~Scan();
    // TODO: Move constructor
    // TODO: Copy constructor

    // TODO: Copy assignment
    // TODO: Move assignment

    void read();
};

class Radar : public Sensor{
private:
    std::vector<Scan> data;

public:
    Radar(int, int, std::string);
    void readData() override;
    void update(const Scan&);
};

#endif