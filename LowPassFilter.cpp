
#include "LowPassFilter.h"

#define ERROR_CHECK (false)

#if ERROR_CHECK
#include <iostream>
#endif

LowPassFilter::LowPassFilter()
	: m_y {0.0F}
	, m_y_dt {0.0F}
	, ePow {0.0F}
{
}

LowPassFilter::LowPassFilter(float iCutOffFrequency, float iDeltaTime)
	: m_y {0.0F}
	, m_y_dt {0.0F}
	, ePow(1-exp(-iDeltaTime * 2 * M_PI * iCutOffFrequency))
{
	#if ERROR_CHECK
	if (iDeltaTime <= 0){
		std::cout << "Warning: A LowPassFilter instance has been configured with 0 s as delta time.";
		ePow = 0;
	}
	if(iCutOffFrequency <= 0){
		std::cout << "Warning: A LowPassFilter instance has been configured with 0 Hz as cut-off frequency.";
		ePow = 0;
	}
	#endif
}

float LowPassFilter::update(float input){
	return m_y += (input - m_y) * ePow;
}

LPFData_t LowPassFilter::update(float input, float deltaTime, float cutoffFrequency){
	reconfigureFilter(deltaTime, cutoffFrequency); //Changes ePow accordingly.

	float y = m_y + (input - m_y) * ePow;
	float y_dt = (y - m_y) / deltaTime;

	m_y = y;
	m_y_dt = y_dt;

	return LPFData_t {y, y_dt};
}

void LowPassFilter::reconfigureFilter(float deltaTime, float cutoffFrequency){
	#if ERROR_CHECK
	if (deltaTime <= 0){
		std::cout << "Warning: A LowPassFilter instance has been configured with 0 s as delta time.";
		ePow = 0;
	}
	if(cutoffFrequency <= 0){
		std::cout << "Warning: A LowPassFilter instance has been configured with 0 Hz as cut-off frequency.";
		ePow = 0;
	}
	#endif
	ePow = 1-exp(-deltaTime * 2 * M_PI * cutoffFrequency);
}
