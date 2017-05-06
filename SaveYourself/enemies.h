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
		void create(int x, int y, double boundx, double boundy, short radius); //This is the 'missile' object itself
		void render(); //refresh missile
		void destroy();
		bool isVisible();
		physics::object particle;
		string identity = "missile";

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
		void create(double boundx, double boundy); //This is the 'missile' object itself
		void render(); //refresh spaceship
		void destroy();
		bool isVisible();
		physics::object particle;
		ALLEGRO_BITMAP* spaceshipimage = al_load_bitmap("enemyship.png");
		string identity = "enemy ship";
	private:
		bool visible = true;
		double dt;
		double angle;
	};
	
}