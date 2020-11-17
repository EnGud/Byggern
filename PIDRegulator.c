#include <stdio.h>
#define DATATYPE double

/* A PID regulator based on a teachings from REGTEK at NTNU
   The pGain (KP) controls the simple gain of the circuit.
   The IGain is the integral which integrates over time, leading to long term stability
   The DGain is the derivative which checks the "rise" of the circuit, and can make quick adjustments for instance.

   It is designed with future proofing in mind such as bias and correction.

   The values seen in this file were used during testing, and can be seen in the monitor during a run.

   The datatype may be quickly tuned for implementation with the define, however during testing precission was needed and thus double was used.
*/

DATATYPE preError = 0; // Errors before startup
DATATYPE integralPrior = 0; // Memory for integral
DATATYPE bias = 0;	// General bias

// these values must be variated for a given control jobb
DATATYPE pGain = 0.5; //KP (simple gain)
DATATYPE IGain = 4;	  //Integration 
DATATYPE DGain = 0;	  //Derivative
DATATYPE timeValue = 0.1; // The time constant which affects the integration and derivation time.

// These are the values we wish to hit and the current values.
DATATYPE targetValue = 100;
DATATYPE currentValue = 80;

// These are 
DATATYPE integral;
DATATYPE derivative;

// Test setting in main loop
void main() {
	printf("target is: %f \n", targetValue);
	printf("start value is: %f \n", currentValue);
	printf("Our parameters are: pGain: %f, IGain: %f, DGain:%f, timeValue: %f \n", pGain, IGain, DGain, timeValue);
	printf("------------------------------------------------------------------\n");

	printf("results from regulation are as following \n");

	for (int i = 0; i < 100; i++) {
		printf("We have %f: \n", currentValue);
		currentValue = pidRegulator(targetValue, currentValue);
	}
}

int pidRegulator(double target, double measure) {
	// This is the mathematical function that finds the output as close as possible to the desired value.
	DATATYPE error = 1.0 * (target - measure); // Calculates the error as the difference between target and measure.
	integral = integralPrior + error * timeValue; //Finds the integral that is to be used.
	derivative = (error - preError) / timeValue; // Finds the derivative that is to be used.
	preError = error;	//Stores the previous error
	integralPrior = integral;	//Stores the current integral to former value, for memory.
	DATATYPE correciton = 1.0 * (pGain * error + DGain * derivative + IGain * integral + bias); //The main calculation, here the correction is done.
	return correciton;
}