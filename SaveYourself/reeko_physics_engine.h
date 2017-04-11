#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <allegro5\allegro.h>
#include <allegro5\color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h> //Normal font
#include <allegro5\allegro_ttf.h> //True Type Font
#define GAMING_WINDOW_HEIGHT 600
#define GAMING_WINDOW_WIDTH 1024

struct Vector {
	double x;
	double y;
};

namespace physics {
	class object {
	private:
		Vector vel, accel, pos, unit_vec, forces,empty;
		ALLEGRO_BITMAP *image = NULL;
		short radius;
		double height, length, breadth;
		double mass;
		short reflex; //This is how fast the object will respond to change
		double angle;

	public:
		//Create new object
		void create(short r = 0, short reaction_time = 0, double m = 0, double hei = 0, double len = 0, double bre = 0, double theta =0) {
			radius = r;
			reflex = reaction_time;
			mass = m;
			height = hei;
			length = len;
			breadth = bre;
			angle = theta;
		}

		//Set physical parameters
		void initialise(double position_x = 1, double position_y = 1, double velocity_x = 1, double velocity_y = 1, double acceleration_x = 1, double acceleration_y = 1, double force_x = 1, double force_y = 1) {
			pos.x = position_x;
			pos.y = position_y;
			vel.x = velocity_x;
			vel.y = velocity_y;
			accel.x = acceleration_x;
			accel.y = acceleration_y;
			forces.x = force_x;
			forces.y = force_y;
		}

		//Move object constant velocity
		void move(char direction, double speed_x = 1, double speed_y = 1) {
			switch (direction)
			{
				//Move up
			case 'U':
			case 'u':
				pos.y -= speed_y;
				if (pos.y < 0)
					pos.y = 0;
				break;
				//Move down
			case 'D':
			case 'd':
				pos.y += speed_y;
				if (pos.y > GAMING_WINDOW_HEIGHT)
					pos.y = GAMING_WINDOW_HEIGHT;
				break;
				//Move left
			case 'L':
			case 'l':
				pos.x -= speed_x;
				if (pos.x < 0)
					pos.x = 0;
				break;
				//Move left
			case 'R':
			case 'r':
				pos.x += speed_x;
				cout << pos.x << endl;
				if (pos.x > GAMING_WINDOW_WIDTH)
					pos.x = GAMING_WINDOW_WIDTH;
				break;
			default:
				break;
			}
		}


		//Move object constant acceleration and direction
		void move(char direction, double speed_x = 1, double speed_y = 1, double acceleration_x = 1, double acceleration_y=1, double unit_x=1,double unit_y=1) {
			double vi;//Initial_velocity
			switch (direction)
			{
				//Move up
			case 'U':
			case 'u':
				vi = vel.y;
				vel.y += acceleration_y;
				pos.y -= ((vi + vel.y) / 2)*unit_y;
				if (pos.y < 0)
					pos.y = 0;
					vel.y = 0;
					accel.y = 0;
				break;
				//Move down
			case 'D':
			case 'd':
				vi = vel.y;
				vel.y += acceleration_y;
				pos.y += ((vi + vel.y) / 2)*unit_y;
				if (pos.y > GAMING_WINDOW_HEIGHT)
					pos.y = GAMING_WINDOW_HEIGHT;
					vel.y = 0;
					accel.y = 0;
				break;
				//Move left
			case 'L':
			case 'l':
				vi = vel.x;
				vel.x += acceleration_x;
				pos.x -= ((vi + vel.x) / 2)*unit_x;
				if (pos.x < 0)
					pos.x = 0;
					vel.x = 0;
					accel.x = 0;
				break;
				//Move left
			case 'R':
			case 'r':
				vi = vel.x;
				vel.x += acceleration_x;
				pos.x += ((vi + vel.x) / 2)*unit_x;
				if (pos.x > GAMING_WINDOW_WIDTH)
					pos.x = GAMING_WINDOW_WIDTH;
					vel.x = 0;
					accel.x = 0;
				break;
			default:
				break;
			}
		}


		//Returns attributes of a vector
		Vector getVector(char option) {
			switch (option)
			{
			case 'P':
			case 'p':
				return pos;
				break;
			case 'V':
			case 'v':
				return vel;
				break;
			case 'A':
			case 'a':
				return accel;
				break;
			case 'U':
			case 'u':
				return unit_vec;
				break;
			case 'F':
			case 'f':
				return forces;
				break;
			default:
				return empty;
				break;
			}
		}

		void setRadius(double r) {
			radius = r;
		}
		double getRadius() {
			return radius;
		}

		void setAngle(double theta) {
			angle = theta;
		}
		double getAngle() {
			return angle;
		}

		void setHeight(double hei) {
			height = hei;
		}
		double getHeight() {
			return height;
		}

		void setLength(double len) {
			length = len;
		}
		double getLength() {
			return length;
		}

		void setBreadth(double bre) {
			breadth = bre;
		}
		double getBreadth() {
			return breadth;
		}

		void setMass(double m) {
			mass = m;
		}
		double getMass() {
			return mass;
		}


		//Adds another vector
		void addVector(char option, struct Vector vector) {
			switch (option)
			{
			case 'P':
			case 'p':
				pos.x += vector.x;
				pos.y += vector.y;
				break;
			case 'V':
			case 'v':
				vel.x += vector.x;
				vel.y += vector.y;
				break;
			case 'A':
			case 'a':
				accel.x += vector.x;
				accel.y += vector.y;
				break;
			case 'U':
			case 'u':
				unit_vec.x += vector.x;
				unit_vec.y += vector.y;
				break;
			case 'F':
			case 'f':
				forces.x += vector.x;
				forces.y += vector.y;
				break;
			default:
				break;
			}
		}
	};
}