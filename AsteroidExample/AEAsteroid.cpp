#include "AEAsteroid.h"
//#include <SDL.h>

AEAsteroid::AEAsteroid()
{
	Location.x = 0;
	Location.y = 0;

	Velocity.x = 0;
	Velocity.y = 0;

	Rotation = 0;
}

AEAsteroid::~AEAsteroid()
{

}

void AEAsteroid::SetRenderer(SDL_Renderer * renderer)
{
	this->Renderer = renderer;
}

void AEAsteroid::SetRadius(float radius)
{
	Radius = radius;
}

void AEAsteroid::SetLocation(float x, float y)
{
	Location.x = x;
	Location.y = y;
}

void AEAsteroid::SetVelocity(float x, float y)
{
	Velocity.x = x;
	Velocity.y = y;
}

void AEAsteroid::SetVelocityRandomDirection(float x, float y)
{
	Velocity.x = ((rand() % 3) - 1) * x;
	Velocity.y = ((rand() % 3) - 1) * y;
}

Vector2 AEAsteroid::GetLocation()
{
	return Location;
}

void AEAsteroid::Rotate(float Angle)
{
	float newx, newy;

	for (size_t i = 0; i < Vertices.size(); i++)
	{
		newx = ((Vertices[i].x) * cos(Angle * 3.1416 / 180)) - ((Vertices[i].y) * sin(Angle * 3.1416 / 180));
		newy = ((Vertices[i].y) * cos(Angle * 3.1416 / 180)) + ((Vertices[i].x) * sin(Angle * 3.1416 / 180));

		Vertices[i].x = newx;
		Vertices[i].y = newy;
	}
}

void AEAsteroid::GenerateAsteroid(int VertexCount, float xOffsetMargin, float yOffsetMargin)
{
	//return if it can't generate a valid geometry.
	if (VertexCount < 3)
		return;
	
	float AngleBetweenVerts = 360 / VertexCount;
	float CurrentAngle = AngleBetweenVerts;

	Vertices.push_back(Vector2(Location.x + Radius, Location.y));

	for (size_t i = 1; i < VertexCount; i++)
	{
		float x, y;

		x = (Vertices[0].x * cos(CurrentAngle * 3.1416 / 180)) - (Vertices[0].y * sin(CurrentAngle * 3.1416 / 180));
		y = (Vertices[0].y * cos(CurrentAngle * 3.1416 / 180)) + (Vertices[0].x * sin(CurrentAngle * 3.1416 / 180));

		CurrentAngle += AngleBetweenVerts;

		x += ((rand() % 3) - 1) * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / xOffsetMargin));
		y += ((rand() % 3) - 1) * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / yOffsetMargin));

		Vertices.push_back(Vector2(x, y));
	}
}

void AEAsteroid::Draw()
{
	for (size_t i = 0; i < Vertices.size(); i++)
	{
		SDL_RenderDrawLine(Renderer, Location.x + Vertices[i].x, Location.y + Vertices[i].y, Location.x + Vertices[(i + 1) % Vertices.size()].x, Location.y + Vertices[(i + 1) % Vertices.size()].y);
	}

	SDL_RenderDrawPoint(Renderer, Location.x, Location.y);
}

void AEAsteroid::Update(float deltaTime)
{
	if (!Velocity.IsZero())
	{
		SetLocation(Location.x + Velocity.x * deltaTime, Location.y + Velocity.y * deltaTime);
	}

	if (Rotation != 0)
	{
		Rotate(Rotation * deltaTime);
	}

	if (Location.x < -10 || Location.x > 800)
	{
		ResetGenerateRandom();
	}
	if (Location.y < -10 || Location.y > 600)
	{
		ResetGenerateRandom();
	}
}

void AEAsteroid::ResetGenerateRandom()
{
	Vertices.clear();
	SetLocation(0, 0);
	SetRadius(rand() % 50 + 15);
	GenerateAsteroid(rand() % 5 + 5, rand() % 15 + 5, rand() % 15 + 10);
	SetLocation(rand() % 800, rand() % 600);
	SetVelocityRandomDirection(0.05, 0.05);
}
