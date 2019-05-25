#include "Sensor.h"
double slope_calibration;// = -0.058;
double slope_pH(double temp_subfunction)
{
	return (slope_calibration*(temp_subfunction + 273.15)/(Probe_pH_temp + 273.15));
}
