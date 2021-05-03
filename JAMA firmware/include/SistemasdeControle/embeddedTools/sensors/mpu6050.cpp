#include "mpu6050.h"

#define ORIGINAL_OUTPUT			 (0)
#define ACC_FULLSCALE        	 (16)
#define GYRO_FULLSCALE			 (2000)

#if ORIGINAL_OUTPUT == 0
	#if  ACC_FULLSCALE  == 2
		#define AccAxis_Sensitive (float)(16384)
	#elif ACC_FULLSCALE == 4
		#define AccAxis_Sensitive (float)(8192)
	#elif ACC_FULLSCALE == 8
		#define AccAxis_Sensitive (float)(4096)
	#elif ACC_FULLSCALE == 16
		#define AccAxis_Sensitive (float)(2048)
	#endif 
		
	#if   GYRO_FULLSCALE == 250
		#define GyroAxis_Sensitive (float)(131.0)
	#elif GYRO_FULLSCALE == 500
		#define GyroAxis_Sensitive (float)(65.5)
	#elif GYRO_FULLSCALE == 1000
		#define GyroAxis_Sensitive (float)(32.8)
	#elif GYRO_FULLSCALE == 2000
		#define GyroAxis_Sensitive (float)(16.4)
	#endif
		
#else
	#define AccAxis_Sensitive  (1)
	#define GyroAxis_Sensitive (1)
#endif

MPU6050::MPU6050( uint8_t MPUADDR) {
    this->MPU_ADDR = MPUADDR;
    //this->i2c = i2c;
}

MPU6050::MPU6050(gpio_num_t scl, gpio_num_t sda, i2c_port_t port) {
    //i2c = new Communication::I2C(scl, sda, port);
}

MPU6050::~MPU6050() {
    //delete(i2c);
}

bool MPU6050::init() {
    if (!i2c.slave_write(MPU_ADDR, PWR_MGMT_1  , 0x00))
        return false;
    if (!i2c.slave_write(MPU_ADDR, SMPLRT_DIV  , 0x07))
        return false;
    if (!i2c.slave_write(MPU_ADDR, CONFIG      , 0x07))
        return false;
    if (!i2c.slave_write(MPU_ADDR, GYRO_CONFIG , 0x18))
        return false;
    if (!i2c.slave_write(MPU_ADDR, ACCEL_CONFIG, 0x01))
        return false;
    if (!i2c.slave_write(MPU_ADDR, MPU6050_PWR1_SLEEP_BIT, 0))
        return false;
    return true;
}

float MPU6050::getAccX() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, ACCEL_XOUT, r, 2);
    short accx = r[0] << 8 | r[1];
    return (float)accx / AccAxis_Sensitive;
}

float MPU6050::getAccY() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, ACCEL_YOUT_H, r, 2);
    short accy = r[0] << 8 | r[1];
    return (float)accy / AccAxis_Sensitive;
}

float MPU6050::getAccZ() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, ACCEL_ZOUT_H, r, 2);
    short accz = r[0] << 8 | r[1];
    return (float)accz / AccAxis_Sensitive;
}

float MPU6050::getGyroX() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, GYRO_XOUT_H, r, 2);
    short gyrox = r[0] << 8 | r[1];
    return (float)gyrox / GyroAxis_Sensitive;
}

float MPU6050::getGyroY() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, GYRO_YOUT_H, r, 2);
    short gyroy = r[0] << 8 | r[1];
    return (float)gyroy / GyroAxis_Sensitive;
}

float MPU6050::getGyroZ() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, GYRO_ZOUT_H, r, 2);
    short gyroz = r[0] << 8 | r[1];
    return (float)gyroz / GyroAxis_Sensitive;
}

short MPU6050::getTemp() {
    uint8_t r[2];
    i2c.slave_read(MPU_ADDR, TEMP_OUT_H, r, 2);
    return r[0] << 8 | r[1];
}

void MPU6050::getMotion6(double &ax, double &ay, double &az, double &gx, double &gy, double &gz)
{
    uint8_t r[12];
    i2c.slave_read(MPU_ADDR, ACCEL_XOUT, r, 12);
    short temp = r[0] << 8 | r[1];
    ax = (double)temp / AccAxis_Sensitive;
    temp = r[2] << 8 | r[3];
    ay = (double)temp / AccAxis_Sensitive;
    temp = r[4] << 8 | r[5];
    az = (double)temp / AccAxis_Sensitive;
    temp = r[6] << 8 | r[7];
    gx = (double)temp / GyroAxis_Sensitive;
    temp = r[8] << 8 | r[9];
    gy = (double)temp / GyroAxis_Sensitive;
    temp = r[10] << 8 | r[11];
    gz = (double)temp / GyroAxis_Sensitive;
}
    
void MPU6050::SetOffsets(double ax, double ay, double az, double gx, double gy, double gz){
    i2c.slave_write(MPU_ADDR, MPU6050_RA_XA_OFFS_H, ax);
    i2c.slave_write(MPU_ADDR, MPU6050_RA_YA_OFFS_H, ay);
    i2c.slave_write(MPU_ADDR, MPU6050_RA_ZA_OFFS_H, az);
    i2c.slave_write(MPU_ADDR, MPU6050_RA_XG_OFFS_USRH, gx);
    i2c.slave_write(MPU_ADDR, MPU6050_RA_YG_OFFS_USRH, gy);
    i2c.slave_write(MPU_ADDR, MPU6050_RA_ZG_OFFS_USRH, gz);
}

bool MPU6050::initDMP6(gpio_num_t interruptPin){
    
}