#include <cmath>
#include "nukes.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace nukes
{

	void nukes::create(Vector pos, double a) { //This is the 'missile' object itself
		particle.create();
		particle.initialise(pos.x, pos.y);
		angle1 = a;
		render();
	}

	void nukes::render() {//refresh missile bitmap
		if (visible) {
			//angle = (-particle.getAngle()) + 1.5708;
			//particle.move(1, tan(angle1));
			al_draw_rotated_bitmap(playershipimage, 0, 0, particle.getVector('P').x, particle.getVector('P').y, angle1, NULL); //Rotate bitmap in direction of mouse

		}
	}

	void nukes::destroy() {
		visible = false;
	}

	void nukes::move()
	{
		particle.move(1, tan(angle1));
	}
};