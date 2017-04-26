#include <cmath>
#include "player.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace player
{
	
	void playership::create() { //This is the 'missile' object itself
		particle.create();
		particle.initialise(300, 300);
		render();

	
		
	}

	void playership::render() {//refresh missile bitmap
		if (visible) {
			angle = (-particle.getAngle()) + 1.5708;
			al_draw_rotated_bitmap(playershipimage, 0, 0, particle.getVector('P').x, particle.getVector('P').y, angle, NULL); //Rotate bitmap in direction of mouse

		}
	}

	void playership::destroy() {
		visible = false;
	}


};