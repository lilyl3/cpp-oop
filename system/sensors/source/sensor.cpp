#include "sensor.h"

void Sensor::setStatus(STATUS newStatus) {
    status = newStatus;
}

STATUS Sensor::getStatus() {
    return status;
}

Sensor::Sensor(
    int id, int data_rate, std::string units
) : id(id), status(STATUS::OFFLINE), data_rate(data_rate), units(units){}