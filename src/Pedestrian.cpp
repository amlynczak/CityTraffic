#include"Pedestrian.h"
#include<iostream>

Pedestrian::Pedestrian(int id, float x, float y, Direction dir) : Entity(id, x, y, dir) {}

void Pedestrian::update(float delta, const Map& map) {
	float speed = 2.0f;

	switch (_dir)
	{
	case Direction::UP:
		break;
	case Direction::DOWN:
		break;
	case Direction::RIGHT:
		break;
	case Direction::LEFT:
		break;
	default:
		break;
	}
}