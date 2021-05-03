#include "SistemasdeControle/headers/optimizationLibs/relay.h"

Relay::Relay()
{
    this->Error = 0;
    this->Reference = 0;
    this->toleranceError = 0.01;

    this->relayOutput = LinAlg::Zeros<double>(100,1);
    this->systemOutput = LinAlg::Zeros<double>(100,1);

    this->kp = 1;
    this->ki = 1;
    this->kd = 0;

    this->peakRelayOutput = 1;
    this->peakSystemOutput = 0;

    this->Sample = 2;
    this->SampleTime = 0.01;
}

void Relay::relayCalc()
{
    if((this->Error > this->toleranceError) && (this->Error > 0))
       this->relayOutput(Sample, 1) = this->peakRelayOutput;
    if((this->Error > this->toleranceError) && (this->Error < 0))
       this->relayOutput(Sample, 1) = -this->peakRelayOutput;
    if((this->Error < this->toleranceError) && (this->relayOutput(this->Sample-1, 1) == this->peakRelayOutput))
       this->relayOutput(Sample, 1) = this->peakRelayOutput;
    if((this->Error < this->toleranceError) && (this->relayOutput(this->Sample-1, 1) == -this->peakRelayOutput))
       this->relayOutput(Sample, 1) = -this->peakRelayOutput;
}

void Relay::setToleranceError(double tolerance)
{
    this->toleranceError = tolerance;
}

void Relay::setReference(double ref)
{
    this->Reference = ref;
}

double Relay::relayLoop(double output)
{
    this->Error = this->Reference - output;
    this->systemOutput(this->Sample, 1) = output;

    relayCalc();
    return 0;
}
