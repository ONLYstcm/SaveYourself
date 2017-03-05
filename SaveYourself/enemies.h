#pragma once
#include <cmath>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace enemies
{
	class missile
		/*
			This class is the class for the random missiles coming at the player
		*/
	{
	public:
		//Note: lookup rand() function to understand 42 & 54.6
		void create(ALLEGRO_DISPLAY *display, float initial_vx = 0, float initial_vy = 0); //This is the 'missile' object itself
		void update(ALLEGRO_DISPLAY *display); //refresh missile bitmap
		void attack(missile Missile, int level); //level determine how strong the attack will be
		void setDir(short x, short y);
		void advance_by_time(__int8 setpace, float speed); //to be used in the 'attack' function to make to object accelerate/deccelerate
		void destroy();

	private:
		__int8 pace=0;
		bool visible;
		float angle;
		float x_dir;
		float y_dir;
		short x_pos;
		short y_pos;
		float x_v;	//x velocity
		float y_v;	//y velocity
		ALLEGRO_BITMAP* image;
	};

	class spaceship
	{
		/*
		This class is the class for the random missiles coming at the player
		*/
	public:
		void create(float initial_vx = 0, float initial_vy = 0);
		void update(ALLEGRO_DISPLAY *display);
		void attack(spaceship Spaceship, int level);
		void advance_by_time(double dt);
	private:
		float x_pos;
		float y_pos;
		float x_v;
		float y_v;
		ALLEGRO_BITMAP* image;
	};
}