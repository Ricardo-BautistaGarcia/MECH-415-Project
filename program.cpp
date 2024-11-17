#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h>

#include "2D_graphics.h"

#include "timer.h"

#include "game_pad.h"

//#include "Avatar.h"

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



Avatar::Avatar(double x, double y, double theta, double speed, int id)
{
	X = x;
	Y = y;
	Theta = theta;
	Speed = speed;
	Id = id;
}

/* in case we need a sparate function for the view part.
void Avatar::camera()
{
	double theta_v = 0.0;

	view(X, Y, theta_v);
}
*/

void Avatar::draw()
{
	double xv = X, yv = Y, theta_v = 0.0, scale = 0.5;

	view(xv, yv, theta_v);
	draw_sprite(Id, X, Y, Theta, scale);
}

void Avatar::update()
{
	int i;
	int index, GS[N_GS];
	double fleftx, flefty,frightx,frighty;

	// function returns 0 if success and 1 if not connected / error
	// array GS[i] = 0 if the game pad is not connected / error
	index = 1; // gamepad #1
	gamepad_state(GS, index);

	fleftx = GS[LEFT_STICK_X] / 1.0e6; // normalize -> -1 to 1

	flefty = GS[LEFT_STICK_Y] / 1.0e6; // normalize

	frightx = GS[RIGHT_STICK_X] / 1.0e6; // normalize

	frighty = GS[RIGHT_STICK_Y] / 1.0e6; // normalize

	// the if statements are to prevent motion if the stick
	// just jiggles a small amount -- ie a small dead-zone

	if (abs(fleftx) > 0.1)	X += Speed * fleftx;

	if (abs(flefty) > 0.1) Y += Speed * flefty;

	if ((abs(frightx) > 0.1) || (abs(frighty) > 0.1)) Theta = atan2(frighty, frightx);

	// keboard input below for people without gamepads ///

	if (KEY('L')) {
		X += Speed;
		Theta = 0;
	}

	if (KEY('J')) {
		X -= Speed;
		Theta = 3.14159;
	}

	if (KEY('I')) {
		Y += Speed;
		Theta = 3.14159 / 2;
	}

	if (KEY('K')) {
		Y -= Speed;
		Theta = -3.14159 / 2;
	}

	/////////////////////////////////////////////////////


	// print out gamepad state for testing purposes
	for (i = 0; i < N_GS; i++) {
		cout << GS[i] << " ";
	}
	cout << "\n";


}





class Background {

public:

	double Xb;
	double Yb;
	double Theta_b;
	double Scale_b;
	double ID_b;

	Background(double xb, double yb, double theta_b, double scale, int id_background);


	void draw();
};


Background::Background(double xb, double yb, double theta_b, double scale, int id_background)
{
	Xb = xb;
	Yb = yb;
	Theta_b = theta_b;
	Scale_b = scale;
	ID_b = id_background;
}


void Background::draw()
{
	draw_sprite(ID_b, Xb, Yb, Theta_b, Scale_b);
}



int main()
{
	double t;
	int id_avatar, id_background;
	double x, y, scale_b, theta, speed;
	double xb, yb, theta_b, xv, yv, theta_v;
	double width, height;


	//Background parameters

	width = 1500;
	height = 800;
	xb = 0.5 * (width - 1);
	yb = 0.5 * (height - 1);
	theta_b = 0.0;
	scale_b = 10;


	//avatar parameters
	x = 750;
	y = 400;
	theta = 0;
	speed = 5;



	initialize_graphics();




	// create all sprites before entering the loop below

	create_sprite("background1.jpg", id_background);
	create_sprite("Aang.png", id_avatar);

	// declare avatar object
	Avatar aang(x, y, theta, speed, id_avatar);

	// declare background object

	Background Omashu(xb, yb, theta_b, scale_b, id_background);





	// drawing / animation loop
	while (1) {

		// read the computer clock 
		// (units of seconds, 0.1 microsecond resolution)
		t = high_resolution_time();

		// clear 2D graphics window
		clear();


		// draw background

		Omashu.draw();

		//update avatar camera view

		//aang.view();

		// update avatar position
		aang.update();


		// draw avatar
		aang.draw();

		// update 2D graphics window
		update();

	} // end while(1)

	return 0;
}
