#pragma once

class Vector2 {
public:
	Vector2() { xCoordinate = 0.0f; yCoordinate = 0.0f; };
	Vector2(float x, float y) { xCoordinate = x; yCoordinate = y; };
	~Vector2() {};
	float xCoordinate;
	float yCoordinate;
private:

};