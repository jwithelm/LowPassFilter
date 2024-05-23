#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H

#include <cmath>


typedef struct LPFData
{
	float y;
	float y_dt;
} LPFData_t;


class LowPassFilter {
public:
	//constructors
	LowPassFilter();
	LowPassFilter(float iCutOffFrequency, float iDeltaTime);
	//functions
	float update(float input);
	LPFData_t update(float input, float deltaTime, float cutoffFrequency);
	//get and configure funtions
	float get_y(void) const {return m_y;}
	float get_y_dt(void) const {return m_y_dt;}
	void reconfigureFilter(float deltaTime, float cutoffFrequency);
private:
	float m_y { };
	float m_y_dt { };
	float ePow { };
};

#endif //LOW_PASS_FILTER_H
