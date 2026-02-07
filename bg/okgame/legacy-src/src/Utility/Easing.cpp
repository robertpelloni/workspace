#include "stdafx.h"
#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif
//Logger Easing::log = Logger("Easing");

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"

double Easing::linearTween(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * ticks / durationTicks + beginningValue;
}

double Easing::easeInQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * (ticks /= durationTicks) * ticks + beginningValue;
}

double Easing::easeOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return -changeInValue * (ticks /= durationTicks) * (ticks - 2) + beginningValue;
}

double Easing::easeInOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * ticks * ticks + beginningValue;
	}
	return -changeInValue / 2 * ((--ticks) * (ticks - 2) - 1) + beginningValue;
}

double Easing::easeInCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * (ticks /= durationTicks) * ticks * ticks + beginningValue;
}

double Easing::easeOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * ((ticks = ticks / durationTicks - 1) * ticks * ticks + 1) + beginningValue;
}

double Easing::easeInOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * ticks * ticks * ticks + beginningValue;
	}
	return changeInValue / 2 * ((ticks -= 2) * ticks * ticks + 2) + beginningValue;
}

double Easing::easeInQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * (ticks /= durationTicks) * ticks * ticks * ticks + beginningValue;
}

double Easing::easeOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return -changeInValue * ((ticks = ticks / durationTicks - 1) * ticks * ticks * ticks - 1) + beginningValue;
}

double Easing::easeInOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * ticks * ticks * ticks * ticks + beginningValue;
	}
	return -changeInValue / 2 * ((ticks -= 2) * ticks * ticks * ticks - 2) + beginningValue;
}

double Easing::easeInQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * (ticks /= durationTicks) * ticks * ticks * ticks * ticks + beginningValue;
}

double Easing::easeOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * ((ticks = ticks / durationTicks - 1) * ticks * ticks * ticks * ticks + 1) + beginningValue;
}

double Easing::easeInOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * ticks * ticks * ticks * ticks * ticks + beginningValue;
	}
	return changeInValue / 2 * ((ticks -= 2) * ticks * ticks * ticks * ticks + 2) + beginningValue;
}

double Easing::easeInSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return -changeInValue * cos(ticks / durationTicks * (M_PI / 2)) + changeInValue + beginningValue;
}

double Easing::easeOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * sin(ticks / durationTicks * (M_PI / 2)) + beginningValue;
}

double Easing::easeInOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return -changeInValue / 2 * (cos(M_PI * ticks / durationTicks) - 1) + beginningValue;
}

double Easing::easeInExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return (ticks == 0) ? beginningValue : changeInValue * pow(2, 10 * (ticks / durationTicks - 1)) + beginningValue;
}

double Easing::easeOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return (ticks == durationTicks) ? beginningValue + changeInValue : changeInValue * (-pow(2, -10 * ticks / durationTicks) + 1) + beginningValue;
}

double Easing::easeInOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if (ticks == 0)
	{
	
		return beginningValue;
	}
	if (ticks == durationTicks)
	{
	
		return beginningValue + changeInValue;
	}
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * pow(2, 10 * (ticks - 1)) + beginningValue;
	}
	return changeInValue / 2 * (-pow(2, -10 * --ticks) + 2) + beginningValue;
}

double Easing::easeInCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return -changeInValue * (sqrt(1 - (ticks /= durationTicks) * ticks) - 1) + beginningValue;
}

double Easing::easeOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue * sqrt(1 - (ticks = ticks / durationTicks - 1) * ticks) + beginningValue;
}

double Easing::easeInOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return -changeInValue / 2 * (sqrt(1 - ticks * ticks) - 1) + beginningValue;
	}

	return changeInValue / 2 * (sqrt(1 - (ticks -= 2) * ticks) + 1) + beginningValue;
}

