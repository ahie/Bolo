#include <math.h>
#include "NavGraph.h"
#include "Terrain.h"

NavGraph::NavGraph()
{
}


NavGraph::~NavGraph()
{
	for (Vertex* v : vertices_)
		delete v;
}

void NavGraph::generate(Terrain* from)
{
	for (int i = 0; i < from->width_ * 2; i++) {
		for (int j = 0; j < from->height_ * 2; j++) {
			if (from->walkable(sf::Vector2f(i*TILE_WIDTH / 2 + TILE_WIDTH / 4, j*TILE_HEIGHT / 2 + TILE_HEIGHT / 4)))
				vertices_.push_back(new Vertex(i*TILE_WIDTH / 2 + TILE_WIDTH / 4, j*TILE_HEIGHT / 2 + TILE_HEIGHT / 4));
		}
	}

	// slow..
	for (auto v : vertices_){
		std::vector<Vertex*> neighbors;
		for (auto u : vertices_) {
			if (v != u && sqrt(pow(v->pos_.x - u->pos_.x, 2) + pow(v->pos_.y - u->pos_.y, 2)) < TILE_WIDTH) {
				neighbors.push_back(u);
			}
		}
		v->neighbors_ = neighbors;
	}
}

float NavGraph::heuristicEstimate(Vertex start, Vertex end) const
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

// A* search
std::vector<sf::Vector2f> NavGraph::getPath(sf::Vector2f& start, sf::Vector2f& end)
{
	std::vector<sf::Vector2f> path;
	for (Vertex* v : vertices_) {
		v->cameFrom_ = nullptr;
		v->fScore_ = INF;
		v->gScore_ = INF;
	}
	// TODO: use priority queues
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
			// Reconstruct path and return
			Vertex* next = current->cameFrom_;
			while (next != nullptr)
			{
				path.push_back(current->pos_);
				current = next;
				next = next->cameFrom_;
			}
			//path.push_back(current->pos_); 
			//Don't walk to first vertex => Causes tunneling problems but makes moving less jerky
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
	return path; // No path found
}

// Visualize graph, for testing
void NavGraph::render(sf::RenderWindow& wnd)
{
	for (auto v : vertices_) {
		for (auto u : v->neighbors_) {
			sf::Vector2f i = u->pos_;
			i = sf::Vector2f(i.x - i.y, (i.x + i.y) / 2.0f);
			sf::Vector2f j = v->pos_;
			j = sf::Vector2f(j.x - j.y, (j.x + j.y) / 2.0f);
			sf::Vertex line[] =
			{
				i,
				j
			};

			wnd.draw(line, 2, sf::Lines);
		}
	}
}
