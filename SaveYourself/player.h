#pragma once
#include <cmath>
#include "reeko_physics_engine.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>
#define FPS 60


namespace player
{

	class playership
	{
		/*
		This class is the class for the player ship
		*/
	public:
		void create(double boundx, double boundy); //This is the 'player' object itself
		void render(); //refresh spaceship
		void destroy();
		physics::object particle;
		ALLEGRO_BITMAP* playershipimage = al_load_bitmap("playa.png");
		string identity = "player";
		int health = 50;

	private:
		bool visible = true;
		double dt;
		double angle;
	};

	class PowerUps

	{
	public:
		void create(int x, int y, double boundx, double boundy, short radius); //This is the 'missile' object itself
		void render(); //refresh missile
		void destroy();
		physics::object particle;
		ALLEGRO_BITMAP* shieldimage = al_load_bitmap("power up shield(1).png");
		string identity = "shield";
		void move();
		PowerUps();
		bool visible = true;
		bool enabled = false;



	private:

		double dt;


	};

}