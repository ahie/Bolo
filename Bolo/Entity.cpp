#include "Entity.h"
#include "StandingState.h"
#include "DeathState.h"
#include "Level.h"
#include "NavGraph.h"
#include "Attack.h"
#include "Missile.h"

#include <iostream>


Entity::Entity(std::string name, Faction faction, AttackDescriptor attack) :
	pos_(sf::Vector2f(50.0, 50.0)),
	color_(sf::Color(0, 255, 0)),
	state_(new StandingState()),
	moveSpeed_(25.0f),
	hp_(100.0f),
	maxhp_(200.0f),
	hpRegen_(0.f),
	armor_(0.f),
	name_(name),
	faction_(faction),
	collisionRadius_(20.0f),
	navGraph_(nullptr),
	level_(nullptr),
	alive_(true),
	aDescription_(attack),
	animTime_(0.0f),
	attackSpeed_(0.6f),
	orient_(S)
{
}


Entity::~Entity()
{
	delete state_;
	for (auto anim : animations_)
		delete anim.second;
}

void Entity::setHP(float hp)
{
	hp_ = hp;
}

void Entity::setLevel(Level* level)
{
	level_ = level;
	navGraph_ = level_->getNavGraph();
}

float Entity::getDamage() const
{
	return aDescription_.damage;
}

float Entity::getHP() const
{
	return hp_;
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
	sf::Vector2f pos = pos_ + direction*(collisionRadius_ + aDescription_.hitRadius);
	level_->addAttack(aDescription_, *this, pos, direction);
	updateOrientation(direction);
}

void Entity::castSpell(sf::Vector2f direction)
{
	
}

void Entity::setMaxHP(float maxhp)
{
	maxhp_ = maxhp;
}

void Entity::update(float dt)
{
	animTime_ += dt;
	if (hp_ >= 0.0f && hp_ < maxhp_) {
		hp_ += hpRegen_;
		if (hp_ > maxhp_) hp_ = maxhp_;
		notify(HEALTH_CHANGED);
	}
	EntityState* state = state_->update(*this, dt);
	if (state != nullptr) {
		delete state_;
		state_ = state;
		state_->enter(*this);
	}
}

float Entity::getArmor() { return armor_; }

float Entity::getHPRegen() { return hpRegen_; }

void Entity::applyModifier(const std::pair<ModType, float>& mod)
{
	switch (mod.first) {
	case ARMOR:
		armor_ += mod.second;
		break;
	case HPREGEN:
		hpRegen_ += mod.second;
		break;
	case DAMAGE:
		addDamage(mod.second);
		break;
	default:
		break;
	}
}

void Entity::damage(Attack* attack)
{
	float damage = attack->getDamage() - armor_;
	if (damage < 0.f) damage = 0.f;
	// TODO: other mod calculation (e.g. resists)

	hp_ -= damage;
	notify(HEALTH_CHANGED);
	if (hp_ <= 0.0f && dynamic_cast<DeathState*>(state_) == nullptr) {
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

Faction Entity::getFaction() const
{
	return faction_;
}

bool Entity::isAlive() const
{ 
	return alive_; 
}

Level* Entity::getLevel() const
{
	return level_;
}

EntityState* Entity::getState() const
{
	return state_;
}

void Entity::setState(EntityState* state)
{
	state_ = state;
}

void Entity::addHP(float hp)
{
	hp_ += hp;
}

void Entity::addDamage(float damage)
{
	aDescription_.damage += damage;
}

float Entity::getAttackSpeed() const 
{ 
	return attackSpeed_; 
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
	sf::Vector2f to(x, y);
	return navGraph_->getPath(pos_, to);
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
	return ((pos_.x - at.x)*(pos_.x - at.x) +
		(pos_.y - at.y)*(pos_.y - at.y)) <= (collisionRadius_ + radius)*(collisionRadius_ + radius);
}

void Entity::addAnimation(Anim type, Animation* pointerToAnim)
{
	animations_.insert(std::make_pair(type, pointerToAnim));
}

float Entity::getPercentHP() const
{
	return hp_ / maxhp_;
}

RenderableSprite Entity::requestSprite()
{
	if (activeAnimation_ != nullptr){
		sf::Sprite sprite = activeAnimation_->getSprite(animTime_, orient_);
		sf::Vector2f pos = getIsometricPos();
		sprite.setPosition(pos.x - activeAnimation_->getDims() / 2.0f,
			pos.y - activeAnimation_->getDims() + 10.0f);
		return RenderableSprite(sprite, pos_);
	}
	return RenderableSprite();
}

float Entity::getAnimLength()
{
	if (activeAnimation_ == nullptr) return 0.0f;
	return activeAnimation_->getLength();
}

void Entity::setAnimation(Anim animation)
{
	animTime_ = 0.0f;
	activeAnimation_ = (animations_.find(animation))->second;
}

void Entity::updateOrientation(sf::Vector2f dir)
{
	orient_ = getOrientation(dir);
}
