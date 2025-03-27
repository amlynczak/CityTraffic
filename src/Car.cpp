#include"Car.h"
#include<iostream>

Car::Car(int id, float x, float y, float speed, Direction dir) : Vehicle(id, x, y, dir, speed) {}

void Car::update(float delta) {
	if (_dir == Direction::HOR) {
		_x += _speed * delta;
	}
	else {
		_y += _speed * delta;
	}
}