#include "Entity.h"
#include "StandingState.h"
#include "DeathState.h"
#include "Level.h"


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
	aDescription_(AttackDescriptor(10.0f,5.0f,0.2f,MISSILE,SINGLE_TARGET,PURE))
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

void Entity::handleInput(sf::Event inputEvent)
{
	EntityState* state = state_->handleInput(*this, inputEvent);
	if (state != nullptr) {
		delete state_;
		state_ = state;
		state_->enter(*this);
	}
}

void Entity::attack(sf::Vector2f direction)
{
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
	if (hp_ < 0.0f) {
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
	sf::CircleShape entity(collisionRadius_);
	entity.setFillColor(color_);
	entity.setOrigin(collisionRadius_, collisionRadius_);
	entity.setPosition(pos_);
	window.draw(entity);
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