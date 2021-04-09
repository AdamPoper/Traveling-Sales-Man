#include "TravelingSalesMan.h"

TravelingSalesMan TravelingSalesMan::s_travelingSalesManProgram;

void TravelingSalesMan::InitProgram()
{
    s_travelingSalesManProgram.init();
}

void TravelingSalesMan::RunProgram()
{
    s_travelingSalesManProgram.run();
}

void TravelingSalesMan::init()
{
    int fontSize = 14;
    genRandomNodes();
    genInOrderPath();
    m_bestDistance = calculateDistance();
    m_numPermutations = factorial(m_nodeCount);
    m_font.loadFromFile("assets/fonts/Arial.ttf");
    m_progressText.setCharacterSize(fontSize);
    m_progressText.setFont(m_font);
    m_progressText.setString("Progress: ");
    m_progressText.setPosition(sf::Vector2f(10.0f, 5.0f));
    m_progressValueText.setCharacterSize(fontSize);
    m_progressValueText.setFont(m_font);
    m_progressValueText.setString("0%");
    m_progressValueText.setPosition(sf::Vector2f(80.0f, 5.0f));
    m_permutationsText.setCharacterSize(fontSize);
    m_permutationsText.setFont(m_font);
    m_permutationsText.setString(std::string("Permutations: ") + std::to_string(m_numPermutations));
    m_permutationsText.setPosition(sf::Vector2f(10.0f, 20.0f));
    m_bestText.setCharacterSize(fontSize);
    m_bestText.setFont(m_font);
    m_bestText.setString(std::string("Best: ") + "0");
    m_bestText.setPosition(sf::Vector2f(10.0f, 35.0f));
}

void TravelingSalesMan::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }   

        uint32_t largestI = -1;
        for (int i = 0; i < m_nodeCount - 1; i++)
            if (m_nodes[i].id < m_nodes[i + 1].id)
                largestI = i;
        if (largestI == -1)
            m_done = true;
        else 
        {
            m_currentIteration++;
            float distance = calculateDistance();
            if (distance < m_bestDistance)
            {
                m_bestDistance = distance;
                m_bestOrder = m_nodes;
            }
            m_graph.clear();
            onUpdateUI();
            genInOrderPath();
            uint32_t largestJ = -1;
            for (int j = 0; j < m_nodeCount; j++)
                if (m_nodes[j].id > m_nodes[largestI].id)
                    largestJ = j;
            swap(largestI, largestJ);
            reverse(largestI + 1, m_nodeCount);
        }                       
        if (m_done)
            createBestGraph();
      
        m_window.clear();
        m_graph.draw(m_window);
        m_window.draw(m_progressText);
        m_window.draw(m_progressValueText);
        m_window.draw(m_permutationsText);
        m_window.draw(m_bestText);
        m_window.display();
    }
}

TravelingSalesMan::TravelingSalesMan()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Traveling Sales Man!") {}

TravelingSalesMan::~TravelingSalesMan()
{
}

void TravelingSalesMan::genRandomNodes()
{
    m_nodes.reserve(m_nodeCount);
    std::srand(std::time(nullptr));
    uint32_t id = 0;
    for (int i = 0; i < m_nodeCount; i++)
    {
        float x = std::rand() % (uint32_t)WINDOW_WIDTH;
        float y = std::rand() % (uint32_t)WINDOW_HEIGHT;
        m_nodes.emplace_back(NODE_RADIUS, id++, sf::Vector2f(x, y));
    }
}

void TravelingSalesMan::genRandomEdges()
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < m_nodes.size(); i++)
    {
        int randomIndex = 0;
        do {
            randomIndex = std::rand() % m_nodes.size();
        } while (randomIndex == i);
        // i know i'm giving pointers to objects in a vector but the vector never changes size so it should be ok
        m_graph.addEdge(&m_nodes[i].circle, &m_nodes[randomIndex].circle);
    }
}

void TravelingSalesMan::genInOrderPath()
{
    for (int i = 0; i < m_nodes.size() - 1; i++)
        m_graph.addEdge(&m_nodes[i].circle, &m_nodes[i + 1].circle);
}
void TravelingSalesMan::shuffleNodes()
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < m_nodeCount; i++)
    {
        uint32_t randomIndex = std::rand() % m_nodeCount;
        swap(i, randomIndex);
    }
}

float TravelingSalesMan::calculateDistance()
{
    float distance = 0.0f;
    for (int i = 0; i < m_nodeCount-1; i++)
    {
        float x = std::abs(m_nodes[i].circle.getPosition().x - m_nodes[i + 1].circle.getPosition().x);
        float y = std::abs(m_nodes[i].circle.getPosition().y - m_nodes[i + 1].circle.getPosition().y);
        distance += pythagorus(x, y);
    }
    return distance;
}

float TravelingSalesMan::pythagorus(float x, float y)
{
    return std::sqrtf((x * x) + (y * y));
}

void TravelingSalesMan::swap(uint32_t i, uint32_t j)
{
    Node temp = m_nodes[i];
    m_nodes[i] = m_nodes[j];
    m_nodes[j] = temp;
}

void TravelingSalesMan::reverse(uint32_t index, uint32_t count)
{
    uint32_t j = count - 1;
    for (int i = index; i < j; i++)
    {
        swap(i, j);
        j--;
    }
}

uint64_t TravelingSalesMan::factorial(uint64_t i)
{
    if (i == 1)
        return 1;
    return i * factorial(i-1);
}

void TravelingSalesMan::onUpdateUI()
{
    float progressValue = ((float)m_currentIteration / (float)m_numPermutations) * 100.0f;
    m_bestText.setString(std::string("Best: ") + std::to_string(m_bestDistance));
    m_progressValueText.setString(std::to_string(progressValue) + "%");
}

void TravelingSalesMan::createBestGraph()
{
    m_graph.clear();
    for (int i = 0; i < m_nodeCount-1; i++)
        m_graph.addEdge(&m_bestOrder[i].circle, &m_bestOrder[i + 1].circle);
}