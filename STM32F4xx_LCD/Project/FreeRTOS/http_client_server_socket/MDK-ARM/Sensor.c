#include "Sensor.h"
float slope_calibration;// = -0.058;
float slope_pH(float temp_subfunction)
{
	return (slope_calibration*(temp_subfunction + (float)273.15)/(Probe_pH_temp + (float)273.15));
}
