#include <math.h>
#include "NavGraph.h"
#include "World.h"

NavGraph::NavGraph()
{
}


NavGraph::~NavGraph()
{
	for (Vertex* v : vertices_)
		delete v;
}

void NavGraph::generate(World* world)
{
	for (int i = 0; i < TERRAIN_WIDTH * 2; i++) {
		for (int j = 0; j < TERRAIN_HEIGHT * 2; j++) {
			if (world->walkable(sf::Vector2f(i*TILE_WIDTH / 2 + TILE_WIDTH / 4, j*TILE_HEIGHT / 2 + TILE_HEIGHT / 4)))
				vertices_.push_back(new Vertex(i*TILE_WIDTH / 2 + TILE_WIDTH / 4, j*TILE_HEIGHT / 2 + TILE_HEIGHT / 4));
		}
	}
	for (auto v : vertices_){
		std::vector<Vertex*> neighbors;
		for (auto u : vertices_) {
			if (v != u && sqrt(pow(v->pos_.x - u->pos_.x, 2) + pow(v->pos_.y - u->pos_.y, 2)) < 20) {
				neighbors.push_back(u);
			}
		}
		v->neighbors_ = neighbors;
	}
}

float NavGraph::heuristicEstimate(Vertex& start, Vertex& end) const
{
	float dx = abs(start.pos_.x - end.pos_.x);
	float dy = abs(start.pos_.y - end.pos_.y);
	if (dx > dy) return dx;
	return dy;
}

Vertex* findLowestFScore(std::vector<Vertex*>& vertices)
{
	Vertex* ret = nullptr;
	float lowestFScore = INF;
	for (auto v : vertices) {
		if (v->fScore_ < lowestFScore) {
			ret = v;
			lowestFScore = v->fScore_;
		}
	}
	return ret;
}

Vertex* NavGraph::findClosestVertex(sf::Vector2f& pos)
{
	Vertex* closest = nullptr;
	float dist = INF;
	for (Vertex* v : vertices_) {
		if (sqrt(pow(v->pos_.x - pos.x, 2) +
			pow(v->pos_.y - pos.y, 2)) < dist) {
			closest = v;
			dist = sqrt(pow(v->pos_.x - pos.x, 2) +
				pow(v->pos_.y - pos.y, 2));
		}
	}
	return closest;
}

std::vector<sf::Vector2f> NavGraph::getPath(sf::Vector2f& start, sf::Vector2f& end)
{
	std::vector<sf::Vector2f> path;
	for (Vertex* v : vertices_) {
		v->cameFrom_ = nullptr;
		v->fScore_ = INF;
		v->gScore_ = INF;
	}
	std::vector<Vertex*> closedSet;
	std::vector<Vertex*> openSet;
	Vertex* startVertex = findClosestVertex(start);
	Vertex* endVertex = findClosestVertex(end);

	startVertex->gScore_ = 0;
	startVertex->fScore_ = heuristicEstimate(*startVertex, *endVertex);
	openSet.push_back(startVertex);

	while (!openSet.empty()) {
		Vertex* current = findLowestFScore(openSet);
		if (current == endVertex) {
			Vertex* next = current->cameFrom_;
			while (next != nullptr)
			{
				path.push_back(current->pos_);
				current = next;
				next = next->cameFrom_;
			}
			return path;
		}
		openSet.erase(find(openSet.begin(),openSet.end(),current));
		closedSet.push_back(current);
		std::vector<Vertex*> neighbors = current->neighbors_;
		for (auto neighbor : neighbors) {
			if (find(closedSet.begin(), closedSet.end(), neighbor)
				!= closedSet.end()) continue;

			float tentativeGScore = current->gScore_ + 
				sqrt(pow(current->pos_.x - neighbor->pos_.x, 2) + 
				pow(current->pos_.y - neighbor->pos_.y, 2));
			if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end() ||
				tentativeGScore < neighbor->gScore_) {
				neighbor->cameFrom_ = current;
				neighbor->gScore_ = tentativeGScore;
				neighbor->fScore_ = neighbor->gScore_ + heuristicEstimate(*neighbor, *endVertex);
				if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
					openSet.push_back(neighbor);
				}
			}
		}
	}
	return path; //ei reittiä
}

void NavGraph::render(sf::RenderWindow& wnd)
{
	//for (auto v : vertices_) {
	//	for (auto u : v->neighbors_) {
	//		sf::Vertex line[] =
	//		{
	//			u->pos_,
	//			v->pos_
	//		};

	//		wnd.draw(line, 2, sf::Lines);
	//	}
	//}
}
