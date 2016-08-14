#ifndef CO2_sensor_h
#define CO2_sensor_h

#include "../../../sources/Sensors/Sensor.h"


#define         DC_GAIN                      (5)   //define the DC gain of amplifier


/***********************Software Related Macros************************************/
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in milisecond) between each samples in 
//normal operation

/**********************Application Related Macros**********************************/
//These two values differ from sensor to sensor. user should derermine this value.
#define         ZERO_POINT_VOLTAGE           (0.524) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTGAE             (0.020) //define the “voltage drop” of the sensor when move the sensor from air into 1000ppm CO2



class CO2Sensor: public Sensor
{
	public:
		CO2Sensor(String _name, int pin);
		bool read();
	private:
		int MG_PIN;     //define which analog input channel you are going to use
		/*****************************Globals***********************************************/
		float           CO2Curve[3] = { 2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE / (2.602 - 3)) };
		//two points are taken from the curve. 
		//with these two points, a line is formed which is
		//"approximately equivalent" to the original curve.
		//data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280) 
		//slope = ( reaction voltage ) / (log400 –log1000) 

		float MGRead(int mg_pin);
		int  MGGetPercentage(float volts, float *pcurve);
};

#endif

