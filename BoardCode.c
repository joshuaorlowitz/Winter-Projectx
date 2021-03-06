#pragma config(Sensor, S2,     GyroScope,      sensorEV3_Gyro)
#pragma config(Sensor, S3,     UltraSonicSense, sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     ColorSense,     sensorEV3_Color)
#pragma config(Motor,  motorB,          LMotor,        tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          RMotor,        tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int turningPower = 100;
int straightPower = 40;
const tSensors SensorS2 = (tSensors) S2; //gyroscope
const tSensors SensorS3 = (tSensors) S3; //Ultrasonic sensor

void stopRobot() { //function to stop robot
	motor[LMotor] = 0;
	motor[RMotor] = 0;
	wait1Msec(1000);
}

void turnRight() { //function to turn the robot right
	resetGyro(S2);

	repeatUntil(getGyroDegrees(S2) > 70) { //turn '90' degrees
		motor[LMotor] = turningPower; //turning power must be high for
		motor[RMotor] = -turningPower;//gyro to accurately read angle
	}
	stopRobot();
}

void moveForward() { //function to move forward
	motor[LMotor] = straightPower;
	motor[RMotor] = straightPower;
}

void correctedMoveForward() { //function to correct for robot drifting
	resetGyro(S2);
	moveForward();
	wait1Msec(3000);
	stopRobot();

	while (true) {
		while (getGyroDegrees(SensorS2) == 0) {
			moveForward();
		}

		while (getGyroDegrees(SensorS2) < 0) {
			motor[LMotor] = straightPower+10;
			motor[RMotor] = straightPower;
		}

		while (getGyroDegrees(SensorS2) > 0) {
			motor[LMotor] = straightPower;
			motor[RMotor] = straightPower+10;
		}

	}
}


task main() {
	//4x5 board, MUST START ON BOTTOM LEFT HAND CORNER
	//OF BOARD...i.e. perpendicular to length

	float width = 21.59; //width of paper (short dimension)
	float length = 27.94; //length of paper (long dimension)
	float dShort = width/2; //half width
	float dLong = length/2; //half length

	//searching pattern based off of 8 moves; for a graphical
	//version of search pattern, see OneNote

	//move 1
	while(SensorValue(SensorS3) > dShort) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 2
	while(SensorValue(SensorS3) > dLong) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 3
	while(SensorValue(SensorS3) > dShort) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 4
	while(SensorValue(SensorS3) > dLong + length) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 5
	while(SensorValue(SensorS3) > dShort + width) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 6
	while(SensorValue(SensorS3) > dLong + length) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 7
	while(SensorValue(SensorS3) > dShort + width) {
		correctedMoveForward();
	}
	stopRobot();
	turnRight();

	//move 8
	while(SensorValue(SensorS3) > dLong + 2 * length) {
		correctedMoveForward();
	}
	stopRobot();

}//end main
