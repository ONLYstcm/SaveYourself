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
		//boundx and bouny is slight smaller than the size of the image used (look at dimensions of the actual picture)
		particle.initialise(x,y);
		visible = true;
		render();
		}
	void spaceship::create(int x, int y, double boundx, double boundy, ALLEGRO_BITMAP* spaceshipimage) { //This is the 'spaceship' object itself
		particle.create(boundx, boundy);
		particle.initialise(x, y);
		visible = true;
		render(spaceshipimage);
	}
	void missile::render() {//refresh missile bitmap
			if (visible) {
				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius(), al_map_rgb(250, 50, 50)); //Draw red circle
				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius()*0.5, al_map_rgb(50, 50, 50)); //Draw black circle
			}
		} 

	void spaceship::render(ALLEGRO_BITMAP* spaceshipimage) {//refresh missile bitmap
		if (visible) {
			angle = 1.5708 - particle.getAngle();
			al_draw_rotated_bitmap(spaceshipimage, 20, 16, particle.getVector('P').x, particle.getVector('P').y, angle, NULL); //Rotate bitmap in direction
		}
	}
	
	void spaceship::shoot(double boundx, double boundy, Vector pos, Vector target) {
		bullet.create(boundx, boundy);
		bullet.initialise(pos.x, pos.y);
		bullet.setDirection(target);
		bullet.travel(0, 0, bullet.getVector('U').x, bullet.getVector('U').y);
		al_draw_filled_circle(bullet.getVector('P').x, bullet.getVector('P').y, 2, al_map_rgb(255, 0, 255));
	}

	void missile::setVisible(bool value) {
		visible = value;
	}

	void spaceship::setVisible(bool value) {
		visible = value;
	}

	bool missile::isVisible() {
		return visible;
	}

	bool spaceship::isVisible() {
		return visible;
	}

	void missile::destroy() {
		particle.initialise(0, 0, 0, 0, 0, 0, 0, 0); //Place object in corner and keep it there
		visible = false;
		}
	void spaceship::destroy() {
		particle.initialise(0,0,0,0,0,0,0,0); //Place object in corner and keep it there
		visible = false;
	}

	};