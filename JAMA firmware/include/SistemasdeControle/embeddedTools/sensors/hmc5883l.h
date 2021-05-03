#ifndef ADRONE_HMC5883L_H
#define ADRONE_HMC5883L_H

#include <stdint.h>
#include "SistemasdeControle/embeddedTools/communicationLibs/i2cHandler.h"


class hmc5883l
{
public:
    // setup registers
    bool init();
    // check wire connection
    bool connected();
    // read data from sensor
    void read();
    // get Y axie gauss
    const double& get_x() const;
    // get X axie gauss
    const double& get_y() const;
    // get Z axie gauss
    const double& get_z() const;

private:
    double  _data[3];      // aceleration data
};

#include "SistemasdeControle/embeddedTools/sensors/hmc5883l.cpp"
#endif
