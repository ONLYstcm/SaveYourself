#include <cmath>
#include "nukes.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>


namespace nukes
{
	void nukes::shoot(double boundx, double boundy, Vector pos, Vector aim)
	{
		if (bullets < amo) {
			particle[bullets].create(boundx, boundy);
			particle[bullets].initialise(pos.x, pos.y);
			particle[bullets].setDirection(aim);
			bullets++;
			render();
		}
	}

	void nukes::fire(double boundx, double boundy, Vector pos, Vector aim) {
		atom[enemybullets].create(boundx, boundy);
		atom[enemybullets].initialise(pos.x, pos.y,4,4);
		atom[enemybullets].setDirection(aim);
		enemybullets++;
		enemyrender();
	}

	void nukes::enemyrender() {//refresh missile bitmap
		if (visible) {
			for (int i = 0; i < enemybullets; i++) {
				atom[i].travel(0, 0, atom[i].getVector('U').x, atom[i].getVector('U').y);
				al_draw_filled_circle(atom[i].getVector('P').x, atom[i].getVector('P').y, 4, al_map_rgb(255, 0, 255));
			}
		}
	}

	void nukes::render() {//refresh missile bitmap
		if (visible) {
			for (int i = 0; i < bullets; i++) {
				particle[i].travel(1, 1, particle[i].getVector('U').x, particle[i].getVector('U').y);
				al_draw_filled_circle(particle[i].getVector('P').x, particle[i].getVector('P').y, 2, al_map_rgb(255, 255, 255));
			}
		}
	}

	void nukes::destroy() {
		visible = false;
	}
};