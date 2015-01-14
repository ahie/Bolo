#pragma once

#include <SFML/Graphics.hpp>

enum Orientation { S, SW, W, NW, N, NE, E, SE };

#define PI 3.14159265358979
Orientation getOrientation(sf::Vector2f dir);

struct Animation
{
	Animation(int width, sf::Texture* texture, float frameRate = 6.0f);

	int frameWidth;
	int frameCount;
	float framesPerSecond;
	float totalTime;

	sf::Texture* spritesheet;

	void setSpeed(float speed);
	float getLength();
	float getDims();
	sf::Sprite getSprite(float& time, Orientation orient);
};
