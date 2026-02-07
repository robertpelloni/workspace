package easing;

//http://www.robertpenner.com/easing/

/*
TERMS OF USE - EASING EQUATIONS

Open source under the BSD License.

Copyright © 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
	Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

public class Easing
{



	// simple linear tweening - no easing
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	static public double linearTween(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*ticksPassed/durationTicks + beginningValue;
	}


	///////////// QUADRATIC EASING: ticksPassed^2 ///////////////////

	// quadratic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds
	static public double easeInQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*(ticksPassed/=durationTicks)*ticksPassed + beginningValue;
	}

	// quadratic easing out - decelerating to zero velocity
	static public double easeOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return -changeInValue *(ticksPassed/=durationTicks)*(ticksPassed-2) + beginningValue;
	}

	// quadratic easing in/out - acceleration until halfway, then deceleration
	static public double easeInOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2*ticksPassed*ticksPassed + beginningValue;
		return -changeInValue/2 * ((--ticksPassed)*(ticksPassed-2) - 1) + beginningValue;
	}


	///////////// CUBIC EASING: ticksPassed^3 ///////////////////////

	// cubic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static public double easeInCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*(ticksPassed/=durationTicks)*ticksPassed*ticksPassed + beginningValue;
	}

	// cubic easing out - decelerating to zero velocity
	static public double easeOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*((ticksPassed=ticksPassed/durationTicks-1)*ticksPassed*ticksPassed + 1) + beginningValue;
	}

	// cubic easing in/out - acceleration until halfway, then deceleration
	static public double easeInOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2*ticksPassed*ticksPassed*ticksPassed + beginningValue;
		return changeInValue/2*((ticksPassed-=2)*ticksPassed*ticksPassed + 2) + beginningValue;
	}


	///////////// QUARTIC EASING: ticksPassed^4 /////////////////////

	// quartic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static public double easeInQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*(ticksPassed/=durationTicks)*ticksPassed*ticksPassed*ticksPassed + beginningValue;
	}

	// quartic easing out - decelerating to zero velocity
	static public double easeOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return -changeInValue * ((ticksPassed=ticksPassed/durationTicks-1)*ticksPassed*ticksPassed*ticksPassed - 1) + beginningValue;
	}

	// quartic easing in/out - acceleration until halfway, then deceleration
	static public double easeInOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2*ticksPassed*ticksPassed*ticksPassed*ticksPassed + beginningValue;
		return -changeInValue/2 * ((ticksPassed-=2)*ticksPassed*ticksPassed*ticksPassed - 2) + beginningValue;
	}


	///////////// QUINTIC EASING: ticksPassed^5  ////////////////////

	// quintic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static public double easeInQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*(ticksPassed/=durationTicks)*ticksPassed*ticksPassed*ticksPassed*ticksPassed + beginningValue;
	}

	// quintic easing out - decelerating to zero velocity
	static public double easeOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue*((ticksPassed=ticksPassed/durationTicks-1)*ticksPassed*ticksPassed*ticksPassed*ticksPassed + 1) + beginningValue;
	}

	// quintic easing in/out - acceleration until halfway, then deceleration
	static public double easeInOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2*ticksPassed*ticksPassed*ticksPassed*ticksPassed*ticksPassed + beginningValue;
		return changeInValue/2*((ticksPassed-=2)*ticksPassed*ticksPassed*ticksPassed*ticksPassed + 2) + beginningValue;
	}



	///////////// SINUSOIDAL EASING: sin(ticksPassed) ///////////////

	// sinusoidal easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static public double easeInSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return -changeInValue * Math.cos(ticksPassed/durationTicks * (Math.PI/2)) + changeInValue + beginningValue;
	}

	// sinusoidal easing out - decelerating to zero velocity
	static public double easeOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue * Math.sin(ticksPassed/durationTicks * (Math.PI/2)) + beginningValue;
	}

	// sinusoidal easing in/out - accelerating until halfway, then decelerating
	static public double easeInOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return -changeInValue/2 * (Math.cos(Math.PI*ticksPassed/durationTicks) - 1) + beginningValue;
	}


	///////////// EXPONENTIAL EASING: 2^ticksPassed /////////////////

	// exponential easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static public double easeInExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return (ticksPassed==0) ? beginningValue : changeInValue * Math.pow(2, 10 * (ticksPassed/durationTicks - 1)) + beginningValue;
	}

	// exponential easing out - decelerating to zero velocity
	static public double easeOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks) {
		return (ticksPassed==durationTicks) ? beginningValue+changeInValue : changeInValue * (-Math.pow(2, -10 * ticksPassed/durationTicks) + 1) + beginningValue;
	}

	// exponential easing in/out - accelerating until halfway, then decelerating
	static public double easeInOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if (ticksPassed==0) return beginningValue;
		if (ticksPassed==durationTicks) return beginningValue+changeInValue;
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2 * Math.pow(2, 10 * (ticksPassed - 1)) + beginningValue;
		return changeInValue/2 * (-Math.pow(2, -10 * --ticksPassed) + 2) + beginningValue;
	}


	/////////// CIRCULAR EASING: sqrt(1-ticksPassed^2) //////////////

	// circular easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static public double easeInCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return -changeInValue * (Math.sqrt(1 - (ticksPassed/=durationTicks)*ticksPassed) - 1) + beginningValue;
	}

	// circular easing out - decelerating to zero velocity
	static public double easeOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue * Math.sqrt(1 - (ticksPassed=ticksPassed/durationTicks-1)*ticksPassed) + beginningValue;
	}

	// circular easing in/out - acceleration until halfway, then deceleration
	static public double easeInOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks/2) < 1) return -changeInValue/2 * (Math.sqrt(1 - ticksPassed*ticksPassed) - 1) + beginningValue;

		return changeInValue/2 * (Math.sqrt(1 - (ticksPassed-=2)*ticksPassed) + 1) + beginningValue;
	}


	/////////// ELASTIC EASING: exponentially decaying sine wave  //////////////

	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks, a: amplitude (optional), p: period (optional)
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds

	static public double easeInElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
	{
		if (ticksPassed==0) return beginningValue;
		if ((ticksPassed/=durationTicks)==1) return beginningValue+changeInValue;

		double period=durationTicks*.3;
		double s=0;

		if (amplitude < Math.abs(changeInValue))
		{
			amplitude=changeInValue;
			s=period/4;
		}
		else s = period/(2*Math.PI) * Math.asin (changeInValue/amplitude);

		return -(amplitude*Math.pow(2,10*(ticksPassed-=1)) * Math.sin( (ticksPassed*durationTicks-s)*(2*Math.PI)/period )) + beginningValue;
	}

	static public double easeOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
	{
		if (ticksPassed==0) return beginningValue;
		if ((ticksPassed/=durationTicks)==1) return beginningValue+changeInValue;

		double period=durationTicks*.3;
		double s = 0;

		if (amplitude < Math.abs(changeInValue))
		{
			amplitude=changeInValue;
			s=period/4;
		}
		else s = period/(2*Math.PI) * Math.asin (changeInValue/amplitude);

		return amplitude*Math.pow(2,-10*ticksPassed) * Math.sin( (ticksPassed*durationTicks-s)*(2*Math.PI)/period ) + changeInValue + beginningValue;
	}

	static public double easeInOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
	{
		if (ticksPassed==0) return beginningValue;
		if ((ticksPassed/=durationTicks/2)==2) return beginningValue+changeInValue;
		double period=durationTicks*(.3*1.5);

		double s = 0;

		if (amplitude < Math.abs(changeInValue))
		{
			amplitude=changeInValue; s=period/4;
		}
		else s = period/(2*Math.PI) * Math.asin (changeInValue/amplitude);

		if (ticksPassed < 1) return -.5*(amplitude*Math.pow(2,10*(ticksPassed-=1)) * Math.sin( (ticksPassed*durationTicks-s)*(2*Math.PI)/period )) + beginningValue;

		return amplitude*Math.pow(2,-10*(ticksPassed-=1)) * Math.sin( (ticksPassed*durationTicks-s)*(2*Math.PI)/period )*.5 + changeInValue + beginningValue;
	}


	/////////// BACK EASING: overshooting cubic easing: (s+1)*ticksPassed^3 - s*ticksPassed^2  //////////////

	// back easing in - backtracking slightly, then reversing direction and moving to target
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks, s: overshoot amount (optional)
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds
	// s controls the amount of overshoot: higher s means greater overshoot
	// s has a default value of 1.70158, which produces an overshoot of 10 percent
	// s==0 produces cubic easing with no overshoot
	static public double easeInBackSlingshot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		double overshootAmount = 1.70158;
		return changeInValue*(ticksPassed/=durationTicks)*ticksPassed*((overshootAmount+1)*ticksPassed - overshootAmount) + beginningValue;
	}

	// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target
	static public double easeOutBackOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		double overshootAmount = 1.70158;
		return changeInValue*((ticksPassed=ticksPassed/durationTicks-1)*ticksPassed*((overshootAmount+1)*ticksPassed + overshootAmount) + 1) + beginningValue;
	}

	// back easing in/out - backtracking slightly, then reversing direction and moving to target,
	// then overshooting target, reversing, and finally coming back to target
	static public double easeInOutBackSlingshotOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		double overshootAmount = 1.70158;
		if ((ticksPassed/=durationTicks/2) < 1) return changeInValue/2*(ticksPassed*ticksPassed*(((overshootAmount*=(1.525))+1)*ticksPassed - overshootAmount)) + beginningValue;
		return changeInValue/2*((ticksPassed-=2)*ticksPassed*(((overshootAmount*=(1.525))+1)*ticksPassed + overshootAmount) + 2) + beginningValue;
	}


	/////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////

	// bounce easing in
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static public double easeInParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		return changeInValue - easeOutParabolicBounce (durationTicks-ticksPassed, 0, changeInValue, durationTicks) + beginningValue;
	}

	// bounce easing out
	static public double easeOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if ((ticksPassed/=durationTicks) < (1/2.75)) {
			return changeInValue*(7.5625*ticksPassed*ticksPassed) + beginningValue;
		} else if (ticksPassed < (2/2.75)) {
			return changeInValue*(7.5625*(ticksPassed-=(1.5/2.75))*ticksPassed + .75) + beginningValue;
		} else if (ticksPassed < (2.5/2.75)) {
			return changeInValue*(7.5625*(ticksPassed-=(2.25/2.75))*ticksPassed + .9375) + beginningValue;
		} else {
			return changeInValue*(7.5625*(ticksPassed-=(2.625/2.75))*ticksPassed + .984375) + beginningValue;
		}
	}

	// bounce easing in/out
	static public double easeInOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
	{
		if (ticksPassed < durationTicks/2) return easeInParabolicBounce (ticksPassed*2, 0, changeInValue, durationTicks) * .5 + beginningValue;
		return easeOutParabolicBounce (ticksPassed*2-durationTicks, 0, changeInValue, durationTicks) * .5 + changeInValue*.5 + beginningValue;
	}


}



