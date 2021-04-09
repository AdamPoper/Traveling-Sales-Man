#pragma once
#include <unordered_map>
#include <list>
#include <SFML/Graphics.hpp>

class Graph
{
public:
	Graph();

	~Graph();

	void addEdge(sf::CircleShape* src, sf::CircleShape* dest);
	void removeEdge(sf::CircleShape* src, sf::CircleShape* dest);

	void draw(sf::RenderWindow& window);
	void clear();

private:

	void addVertex(sf::CircleShape* v);
	void removeVertex(sf::CircleShape* v);

private:
	std::unordered_map<sf::CircleShape*, std::list<sf::CircleShape*>> m_map;
};