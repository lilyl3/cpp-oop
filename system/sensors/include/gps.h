#ifndef GPS_H
#define GPS_H

#include "sensor.h"
#include <vector>
#include <ctime>
#include <string>

enum class FIX_TYPE {None, TwoD, ThreeD};

struct GPSReading {
    double longitude, latitude, altitude;
    int numberOfSatellites;
    time_t timestamp;

    double hdop, vdop;      // Dilution of precision due to satellite geometry
    FIX_TYPE fix;

    GPSReading(
        double longitude, double latitude, double altitude, 
        int numberOfSatellites, time_t timestamp, double hdop,
        double vdop, FIX_TYPE fix
    ) : longitude(longitude), latitude(latitude), altitude(altitude),
        numberOfSatellites(numberOfSatellites), timestamp(timestamp), hdop(hdop),
        vdop(vdop), fix(fix) {}

    void readData();
};

class GPS : public Sensor {
private:
    std::vector<GPSReading> data;

public:
    GPS(int, int, std::string);
    void readData() override;
    void update(const GPSReading& newData);
};

#endif