#include "Animation.h"

Animation::Animation(int width, sf::Texture* texture, float frameRate) :
	frameWidth(width), spritesheet(texture), framesPerSecond(frameRate)
{
	frameCount = (spritesheet->getSize().x / frameWidth);
	totalTime = ((float)frameCount) / framesPerSecond;
}

void Animation::setSpeed(float speed) { totalTime = speed; }

float Animation::getLength() { return totalTime; }

float Animation::getDims() { return (float)frameWidth; }

sf::Sprite Animation::getSprite(float& time, Orientation orient)
{
	sf::Sprite sprite;
	sprite.setTexture(*spritesheet);
	if (time > totalTime) time = 0.0f;
	sprite.setTextureRect(sf::IntRect((int)((time / totalTime)*frameCount)*frameWidth, frameWidth*orient, frameWidth, frameWidth));
	return sprite;
}

Orientation getOrientation(sf::Vector2f dir)
{
	float angle = atan2(dir.y, dir.x);
	Orientation orient = (angle <= PI / 8.0f && angle >= -PI / 8.0f) ? SE
		: (angle <= 3 * PI / 8.0f && angle >= PI / 8.0f) ? S
		: (angle <= 5 * PI / 8.0f && angle >= 3 * PI / 8.0f) ? SW
		: (angle <= 7 * PI / 8.0f && angle >= 5 * PI / 8.0f) ? W
		: (angle <= -7 * PI / 8.0f || angle >= 7 * PI / 8.0f) ? NW
		: (angle <= -5 * PI / 8.0f && angle >= -7 * PI / 8.0f) ? N
		: (angle <= -3 * PI / 8.0f && angle >= -5 * PI / 8.0f) ? NE
		: E;
	return orient;
}