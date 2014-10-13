#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <vector>

const float INF = 100000000000.0f;

class Terrain;

struct Vertex {
	Vertex(float x, float y) : pos_(sf::Vector2f(x,y)) {}
	sf::Vector2f pos_;
	float fScore_;
	float gScore_;
	Vertex* cameFrom_;
	std::vector<Vertex*> neighbors_;
};

class NavGraph
{
public:
	NavGraph();
	~NavGraph();
	void generate(Terrain* from);
	std::vector<sf::Vector2f> getPath(sf::Vector2f& start, sf::Vector2f& end);
	void render(sf::RenderWindow& wnd);
private:
	float heuristicEstimate(Vertex start, Vertex end) const;
	std::vector<Vertex*> findNeighbors(Vertex* v);
	Vertex* findClosestVertex(sf::Vector2f& pos);
	std::vector<Vertex*> vertices_;
};
