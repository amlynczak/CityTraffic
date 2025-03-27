#include"Pedestrian.h"
#include<iostream>

Pedestrian::Pedestrian(int id, float x, float y, Direction dir) : Entity(id, x, y, dir) {}

void Pedestrian::update(float delta) {
	float speed = 2.0f;

	if (_dir == Direction::HOR){
		_x += speed * delta;
	} else {
		_y += speed * delta;
	}
}