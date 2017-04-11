#include <cmath>
#include "enemies.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

namespace enemies
{
	
	void missile::create(short radius) { //This is the 'missile' object itself
		particle.create(radius);
		particle.initialise(20, 20);
		render();
		}

	void missile::render() {//refresh missile bitmap
			if (visible) {
				
				/*
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_translate_transform(&trans, -pos.x, -pos.y);
				al_rotate_transform(&trans, angle);
				al_translate_transform(&trans, pos.x, pos.y);
				al_use_transform(&trans);

				// Draw whatevs here
				al_draw_filled_triangle(pos.x - 2*radius, pos.y, pos.x, pos.y - 2 * radius, pos.x + 2 * radius, pos.y, al_map_rgb(255, 0, 0));
				al_identity_transform(&trans);
				al_use_transform(&trans);
				*/// Turn off the rotation 

				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius(), al_map_rgb(250, 50, 50)); //Draw red circle
				al_draw_filled_circle(particle.getVector('P').x, particle.getVector('P').y, particle.getRadius()*0.5, al_map_rgb(50, 50, 50)); //Draw black circle
				//old_angle = angle;
			}
		} 

		/*Vector pullFromUser = arrow.head - arrow.tail;
		pullFromUser.trim(1);
		ball.particle.addForce(pullFromUser);
		ball.particle.integrate(dt);
		ball.particle.clearResultant();*/

		//float old_angle=0;

	/*
	void missile::setDirection(short x, short y){
			if (visible) {

				forces.x += (x - pos.x);
				forces.y += (pos.y - y);
				accel.x = forces.x / mass;
				accel.y = forces.y / mass;

				angle = atan2(pos.y - (y), (x)-pos.x);	//Get angle from missile to mouse icon
				dir.x = cos(angle);
				dir.y = sin(angle);
				/*if (pos.x == x || pos.y == y) //Collosion detection
				destroy();
				}
			}
		}
		*/

		/*
	void  missile::move() { //to be used in the 'attack' function to make to object accelerate/deccelerate
		
				This scales the movement of the rocket according to the framrate
						Framrate: 0.02 seconds
						Setpace: 10
						Therefore missile will move after 10*o.o2 seconds = 0.1 second
						
				//if (pace >= setpace) {
					pos.x += (vel.x*dt + (0.5*accel.x*dt*dt))*dir.x;
					pos.y -= (vel.y*dt + (0.5*accel.y*dt*dt))*dir.y;
					dt = dt*1.002;
			
		} 
		*/


	void missile::destroy() {
			visible = false;
		}

	};