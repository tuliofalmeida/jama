#pragma once

#include "SistemasdeControle/embeddedTools/communicationLibs/i2cSoft.h"


#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define MPU6050_PWR1_SLEEP_BIT          6
#define	ACCEL_XOUT	0x3B
//#define	ACCEL_XOUT_H	0x3B	
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18
//#define	MPU6050_ADDR	0x68	//IIC写入时的地址字节数据，+1为读取

Communication::I2C i2c(GPIO_NUM_22, GPIO_NUM_21, I2C_NUM_0);

class MPU6050 {
private:
    //Communication::I2C *i2c;
    uint8_t MPU_ADDR;
public:
    MPU6050(uint8_t MPUADDR = 0x68);
    MPU6050(gpio_num_t scl, gpio_num_t sda, i2c_port_t port);
    ~MPU6050();
    bool init();

    float getAccX();
    float getAccY();
    float getAccZ();

    float getGyroX();
    float getGyroY();
    float getGyroZ();
    void getMotion6(double &ax, double &ay, double &az, double &gx, double &gy, double &gz);
    void SetOffsets(double ax, double ay, double az, double gx, double gy, double gz);

    short getTemp();

};
#include "mpu6050.cpp"