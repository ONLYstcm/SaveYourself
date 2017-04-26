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
		void create(); //This is the 'missile' object itself
		void render(); //refresh spaceship
		void destroy();
		physics::object particle;
		ALLEGRO_BITMAP* playershipimage = al_load_bitmap("playa.png");


	private:
		bool visible = true;
		double dt;
		double angle;
	};

}