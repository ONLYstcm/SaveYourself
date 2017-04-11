#pragma once
#include <cmath>
#include "reeko_physics_engine.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>
#define FPS 60


namespace enemies
{
	class missile
		/*
			This class is the class for the random missiles coming at the player
		*/
	{
	public:
		void create(short radius); //This is the 'missile' object itself
		void render(); //refresh missile
		//void setDirection(short x, short y); //point to the mouse
		//void move();
		void destroy();
		physics::object particle;

	private:
		bool visible = true;
		double dt;
	};

	class spaceship
	{
		/*
		This class is the class for the spaceship
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