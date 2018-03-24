#pragma once
#include <vector>
#include "include\SDL.h"

struct Vector2
{
	Vector2() : x(0), y(0) {};
	Vector2(float _x, float _y) : x(_x), y(_y) {};

	float GetX() { return x; };

	bool IsZero() 
	{ 
		if (x == 0 && y == 0)
			return true;
		else
			return false;
	}

	float x, y;
};

class AEAsteroid
{
public:
	AEAsteroid();
	~AEAsteroid();

	void SetRenderer(SDL_Renderer* renderer);
	void SetRadius(float radius);
	void SetLocation(float x, float y);
	void SetVelocity(float x, float y);
	void SetVelocityRandomDirection(float x, float y);

	Vector2 GetLocation();

	void Rotate(float Angle);

	void GenerateAsteroid(int VertexCount, float xOffsetMargin, float yOffsetMargin);

	void Draw();
	void Update(float deltaTime);
	void ResetGenerateRandom();

public:
	Vector2 Location;

	float Radius;

	float Rotation;

	std::vector<Vector2> Vertices;

	Vector2 Velocity;

	SDL_Renderer* Renderer;
};