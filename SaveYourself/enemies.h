#pragma once
#include <cmath>
#include "reeko_physics_engine.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "nukes.h"
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
		void setVisible(bool value);
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
		string identity = "enemy ship";
		void create(int x, int y, double boundx, double boundy, ALLEGRO_BITMAP* spaceshipimage); //This is the 'missile' object itself
		void render(ALLEGRO_BITMAP* spaceshipimage); //refresh spaceship
		void destroy();
		void shoot(double boundx, double boundy, Vector pos, Vector target);
		bool isVisible();
		void setVisible(bool value);
		physics::object particle;
		physics::object bullet;

	private:
		bool visible = false;
		double dt;
		double angle;
	};
	
}