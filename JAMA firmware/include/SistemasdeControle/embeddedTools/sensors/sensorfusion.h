#ifndef ADRONE_SENSOR_FUSION_H
#define ADRONE_SENSOR_FUSION_H

#define M_PI    3.14159265358979323846

// c library
#include <stdint.h>
#include <math.h>
// esp + extras
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
#include "SistemasdeControle/embeddedTools/communicationLibs/i2cHandler.h"
#include "SistemasdeControle/embeddedTools/sensors/kalman.h"
#include "SistemasdeControle/embeddedTools/sensors/adxl345.h"
#include "SistemasdeControle/embeddedTools/sensors/l3g4200d.h"
#include "SistemasdeControle/embeddedTools/sensors/hmc5883l.h"


namespace GY80
{
    class sensorfusion
    {
    public:
        /**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other sensorfusion object
         */
        sensorfusion(){};
        sensorfusion(const sensorfusion &other)  = delete;
        sensorfusion(const sensorfusion &&other) = delete;

       /**
         * Disable copy and move assignment operator
         * 
         * @param other sensorfusion object
         */
        sensorfusion& operator=(const sensorfusion &other)  = delete;
        sensorfusion& operator=(const sensorfusion &&other) = delete;

        /**
         * [brief description]
         */
        ~sensorfusion();

        /**
         * [description]
         * 
         * @return [description]
         */
        LinAlg::Matrix<double> update();
        LinAlg::Matrix<double> updateRaw();
        void init();
    private:
        // sensors
        adxl345  _acce;
        l3g4200d _gyro;
        hmc5883l _magn;
        // matrix result with position & angles
        LinAlg::Matrix<double> _angle_position, rawData;
        // kalman filter parameters
        LinAlg::Matrix<double> _F, B, _Q, _H, _R;
        // kalman filters
        kalman _kpitch, _kroll, _kyaw;
        // X axis as reference in radians
        double get_pitch(const double &x, const double &y, const double &z);
        // Y axis as reference in radians
        double get_roll(const double &x, const double &y, const double &z);
        // to compensate and correct the yaw in radians
        double get_yaw(const double &x, const double &y, const double &z, const double &pitch, const double &roll);
        // remove gravity from accelerometer axis
        // matrix remove_gravity(matrix position, const double &alpha, const double &beta, const double &gama);
    };
}

#include "SistemasdeControle/embeddedTools/sensors/sensorfusion.cpp"
GY80::sensorfusion sensors;
#endif