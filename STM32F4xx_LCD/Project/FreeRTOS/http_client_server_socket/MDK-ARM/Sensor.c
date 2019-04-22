#include "Sensor.h"
float slope_24 = -58.0;
float slope_pH(float temp)
{
	return (slope_24*(temp + 273.15)/(24 + 273.15));
}
