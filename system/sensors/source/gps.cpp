#include "gps.h"
#include "sensor.h"

#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

std::string fixToString(FIX_TYPE fix){
    switch(fix) {
        case FIX_TYPE::None:   return "None";
        case FIX_TYPE::TwoD:   return "2D";
        case FIX_TYPE::ThreeD: return "3D";
        default:               return "N/A";
    }
}

GPS::GPS(int id, int data_rate, std::string units) : Sensor(id, data_rate, units) {}

void GPSReading::readData() {
    cout << "Timestamp: " << timestamp; 
    cout << "\n(Longitude, Latitude, Altitude ): " << longitude << ", " << latitude << ", " << altitude;
    cout << "\nNumber of Satellites: " << numberOfSatellites;
    cout << "\n(Fix, HDOP, VDOP): " << fixToString(fix) << ", " << hdop << ", " << vdop;
}

void GPS::readData() {
    for (GPSReading reading : data) {
        reading.readData();
        cout << endl << endl;
    }
}

void GPS::update(const GPSReading& newData) {
    data.push_back(newData);
}