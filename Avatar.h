//Avatar object


#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h>

#include "2D_graphics.h"

#include "timer.h"

#include "game_pad.h"

using namespace std;

const double PI = 3.14159;

class Avatar {

public:

	double X, Y; // position (pixels)
	double Theta; // angle (rad)
	double Speed; // speed (pixels/s)
	int Id; // sprite ID

	Avatar(double x, double y, double theta, double speed, int id);

	//View the avatar (in case we need a separate function)
	//void camera();

	// move and update pacman depending on the joystick input
	void update();

	// draw using 2D graphics lib 
	void draw();
};


