#include "adxl345.h"

#define ADDR            0x53  // i2c address
#define ID              0xE5  // reg id address

#define REG_WHO_AM_I    0x00  // device id
#define REG_OFFSET_X    0x1E  // offset x
#define REG_OFFSET_Y    0x1F  // offset y
#define REG_OFFSET_Z    0x20  // offset z
#define REG_BW_RATE     0x2C  // data rate, power mode
#define REG_POWER_CTL   0x2D  // power control
#define REG_DATA_FORMAT 0x31  // data resolution
#define REG_DATA        0x32  // first data + 6


bool adxl345::init()
{
    i2c_master_init();
    if (!connected()) return false;
    
    std::cout<<"Connected!!!";
    
    // stop measurement
    i2c_master_write_slave(ADDR, REG_POWER_CTL, 0x00);
    // define offset
    //write_byte(ADDR, REG_OFFSET_X, x);
    //write_byte(ADDR, REG_OFFSET_Z, y);
    //write_byte(ADDR, REG_OFFSET_Y, z);
    // output data rate 200Hz
    i2c_master_write_slave(ADDR, REG_BW_RATE, 0x0B);
    // full resolution 16g
    i2c_master_write_slave(ADDR, REG_DATA_FORMAT, 0x0B);
    // start measurement
    i2c_master_write_slave(ADDR, REG_POWER_CTL, 0x08); 
    

    // reset offset values
    _offset[0] = 0;
    _offset[1] = 0;
    _offset[2] = 0;
    _filtered_data[0] = 0;
    _filtered_data[1] = 0;
    _filtered_data[2] = 0;

    this->filter_constant = 0.1;
    return true;
}


bool adxl345::connected()
{
    uint8_t data;
    i2c_master_read_slave(ADDR, REG_WHO_AM_I, &data);
    std::cout<<data;
    return (data == ID) ? true : false;
}


void adxl345::read()
{
    uint8_t reg[6];
    i2c_master_read_slave(ADDR, REG_DATA, &(reg[0]));
    i2c_master_read_slave(ADDR, REG_DATA+1, &(reg[1]));
    i2c_master_read_slave(ADDR, REG_DATA+2, &(reg[2]));
    i2c_master_read_slave(ADDR, REG_DATA+3, &(reg[3]));
    i2c_master_read_slave(ADDR, REG_DATA+4, &(reg[4]));
    i2c_master_read_slave(ADDR, REG_DATA+5, &(reg[5]));
    

    _raw[0] = ((int16_t)reg[1] << 8) | reg[0];
    _raw[1] = ((int16_t)reg[3] << 8) | reg[2];
    _raw[2] = ((int16_t)reg[5] << 8) | reg[4];

    _data[0] = (_raw[0] - _offset[0]) * 0.00390625;
    _filtered_data[0] = _data[0] * filter_constant + (_filtered_data[0] * (1.0-filter_constant));
    _data[1] = (_raw[1] - _offset[1]) * 0.00390625;
    _filtered_data[1] = _data[1] * filter_constant + (_filtered_data[1] * (1.0-filter_constant));
    _data[2] = (_raw[2] - _offset[2]) * 0.00390625;
    _filtered_data[2] = _data[2] * filter_constant + (_filtered_data[2] * (1.0-filter_constant));
}


void adxl345::calibrate()
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
    _offset[2]  = (_offset[2] / 100) - 256;
}


const double& adxl345::get_x() const
{
    return _data[0];
}


const double& adxl345::get_y() const
{
    return _data[1];
}


const double& adxl345::get_z() const
{
    return _data[2];
}

double adxl345::get_filtered_x()
{
    return _filtered_data[0];
}

double adxl345::get_filtered_y()
{
    return _filtered_data[1];
}

double adxl345::get_filtered_z()
{
    return _filtered_data[2];
}

double adxl345::get_pitch()
{
    return (atan2(_filtered_data[0],sign(_filtered_data[2])*sqrt(_filtered_data[1]*_filtered_data[1]+_filtered_data[2]*_filtered_data[2])) * 180.0) / PI;
}

double adxl345::get_roll()
{
    return (atan2(_filtered_data[1],(sqrt(_filtered_data[0]*_filtered_data[0]+_filtered_data[2]*_filtered_data[2]))) * 180.0) / PI;
}

void adxl345::set_filter_constant(const double &filter_constant)
{
    this->filter_constant = filter_constant;
}
