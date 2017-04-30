#pragma once
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include < stdio.h>
#include <string>
#include <ctime>
#include "gameplay.h"
#define GAMING_WINDOW_HEIGHT 600
#define GAMING_WINDOW_WIDTH 1024
#include "reeko_physics_engine.h"

using namespace std;

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
				object.travel(-1,-1,1,1,1,1,abs(dir.x), abs(dir.y));
			if (dir.x < 0 && dir.y > 0)
				object.travel(-1, 1, 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			if (dir.x > 0 && dir.y < 0)
				object.travel(1, -1, 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			if (dir.x > 0 && dir.y > 0)
				object.travel(1, 1, 1, 1, 1, 1, abs(dir.x), abs(dir.y));

			/*
			if (dir.x < 0)
				object.accelerate('L',1,1,1,1,abs(dir.x), abs(dir.y));
			else {
				object.accelerate('R', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			}
			if (dir.y < 0)
				object.accelerate('D', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			else {
				object.accelerate('U', 1, 1, 1, 1, abs(dir.x), abs(dir.y));
			}
			*/
			
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
		void hit(physics::object objects[], short no_objects, T targets[], short no_targets) {
			for (int i = 0; i < no_objects; i++) {
				for (int j = 0; j < no_targets; j++) {
					if (collision::Collide(objects[i], targets[j].particle)) {
						if (targets[j].identity == "missile") {
							points=points+5;
						}
						else if (targets[j].identity == "enemy ship") {
							points++;
						}
						targets[j].destroy();
					}
				}
			}
		}

		
}