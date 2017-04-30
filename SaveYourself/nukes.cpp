#include <cmath>
#include "nukes.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>


namespace nukes
{/*
	void nukes::create(double boundx, double boundy, Vector pos, Vector aim,short bullets=2000) { //This is the 'missile' object itself
		amo = bullets;
		particle.create(boundx, boundy);
		particle.initialise(pos.x, pos.y);
		//double a
		//angle1 = atan2(particle.getVector('P').y - (aim.y), (aim.x) - particle.getVector('P').x);
		visible = true;
		//render();
	}
	*/

	void nukes::shoot(double boundx, double boundy, Vector pos, Vector aim)
	{
		if (bullets < amo) {
			//visible = true;
			//amo++;
			particle[bullets].create(boundx, boundy);
			particle[bullets].initialise(pos.x, pos.y);
			particle[bullets].setDirection(aim);
			bullets++;
			render();
		}
	}

	void nukes::render() {//refresh missile bitmap
		if (visible) {
			//angle = (-particle.getAngle()) + 1.5708;
			//particle.move(1, tan(angle1));
			for (int i = 0; i < bullets; i++) {
				particle[i].travel(1, 1, 1, 1, 1, 1, particle[i].getVector('U').x, particle[i].getVector('U').y);
				al_draw_filled_circle(particle[i].getVector('P').x, particle[i].getVector('P').y, 2, al_map_rgb(255, 255, 255));
			}
			//al_draw_rotated_bitmap(playershipimage, 0, 0, particle.getVector('P').x, particle.getVector('P').y, angle1, NULL); //Rotate bitmap in direction of mouse
		}
	}

	void nukes::destroy() {
		visible = false;
	}
/*
	void nukes::move(physics::object &shooter)
	{
		particle[i].move(1, tan(angle1));
	}
	*/
};