double Easing::easeInElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	double ticks = ticksPassed;
	if (ticks == 0)
	{
	
		return beginningValue;
	}
	if ((ticks /= durationTicks) == 1)
	{
	
		return beginningValue + changeInValue;
	}

	double period = durationTicks * .3;
	double s = 0;

	if (amplitude < abs(changeInValue))
	{
	
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{
	
		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	return -(amplitude * pow(2, 10 * (ticks -= 1)) * sin((ticks * durationTicks - s) * (2 * M_PI) / period)) + beginningValue;
}

double Easing::easeOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	double ticks = ticksPassed;
	if (ticks == 0)
	{
	
		return beginningValue;
	}
	if ((ticks /= durationTicks) == 1)
	{
	
		return beginningValue + changeInValue;
	}

	double period = durationTicks * .3;
	double s = 0;

	if (amplitude < abs(changeInValue))
	{
	
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{
	
		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	return amplitude * pow(2, -10 * ticks) * sin((ticks * durationTicks - s) * (2 * M_PI) / period) + changeInValue + beginningValue;
}

double Easing::easeInOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	double ticks = ticksPassed;
	if (ticks == 0)
	{
	
		return beginningValue;
	}
	if ((ticks /= durationTicks / 2) == 2)
	{
	
		return beginningValue + changeInValue;
	}
	double period = durationTicks * (.3 * 1.5);

	double s = 0;

	if (amplitude < abs(changeInValue))
	{
	
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{

		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	if (ticks < 1)
	{

		return -.5 * (amplitude * pow(2, 10 * (ticks -= 1)) * sin((ticks * durationTicks - s) * (2 * M_PI) / period)) + beginningValue;
	}

	return amplitude * pow(2, -10 * (ticks -= 1)) * sin((ticks * durationTicks - s) * (2 * M_PI) / period) * .5 + changeInValue + beginningValue;
}

double Easing::easeInBackSlingshot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	double overshootAmount = 1.70158;
	return changeInValue * (ticks /= durationTicks) * ticks * ((overshootAmount + 1) * ticks - overshootAmount) + beginningValue;
}

double Easing::easeOutBackOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	double overshootAmount = 1.70158;
	return changeInValue * ((ticks = ticks / durationTicks - 1) * ticks * ((overshootAmount + 1) * ticks + overshootAmount) + 1) + beginningValue;
}

double Easing::easeInOutBackSlingshotOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	double overshootAmount = 1.70158;
	if ((ticks /= durationTicks / 2) < 1)
	{
	
		return changeInValue / 2 * (ticks * ticks * (((overshootAmount *= (1.525)) + 1) * ticks - overshootAmount)) + beginningValue;
	}
	return changeInValue / 2 * ((ticks -= 2) * ticks * (((overshootAmount *= (1.525)) + 1) * ticks + overshootAmount) + 2) + beginningValue;
}

double Easing::easeInParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	return changeInValue - easeOutParabolicBounce(durationTicks - ticks, 0, changeInValue, durationTicks) + beginningValue;
}

double Easing::easeOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if ((ticks /= durationTicks) < (1 / 2.75))
	{
	
		return changeInValue * (7.5625 * ticks * ticks) + beginningValue;
	}
	else if (ticks < (2 / 2.75))
	{
	
		return changeInValue * (7.5625 * (ticks -= (1.5 / 2.75)) * ticks + .75) + beginningValue;
	}
	else if (ticks < (2.5 / 2.75))
	{
	
		return changeInValue * (7.5625 * (ticks -= (2.25 / 2.75)) * ticks + .9375) + beginningValue;
	}
	else
	{

		return changeInValue * (7.5625 * (ticks -= (2.625 / 2.75)) * ticks + .984375) + beginningValue;
	}
}

double Easing::easeInOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double ticks = ticksPassed;
	if (ticks < durationTicks / 2)
	{
	
		return easeInParabolicBounce(ticks * 2, 0, changeInValue, durationTicks) * .5 + beginningValue;
	}
	return easeOutParabolicBounce(ticks * 2 - durationTicks, 0, changeInValue, durationTicks) * .5 + changeInValue * .5 + beginningValue;
}

#pragma clang diagnostic pop
