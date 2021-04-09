#include "Graph.h"

Graph::Graph()
{
}
Graph::~Graph()
{
}

void Graph::addVertex(sf::CircleShape* v)
{
	m_map[v] = std::list<sf::CircleShape*>();
}

void Graph::addEdge(sf::CircleShape* src, sf::CircleShape* dest)
{
	if (m_map.find(src) == m_map.end())
		addVertex(src);
	if (m_map.find(dest) == m_map.end())
		addVertex(dest);
	m_map.at(src).push_back(dest);
}

void Graph::draw(sf::RenderWindow& window)
{
	for (const auto& [circle, list] : m_map)
	{
		for (auto& c : list)
		{
			sf::Vertex vertices[2];
			vertices[0].position = circle->getPosition();
			vertices[1].position = c->getPosition();
			window.draw(vertices, 2, sf::PrimitiveType::Lines);
		}
		window.draw(*circle);
	}
}

void Graph::clear()
{
	m_map.clear();
}

void Graph::removeVertex(sf::CircleShape* v)
{
	if (m_map.find(v) != m_map.end())
		m_map.erase(v);
}

void Graph::removeEdge(sf::CircleShape* src, sf::CircleShape* dest)
{
	if (m_map.find(src) != m_map.end())
		removeVertex(src);
	if (m_map.find(dest) != m_map.end())
		removeVertex(dest);
}