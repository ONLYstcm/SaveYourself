#include <cmath>
#include "enemies.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace enemies
{
	
	void missile::create(int x, int y, double boundx, double boundy,short radius) { //This is the 'missile' object itself
		particle.create(boundx, boundy, radius);
		particle.initialise(x,y);
		visible = true;
		render();
		}
	void spaceship::create(double boundx, double boundy) { //This is the 'missile' object itself
		particle.create(boundx, boundy);
		particle.initialise(2, 2);
		visible = true;
		render();
	}
	void missile::render() {//refresh missile bitmap
			if (visible) {
				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius(), al_map_rgb(250, 50, 50)); //Draw red circle
				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius()*0.5, al_map_rgb(50, 50, 50)); //Draw black circle
			}
		} 

	void spaceship::render() {//refresh missile bitmap
		if (visible) {
			angle = (-particle.getAngle()) + 1.5708;
			al_draw_rotated_bitmap(spaceshipimage, 20, 16, particle.getVector('P').x, particle.getVector('P').y, angle, NULL); //Rotate bitmap in direction of mouse

		}
	}

	void missile::destroy() {
		visible = false;
		}
	void spaceship::destroy() {
		visible = false;
	}

	};