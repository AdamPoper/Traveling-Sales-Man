#pragma once
#include "Graph.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#define NODE_RADIUS 10.0f
#define WINDOW_WIDTH  800.0f
#define WINDOW_HEIGHT 800.0f

class Node
{
public:
	Node(float radius, uint32_t id, sf::Vector2f pos)
		: id(id)
	{
		circle = sf::CircleShape(radius);
		circle.setPosition(pos);
		circle.setFillColor(sf::Color::Blue);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}

	Node(const Node& n)
	{
		circle = n.circle;
		id = n.id;
	}

	Node operator=(const Node& n)
	{
		circle = n.circle;
		id = n.id;
		return *this;
	}

public:
	sf::CircleShape circle;
	uint32_t id;
};

class TravelingSalesMan
{
public:

	static void RunProgram();
	static void InitProgram();

public:

	static TravelingSalesMan s_travelingSalesManProgram;

private:

	TravelingSalesMan();
	~TravelingSalesMan();

	void init();
	void run();

	void genRandomNodes();
	void genRandomEdges();

	void genInOrderPath();
	void shuffleNodes();
	void createBestGraph();

	float calculateDistance();
	float pythagorus(float x, float y);

	void swap(uint32_t i, uint32_t j);
	void reverse(uint32_t index, uint32_t count);
	uint32_t factorial(uint32_t i);

	void onUpdateUI();
		
private:

	sf::RenderWindow m_window;
	std::vector<Node> m_nodes;
	std::vector<Node> m_bestOrder;
	float m_bestDistance = 0.0f;
	uint32_t m_currentIteration = 1;
	Graph m_graph;
	uint32_t m_nodeCount = 10;
	uint32_t m_numPermutations = 0;

	sf::Text m_progressText;
	sf::Text m_progressValueText;
	sf::Text m_permutationsText;
	sf::Text m_bestText;
	sf::Font m_font;
	bool m_done = false;
};
