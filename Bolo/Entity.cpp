#include "Entity.h"
#include "StandingState.h"


Entity::Entity() :
pos_(sf::Vector2f(50.0, 50.0)),
color_(sf::Color(0, 255, 0)),
state_(new StandingState()),
navGraph_(nullptr),
moveSpeed_(10.0f),
hp_(1000.0f),
maxhp_(1200.0f),
name_("")
{
}


Entity::~Entity()
{
}

void Entity::setNavGraph(NavGraph* navGraph)
{
	navGraph_ = navGraph;
}

void Entity::handleInput(sf::Event inputEvent)
{
	EntityState* state = state_->handleInput(*this, inputEvent);
	if (state != nullptr) {
		delete state_;
		state_ = state;
		state_->enter(*this, inputEvent);
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

void Entity::setName(std::string name)
{
	name_ = name;
}

void Entity::render(sf::RenderWindow& window)
{
	sf::CircleShape hero(2);
	hero.setFillColor(color_);
	hero.setPosition(pos_ - sf::Vector2f(2.f, 2.f));
	window.draw(hero);
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

float Entity::getPercentHP()
{
	return hp_ / maxhp_;
}