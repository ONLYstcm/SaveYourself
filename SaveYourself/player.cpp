#include <cmath>
#include "player.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace player
{
	void playership::create(double boundx, double boundy) { //This is the 'missile' object itself
		particle.create(boundx, boundy);
		particle.initialise(300, 300);
		visible = true;
		render();
	}

	void playership::render() {//refresh missile bitmap
		if (visible) {
			angle = (-particle.getAngle()) + 1.5708;
			al_draw_rotated_bitmap(playershipimage, 16, 16, particle.getVector('P').x, particle.getVector('P').y, angle, NULL); //Rotate bitmap in direction of mouse
		}
	}

	void playership::destroy() {
		visible = false;
	}

	PowerUps::PowerUps()
	{
		particle.initialise(300, 0);
	}

	void PowerUps::create(int x, int y, double boundx, double boundy, short radius) { //This is the 'missile' object itself
		particle.create(boundx, boundy, radius);
		particle.initialise(x, y);
		visible = true;
		render();
	}

	void PowerUps::render() {//refresh missile bitmap
		if (visible) {
			al_draw_bitmap(shieldimage, particle.getVector('P').x, particle.getVector('P').y, NULL); //Draw black circle
		}
	}

	void PowerUps::move() {
		particle.move('s', 0, 1);
		if (particle.getVector('P').y > GAMING_WINDOW_HEIGHT)
			visible = false;
	}
	void PowerUps::destroy() {
		visible = false;

	}
};