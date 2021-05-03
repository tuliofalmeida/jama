#ifndef ADRONE_ADXL345_H
#define ADRONE_ADXL345_H

#include <stdint.h>
#include "SistemasdeControle/embeddedTools/communicationLibs/i2cHandler.h"
#include "iostream"
#include <math.h>
// #define PI 3.14159265359

class adxl345
{
public:
    // setup registers
    bool init();
    // check wire connection
    bool connected();
    // read data from sensor
    void read();
    // calibrate sensor
    void calibrate();
    // get X axie G aceleration
    const double& get_x() const;
    // get Y axie G aceleration
    const double& get_y() const;
    // get Z axie G aceleration
    const double& get_z() const;
    // get X axie G aceleration
    double get_filtered_x();
    // get Y axie G aceleration
    double get_filtered_y();
    // get Z axie G aceleration
    double get_filtered_z();
    // get pitch angle
    double get_pitch();
    // get roll angle
    double get_roll();

    void set_filter_constant(const double &filter_constant);

private:
    int16_t  _raw[3];     // raw data
    double   _data[3], _filtered_data[3], filter_constant;    // aceleration data
    int16_t  _offset[3];  // offset data

    int sign(double value){if(value > 0) return 1; else return -1;}
};

#include "SistemasdeControle/embeddedTools/sensors/adxl345.cpp"
#endif // ADRONE_ADXL345_H
