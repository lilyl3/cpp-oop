#ifndef SENSOR_H
#define SENSOR_H

#include <string>

enum class STATUS {OFFLINE, ACTIVE, ERROR};

class Sensor {
private:
    int id;
    STATUS status;
    int data_rate;
    std::string units;

public:
    virtual void readData() = 0; 
    void setStatus(STATUS);
    STATUS getStatus();

    Sensor(int, int, std::string);
    
    // virtual ensures derived resources are cleaned up ==> calls derived class' destructor
    virtual ~Sensor() = default;    
};

#endif