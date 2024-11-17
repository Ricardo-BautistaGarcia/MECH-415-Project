
#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h>

#include "2D_graphics.h"

#include "timer.h"

#include "game_pad.h"

#include "Avatar.h"

using namespace std;

const double PI = 3.14159;

//define member functions of Avatar class


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
	double xv=X,yv=Y,theta_v=0.0,scale = 0.5;

	view(xv, yv, theta_v);
	draw_sprite(Id, X, Y, Theta, scale);
}

void Avatar::update()
{
	int i;
	int index, GS[N_GS];
	double fx, fy;
	
	// function returns 0 if success and 1 if not connected / error
	// array GS[i] = 0 if the game pad is not connected / error
	index = 1; // gamepad #1
	gamepad_state(GS,index);
	
	fx = GS[LEFT_STICK_X] / 1.0e6; // normalize -> -1 to 1

	fy = GS[LEFT_STICK_Y] / 1.0e6; // normalize

	// the if statements are to prevent motion if the stick
	// just jiggles a small amount -- ie a small dead-zone
	
	if( abs(fx) > 0.1 )	X += Speed*fx;
	
	if( abs(fy) > 0.1 ) Y += Speed*fy;
	
	if ( (abs(fx) > 0.1) || (abs(fy) > 0.1) ) Theta = atan2(fy,fx);
	
	// keboard input below for people without gamepads ///
	
	if( KEY('L') ) {
		X += Speed;
		Theta = 0;
	}
	
	if( KEY('J') ) {
		X -= Speed;
		Theta = 3.14159;
	}
	
	if( KEY('I') ) {
		Y += Speed;
		Theta = 3.14159/2;
	}
	
	if( KEY('K') ) { 
		Y -= Speed;
		Theta = -3.14159/2;
	}
		
	/////////////////////////////////////////////////////
	

	// print out gamepad state for testing purposes
	for(i=0;i<N_GS;i++) {
		cout << GS[i] << " ";
	}
	cout << "\n";

	
}


