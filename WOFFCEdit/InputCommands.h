#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotateRight, rotateLeft, rotateUp, rotateDown;
	bool space;
	int mouseX;
	int mouseY;
	bool mouseLBDown;
	//Numerical keys
	bool numOne, numTwo, numThree, numFour, numFive, numSix, numSeven, numEight, numNine;
};
