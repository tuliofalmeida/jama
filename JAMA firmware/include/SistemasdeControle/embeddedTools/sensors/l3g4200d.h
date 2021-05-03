#ifndef ADRONE_L3G4200D_H
#define ADRONE_L3G4200D_H

#include <stdint.h>
#include "SistemasdeControle/embeddedTools/communicationLibs/i2cHandler.h"



class l3g4200d
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
    // get Y axie degree per second
    const double& get_x() const;
    // get X axie degree per second
    const double& get_y() const;
    // get Z axie degree per second
    const double& get_z() const;

private:
    int16_t  _raw[3];    // raw data
    double   _data[3];   // degree per second data
    int16_t  _offset[3];  // offset data
};

#include "SistemasdeControle/embeddedTools/sensors/l3g4200d.cpp"
#endif
