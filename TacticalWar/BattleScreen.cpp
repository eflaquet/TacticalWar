#include "BattleScreen.h"
#include "TestCharacterModel.h"

using namespace tw;

BattleScreen::BattleScreen()
{
	renderer = new IsometricRenderer(NULL);
	environment = new Environment(11, 5);
	environment->getMapData(2, 2)->setIsObstacle(true);
	environment->getMapData(1, 1)->setIsWalkable(false);

	characters.push_back(new TestCharacterModel(environment, 0, 0, 0));
	XDirection = true;
	YDirection = true;
	testDirection = false;
	setNextPosition();

	font.loadFromFile("../assets/font/arial.ttf");
	FPS.setFont(font);
}

void BattleScreen::handleEvents(sf::RenderWindow * window)
{
	/*
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
	*/
}

void BattleScreen::update(float deltatime)
{
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->update(deltatime);

		if (!characters[i]->hasTargetPosition())
		{
			setNextPosition();
		}
	}
	
	double fps = 1.0 / deltatime;
	FPS.setString(std::to_string((int)fps));
	FPS.setFillColor(sf::Color::Red);
	FPS.setPosition(10, 10);
}

void BattleScreen::render(sf::RenderWindow * window)
{
	renderer->modifyWindow(window);
	renderer->render(environment, characters);
	window->draw(FPS);
}