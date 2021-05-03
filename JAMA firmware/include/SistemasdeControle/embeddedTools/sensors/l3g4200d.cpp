#include "SistemasdeControle/embeddedTools/sensors/l3g4200d.h"

#define GADDR          0x69
#define GID            0xD3

#define GREG_WHO_AM_I  0x0F
#define GREG_1         0x20
#define GREG_2         0x21
#define GREG_3         0x22
#define GREG_4         0x23
#define GREG_5         0x24
#define GREG_TEMP      0x26
#define GREG_DATA      0x28|(1<<7)


bool l3g4200d::init()
{
    if (!connected()) return false;

    // High pass filter
    i2c_master_write_slave(GADDR, GREG_2, 0x00);
    // Generata data ready interrupt
    i2c_master_write_slave(GADDR, GREG_3, 0x00);
    // Controls the full-scale range
    i2c_master_write_slave(GADDR, GREG_4, 0b00000000);
    // Boot in normal mode, disable FIFO, HPF disabled
    i2c_master_write_slave(GADDR, GREG_5, 0x00);
    // Enable all axis and setup normal mode + Output Data Range & Bandwidth
    i2c_master_write_slave(GADDR, GREG_1, 0b01111111);

    // reset offset values
    _offset[0] = 0;
    _offset[1] = 0;
    _offset[2] = 0;

    calibrate();

    return true;
}


bool l3g4200d::connected()
{
    uint8_t data;
    i2c_master_read_slave(GADDR,GREG_WHO_AM_I, &data);

    return (data == GID) ? true : false;
}


void l3g4200d::read()
{
    uint8_t reg[6];  // 3 axis data from 6 registers
    i2c_master_read_slave(GADDR, GREG_DATA, &(reg[0]));
    i2c_master_read_slave(GADDR, GREG_DATA+1, &(reg[1]));
    i2c_master_read_slave(GADDR, GREG_DATA+2, &(reg[2]));
    i2c_master_read_slave(GADDR, GREG_DATA+3, &(reg[3]));
    i2c_master_read_slave(GADDR, GREG_DATA+4, &(reg[4]));
    i2c_master_read_slave(GADDR, GREG_DATA+5, &(reg[5]));

    _raw[0] = ((int16_t)reg[1] << 8) | reg[0];
    _raw[1] = ((int16_t)reg[3] << 8) | reg[2];
    _raw[2] = ((int16_t)reg[5] << 8) | reg[4];

    //read_byte(GADDR, REG_TEMP, &reg[0]);
    //double factor =

    _data[0] = (_raw[0] - _offset[0]) * 0.00875; // + factor);
    _data[1] = (_raw[1] - _offset[1]) * 0.00875; // + factor);
    _data[2] = (_raw[2] - _offset[2]) * 0.00875; // + factor);
}


void l3g4200d::calibrate()
{
    for (unsigned i = 0; i < 100; ++i)
    {
        read();

        _offset[0] += _raw[0];
        _offset[1] += _raw[1];
        _offset[2] += _raw[2];

        vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    _offset[0] /= 100;
    _offset[1] /= 100;
    _offset[2] /= 100;
}


const double& l3g4200d::get_x() const
{
    return _data[0];
}


const double& l3g4200d::get_y() const
{
    return _data[1];
}


const double& l3g4200d::get_z() const
{
    return _data[2];
}
