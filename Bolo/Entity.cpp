#include "Entity.h"
#include "StandingState.h"
#include "DeathState.h"
#include "Level.h"

#include <iostream>


Entity::Entity() :
	pos_(sf::Vector2f(50.0, 50.0)),
	color_(sf::Color(0, 255, 0)),
	state_(new StandingState()),
	moveSpeed_(25.0f),
	hp_(100.0f),
	maxhp_(1200.0f),
	name_("Default name"),
	collisionRadius_(10.0f),
	navGraph_(nullptr),
	level_(nullptr),
	alive_(true),
	faction_(NEUTRAL),
	aDescription_(AttackDescriptor(50.0f, 5.0f, 0.2f, MISSILE, SINGLE_TARGET, PURE)),
	animTime_(0.0f),
	attackSpeed_(0.3f)
{
}


Entity::~Entity()
{
	delete state_;
}

void Entity::setLevel(Level* level)
{
	level_ = level;
	navGraph_ = level_->getNavGraph();
}

void Entity::handleInput(EntityEvent event)
{
	EntityState* state = state_->handleInput(*this, event);
	if (state != nullptr) {
		delete state_;
		state_ = state;
		state_->enter(*this);
	}
}

void Entity::attack(sf::Vector2f direction)
{
	updateOrientation(direction);

	// TODO: Construct missile with Attack?
	switch (aDescription_.atckClass) {
	case MELEE:
		level_->addAttack(
			new Attack(aDescription_.atckType, 
			aDescription_.dmgType, 
			aDescription_.damage,
			aDescription_.hitRadius,
			pos_ + direction*collisionRadius_, faction_));
		break;
	case MISSILE:
		level_->addAttack(
			new Missile(aDescription_.atckType,
			aDescription_.dmgType,
			aDescription_.damage,
			aDescription_.hitRadius,
			pos_ + direction*collisionRadius_, faction_,
			aDescription_.missileSpeed,
			direction));
		break;
	default:
		break;
	}
}

void Entity::update(float dt)
{
	animTime_ += dt;
	EntityState* state = state_->update(*this, dt);
	if (state != nullptr) {
		delete state_;
		state_ = state;
		state_->enter(*this);
	}
}

void Entity::damage(Attack* attack)
{
	hp_ -= attack->getDamage();
	notify(HEALTH_CHANGED);
	if (hp_ <= 0.0f && 
		dynamic_cast<DeathState*>(state_) == nullptr) {
		delete state_;
		state_ = new DeathState();
		state_->enter(*this);
	}
}

void Entity::kill()
{
	alive_ = false;
}

void Entity::setPosition(sf::Vector2f pos)
{
	pos_ = pos;
}

void Entity::setName(std::string name)
{
	name_ = name;
}

Faction Entity::faction() const
{
	return faction_;
}

void Entity::render(sf::RenderWindow& window)
{
	if (activeAnimation_ != nullptr){
		sf::Sprite sprite = activeAnimation_->getSprite(animTime_, orient_);
		sf::Vector2f pos = getIsometricPos();
		sprite.setPosition(pos.x - activeAnimation_->getDims() / 2.0f, 
			pos.y - activeAnimation_->getDims() + 10.0f);
		window.draw(sprite);
	}

	sf::CircleShape entity(collisionRadius_);
	entity.setFillColor(color_);
	entity.setOrigin(collisionRadius_, collisionRadius_);
	entity.setPosition(getIsometricPos());
	window.draw(entity);
}

sf::Vector2f Entity::getIsometricPos() const
{
	return sf::Vector2f(pos_.x - pos_.y, (pos_.x + pos_.y) / 2.0f);
}

void Entity::setColor(sf::Color color)
{
	color_ = color;
}

sf::Vector2f Entity::getPos() const
{
	return pos_;
}

std::vector<sf::Vector2f> Entity::getPath(float x, float y)
{
	return navGraph_->getPath(pos_, sf::Vector2f(x, y));
}


static sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

void Entity::move(sf::Vector2f to, float& dt)
{
	sf::Vector2f dirVec = to - pos_;
	dirVec = normalize(dirVec);

	float dt2 = sqrt((to - pos_).x * (to - pos_).x + (to - pos_).y * (to - pos_).y) / (moveSpeed_);
	if (dt2 < dt) {
		dt -= dt2;
		pos_ = to;
	}
	else {
		pos_ += moveSpeed_ * dirVec * dt;
		dt = -0.1f;
	}
	updateOrientation(dirVec);
}

bool Entity::checkCollision(sf::Vector2f at, float radius) const
{
	return (pos_.x - at.x)*(pos_.x - at.x) +
		(pos_.y - at.y)*(pos_.y - at.y) <= (collisionRadius_ + radius)*(collisionRadius_ + radius);
}

float Entity::getPercentHP()
{
	return hp_ / maxhp_;
}

#define PI 3.14159265358979
void Entity::updateOrientation(sf::Vector2f dir)
{
	float angle = atan2(dir.y, dir.x);
	orient_ = (angle <= PI / 8.0f && angle >= -PI / 8.0f) ? SE
			: (angle <= 3 * PI / 8.0f && angle >= PI / 8.0f) ? S
			: (angle <= 5 * PI / 8.0f && angle >= 3 * PI / 8.0f) ? SW
			: (angle <= 7 * PI / 8.0f && angle >= 5 * PI / 8.0f) ? W
			: (angle <= -7 * PI / 8.0f || angle >= 7 * PI / 8.0f) ? NW
			: (angle <= -5 * PI / 8.0f && angle >= -7 * PI / 8.0f) ? N
			: (angle <= -3 * PI / 8.0f && angle >= -5 * PI / 8.0f) ? NE
			: E;
}