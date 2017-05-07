#pragma once
#include <cmath>
#include "reeko_physics_engine.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>
#define FPS 60
const short amo = 200;


namespace nukes
{

	class nukes
	{
		/*
		This class is the class for the player ship
		*/
	public:
		void create(double boundx, double boundy,Vector,Vector); //This is the 'missile' object itself
		void nukes::shoot(double boundx, double boundy, Vector pos, Vector aim);
		void render(); //refresh spaceship
		void destroy();
		physics::object particle[amo];
		ALLEGRO_BITMAP* playershipimage = al_load_bitmap("nukes.png");
		double angle1;
		short bullets=0;
		string identity="nuke";
	private:
		bool visible = true;
		double dt;
	};

}