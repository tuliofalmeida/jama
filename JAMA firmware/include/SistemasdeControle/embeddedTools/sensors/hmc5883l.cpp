#include "SistemasdeControle/embeddedTools/sensors/hmc5883l.h"

#define MADDR          0x1E   // i2c MADDRess
#define MID_A          0x48   // device id
#define MID_B          0x34
#define MID_C          0x33

#define MREG_WHO_AM_I  0x0A  // device reg id
#define MREG_A         0x00
#define MREG_B         0x01
#define MREG_MODE      0x02
#define MREG_DATA      0x03


bool hmc5883l::init()
{
    if (!connected()) return false;

    // 2 samples averaged - 75Hz
    i2c_master_write_slave(MADDR, MREG_A, 0b00111000);
    // to do...
    //write_byte(MADDR, REG_B, );
    //continuous measurement mode
    i2c_master_write_slave(MADDR, MREG_MODE, 0x00);

    return true;
}


bool hmc5883l::connected()
{
    uint8_t reg[3];
    i2c_master_read_slave(MADDR, MREG_WHO_AM_I,  &(reg[0]));
    i2c_master_read_slave(MADDR, MREG_WHO_AM_I+1,  &(reg[1]));
    i2c_master_read_slave(MADDR, MREG_WHO_AM_I+2,  &(reg[2]));

    return (
        (reg[0] == MID_A) &&
        (reg[1] == MID_B) &&
        (reg[2] == MID_C)) ? true : false;
}


void hmc5883l::read()
{
    uint8_t reg[6];
    i2c_master_read_slave(MADDR, MREG_DATA, &(reg[0]));
    i2c_master_read_slave(MADDR, MREG_DATA+1, &(reg[1]));
    i2c_master_read_slave(MADDR, MREG_DATA+2, &(reg[2]));
    i2c_master_read_slave(MADDR, MREG_DATA+3, &(reg[3]));
    i2c_master_read_slave(MADDR, MREG_DATA+4, &(reg[4]));
    i2c_master_read_slave(MADDR, MREG_DATA+5, &(reg[5]));
    // std::cout << "Entroumag" << std::endl;
    int16_t raw[3];
    raw[0] = ((int16_t)reg[0] << 8) | reg[1];
    raw[2] = ((int16_t)reg[2] << 8) | reg[3];
    raw[1] = ((int16_t)reg[4] << 8) | reg[5];

    _data[0] = raw[0] * 0.92;
    _data[1] = raw[1] * 0.92;
    _data[2] = raw[2] * 0.92;
}


const double& hmc5883l::get_x() const
{
    return _data[0];
}


const double& hmc5883l::get_y() const
{
    return _data[1];
}


const double& hmc5883l::get_z() const
{
    return _data[2];
}
