#pragma once
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include < stdio.h>
#include <string>
#include <ctime>
#include "gameplay.h"
#define GAMING_WINDOW_HEIGHT 768
#define GAMING_WINDOW_WIDTH 1366
#include "reeko_physics_engine.h"
#include "Sound_Engine_Katrina.h"
#include "enemies.h"

Sound_Engine_Katrina explosion; //not yet used
Sound_Engine_Katrina level_complete; //not yet used
Sound_Engine_Katrina game_over; //not yet used

namespace AI {
		Vector random_border_positition() {
			Vector place;
			int border;
			/*
			border = 1; Left side
			border = 2; Top
			border = 3; Right side
			border = 4; Bottom
			*/

			border = (rand()%4) + 1;
			switch (border) {
			case 1:
				place.x = 20;
				place.y = (rand() % GAMING_WINDOW_HEIGHT) + 20;
				break;
			case 2:
				place.x = (rand() % GAMING_WINDOW_WIDTH) + 20;
				place.y = 20;
				break;
			case 3:
				place.x = GAMING_WINDOW_WIDTH - 20;
				place.y = (rand() % GAMING_WINDOW_HEIGHT) + 20;
				break;
			case 4:
				place.x = (rand() % GAMING_WINDOW_WIDTH) + 20;
				place.y = GAMING_WINDOW_HEIGHT - 20;
				break;
			default:
				break;
			}
			return place;
		}

		void follow(physics::object &object, physics::object &target, double acceleration=1) {
			//Get angle between target and object
			object.setAngle(atan2(object.getVector('P').y - (target.getVector('P').y), (target.getVector('P').x)-object.getVector('P').x));	//Get angle from missile to mouse icon
			Vector dir;

			//Convert to unit vector
			dir.x = cos(object.getAngle());
			dir.y = sin(object.getAngle());
			if (dir.x < 0)
				object.accelerate('L');
			else {
				object.accelerate('R');
			}
			if (dir.y < 0)
				object.accelerate('D');
			else {
				object.accelerate('U');
			}
		}

		void follow(physics::object &object, Vector target, double acceleration = 1) {
			//Get angle between target and object
			object.setAngle(atan2(object.getVector('P').y - (target.y), (target.x) - object.getVector('P').x));	//Get angle from missile to mouse icon
			Vector dir;

			//Convert to unit vector
			dir.x = cos(object.getAngle());
			dir.y = sin(object.getAngle());
			if (dir.x < 0 && dir.y < 0)
				object.travel(1,1,abs(dir.x), abs(dir.y));
			if (dir.x < 0 && dir.y > 0)
				object.travel(1, 1, abs(dir.x), abs(dir.y));
			if (dir.x > 0 && dir.y < 0)
				object.travel(1, 1, abs(dir.x), abs(dir.y));
			if (dir.x > 0 && dir.y > 0)
				object.travel(1, 1, abs(dir.x), abs(dir.y));
		}

		enemies::missile launchMissile(short level) {
			enemies::missile enemy;
				switch (level) //Create object according to the level of the game
				{
					enemy.setVisible(true);
				case 1:
					enemy.create(AI::random_border_positition().x, AI::random_border_positition().y, 7, 7, 6);
					enemy.particle.setDirection(AI::random_border_positition());
					enemy.particle.initialise(enemy.particle.getVector('P').x, enemy.particle.getVector('P').y, level*3, level*3);
					return enemy;
					break;
				case 2:
					enemy.create(AI::random_border_positition().x, AI::random_border_positition().y, 7, 7, 6);
					enemy.particle.setDirection(AI::random_border_positition());
					enemy.particle.initialise(enemy.particle.getVector('P').x, enemy.particle.getVector('P').y, level , level);
					return enemy;
					break;
				case 3:
					enemy.create(AI::random_border_positition().x, AI::random_border_positition().y, 7, 7, 6);
					enemy.particle.setDirection(AI::random_border_positition());
					enemy.particle.initialise(enemy.particle.getVector('P').x, enemy.particle.getVector('P').y, level * 3, level * 3);
					return enemy;
					break;
				default:
					break;
				}
			}

		enemies::spaceship launchSpaceship(short level) {
			enemies::spaceship spaceship;
			ALLEGRO_BITMAP* spaceshipimage = al_load_bitmap("enemyship.png");

			switch (level) //Create object according to the level of the game
			{
				spaceship.setVisible(true);
			case 1:
				spaceship.create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25, spaceshipimage);
				spaceship.particle.setDirection(AI::random_border_positition());
				spaceship.particle.initialise(spaceship.particle.getVector('P').x, spaceship.particle.getVector('P').y, level * 3, level * 3);
				return spaceship;
				break;
			case 2:
				spaceship.create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25, spaceshipimage);
				spaceship.particle.setDirection(AI::random_border_positition());
				spaceship.particle.initialise(spaceship.particle.getVector('P').x, spaceship.particle.getVector('P').y, level , level);
				return spaceship;
				break;
			case 3:
				spaceship.create(AI::random_border_positition().x, AI::random_border_positition().y, 25, 25, spaceshipimage);
				spaceship.particle.setDirection(AI::random_border_positition());
				spaceship.particle.initialise(spaceship.particle.getVector('P').x, spaceship.particle.getVector('P').y, level * 2, level * 2);
				return spaceship;
				break;
			default:
				break;
			}
		}


		void rotate(physics::object &object, Vector target, double acceleration = 1) {
			//Get angle between target and object
			object.setAngle(atan2(object.getVector('P').y - (target.y), (target.x) - object.getVector('P').x));	//Get angle from missile to mouse icon
			Vector dir;

			//Convert to unit vector
			dir.x = cos(object.getAngle());
			dir.y = sin(object.getAngle());
		}


		
		template <class T>
		//Function checks if one target has been by other objects - Used to see if player has been hit by enemy bullet
		void playerhit(physics::object object[], short no_objects, T &target) {
			for (int i = 0; i < no_objects; i++) {
				if (collision::Collide(object[i], target.particle)) {
					lives--;
					object[i].initialise(-6, -6, 0, 0, 0, 0, 0, 0);
					break;
				}
			}
		}

		template <class T>
		//Function checks if one target has been by other objects - Used to see if player has been hit by enemy bullet
		bool a(physics::object object[], short no_objects, T &target) {
			for (int i = 0; i < no_objects; i++) {
				if (collision::Collide(object[i], target.particle)) {
					lives--;
					object[i].initialise(-6, -6, 0, 0, 0, 0, 0, 0);
					break;
					return true;
				}
			}
		}

		template <class T>
		//Function checks if several targets has been by other objects - Used to see if enemies has been hit by player bullet
		void hit(physics::object objects[], short no_objects, T targets[], short no_targets) {
			for (int i = 0; i < no_objects; i++) {
				for (int j = 0; j < no_targets; j++) {
					if (collision::Collide(objects[i], targets[j].particle) && targets[j].isVisible()) {
						if (targets[j].identity == "missile") {
							explosion.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "Explosion.wav");
							points = points + 5;

						}
						else if (targets[j].identity == "enemy ship") {
							explosion.playSound(ALLEGRO_PLAYMODE_ONCE, 1, 0, 1, "Explosion.wav");
							points++;

						}
						targets[j].destroy();
					}
				}
			}
		}
}