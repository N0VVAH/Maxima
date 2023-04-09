#include "tutorial.h"
#include "iostream"
#include "combat.h"
#include "Transitions.h"
#include <chrono>
#include "enemy.h"

Tutorial::Tutorial() { }

Tutorial::Tutorial(scene* preScene)
{
	prevScene = preScene;
	//Edge colliders for game scene
	House = Square(sf::Color::Blue, 1.10f, 1.0f);
	House.setPos(-400.0, -399.0f);
	House.setCollider({ 140.0f, 100.0f }, { 280.0f, 200.0f });
	render.push_back(&House);

	leftSide = Square(sf::Color::Blue, 1.0f, 1.0f);
	leftSide.setPos(-400.0, -399.0f);
	leftSide.setCollider({ 1.0f, 450.0f }, {4.0f, 700.0f });
	render.push_back(&leftSide);

	botSide = Square(sf::Color::Blue, 1.0f, 1.0f);
	botSide.setPos(-400.0, -399.0f);
	botSide.setCollider({ 800.0f, 775.0f }, { 1600.0f, 4.0f });
	render.push_back(&botSide);

	rightSide = Square(sf::Color::Blue, 1.0f, 1.0f);
	rightSide.setPos(-400.0, -399.0f);
	rightSide.setCollider({ 1605.0f, 400.0f }, { 4.0f, 800.0f });
	render.push_back(&rightSide);

	topRightSide = Square(sf::Color::Blue, 1.0f, 1.0f);
	topRightSide.setPos(-400.0, -399.0f);
	topRightSide.setCollider({ 1200.0f, 0.0f }, {  800.0f, 4.0f });
	render.push_back(&topRightSide);

	topLeftSide = Square(sf::Color::Blue, 1.0f, 1.0f);
	topLeftSide.setPos(-400.0, -399.0f);
	topLeftSide.setCollider({ 300.0f, 0.0f }, { 600.0f, 4.0f });
	render.push_back(&topLeftSide);



	for (int i = 0; i < 5; i++)
	{
		if (i == 2)
		{
			fence[2] = new Square("..\\assets\\images\\fencegate.png", 256, 256);
		}
		else
		{
			fence[i] = new Square("..\\assets\\images\\fenceleft.png", 256, 256);
			fence[i]->setCollider({ 735.0f, 128.0f + (256.0f * i) }, { 10.0f, 256.0f });
		}
		fence[i]->setPos(800, 128 + (256 * i));
		render.push_back(fence[i]);
	}

	background = new Square("..\\assets\\images\\backgrounds\\tutorial.png", 1600, 800);
	background->setPos(800, 400);


	c.CharSetup("..\\assets\\images\\chartest.png", 100, 100);
	c.setCollider({ 250.0f, 450.0f }, { 64.0f, 64.0f });
	textureAtlasProps a = textureAtlasProps();
	a.timeBetween = 0.3;
	a.texturesInAtlas = 3;
	c.setTextureAtlas(a);
	c.updateTexture();
	render.push_back(&c);
	c.setPos(200, 400);

	Teach.CharSetup("..\\assets\\images\\TeachTest.png", 100, 100);
	Teach.setTextureAtlas(a);
	Teach.updateTexture();
	Teach.setPos(600, 400);
	render.push_back(&Teach);
	

	teachCollision = Square(sf::Color::Black, 120, 120);
	teachCollision.setPos(600, 400);

	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	a.texturesInAtlas = 5;
	for (size_t i = 0; i < 10; i++)
	{
		enemies[i] = new Square("..\\assets\\images\\slimemonster.png", 60, 60);
		enemies[i]->setTextureAtlas(a);
		enemies[i]->updateTexture();
		enemies[i]->setPos((std::rand() % 700) + 850, (std::rand() % 600) + 50);
		enemies[i]->type = 'E';
		render.push_back(enemies[i]);
	}

	textProps p = textProps();
	p.string = "Ah! You are finally awake, Welcome to the realm of Maxima!\nI didn't catch your name before you passed out,\nbut that isn't important now.\nHave a quick walk around to wake yourself up,\njust like you would as normal.";
	p.col = sf::Color::Black;
	p.fontSize = 18.0f;

	tutorialText = new textAppear(p, 0.05f);
	tutorialText->setPos(600, 725);

	Global::ChatBox->setPos(575, 725);
	Global::ChatBox->setSize(500, 150);
	
}

void Tutorial::update(sf::RenderWindow* window, float dtime)
{
	//sprite updates
	c.update(dtime);
	Teach.update(dtime);
	

	for (int i = 0; i < 10; i++)
	{
		enemies[i]->update(dtime);
	}


	if (fightDone == new bool(true))
	{
		delete fightDone;
		delete combatScene;
	}



	if (TransitionController::playing != nullptr && TransitionController::playing->isDone() == false)
	{
		TransitionController::playing->update(dtime);
		return;
	}


	//Event handling
	sf::Event* events = new sf::Event;
	while (window->pollEvent(*events))
	{
		switch ((*events).type)
		{

		case sf::Event::KeyPressed:
			if ((*events).key.code == sf::Keyboard::Enter)
			{
				if (tutorialText->isDone() == true)
				{
					tutorialText->updateText("Good! Now to survive in this world you will need to fight.\nSo go rough up one of those slime monster behind me.\nThey are a push over, bred for food not fighting.");
				}

				tutorialText->changeSpeed(0.025f);
				
			}

			

			switch ((*events).key.code)
			{
			case sf::Keyboard::Escape:
				exitScene();
				break;

			default:
				break;
			}
			break;

			render[0] = &c;

		case sf::Event::KeyReleased:
			if ((*events).key.code == sf::Keyboard::Enter)
			{
				if (tutorialText->getSpeed() != 0.05f)
				{
					tutorialText->changeSpeed(0.05f);
				}
			}
			break;

		case sf::Event::Closed:
			(*window).close();
			break;

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouseDownPos = sf::Mouse::getPosition();
			}

			break;

		case sf::Event::MouseButtonReleased:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mouseDownPos != sf::Vector2i())
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mouseDownPos != sf::Vector2i())
				{

					mouseUpPos = { events->mouseButton.x, events->mouseButton.y };
					for (size_t i = 0; i < UI.size(); i++)
					{
						if (UI[i]->getGlobalBounds().contains(mouseDownPos.x, mouseDownPos.y) && UI[i]->getGlobalBounds().contains(mouseUpPos.x, mouseUpPos.y))
						{
							if (UI[i]->type == 'S')
							{
								loadScene(((scene * (*)())UI[i]->onClick())());
							}
							else
							{
								((void(*)())UI[i]->onClick())();
							}

						}
					}

					mouseDownPos = sf::Vector2i();
				}
			}

		default:
			break;
		}
	}


	sf::Vector2f movement = sf::Vector2f(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement += sf::Vector2f(0, -100 * dtime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement += sf::Vector2f(0, 100 * dtime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement += sf::Vector2f(-100 * dtime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement += sf::Vector2f(100 * dtime, 0);
	}

	c.movePos(movement.x, movement.y);

	//Collision Detection
	if (teachCollision.getGlobalBounds().intersects(c.getGlobalBounds()))
	{
		tutorialText->update(dtime);
		if (chatboxShowing == false)
		{
			chatboxShowing = true;
			render.push_back(Global::ChatBox);
			UI.push_back(tutorialText);
		}

	}
	else
	{
		if (chatboxShowing == true)
		{
			removeFromUI(tutorialText);
			removeFromRender(Global::ChatBox);
			chatboxShowing = false;

		}
	}

	for (size_t i = 0; i < sizeof(enemies) / sizeof(Square*); i++)
	{
		if (c.Collider.getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
		{
			Enemy e = Enemy();
			e.moves.push_back(new move());
			
			for (size_t k = 0; k < 20; k++)
			{
				e.loottable[k] = 1;
			}
			combatScene = new combat(this, fightDone, e);

			if (TransitionController::playing == nullptr)
			{
				TransitionController::playTransition(0);
				return;
			}

			TransitionController::playing->reset();
			TransitionController::playing = nullptr;
			removeFromRender(enemies[i]);
			enemies[i]->setPos(-400, -400);


			loadScene(combatScene);
			return;
		}
	}

	for (int i = 0; i < render.size(); i++)
	{
		if (render[i]->hasCollider == true)
		{
			if (render[i] == &c)
			{
				continue;
			}
			if (c.Collider.getGlobalBounds().intersects(render[i]->Collider.getGlobalBounds()))
			{
				c.movePos(-movement.x, -movement.y);
				break;
			}
		}
	}


}

void Tutorial::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	background->draw(target, states);

	for (size_t i = 0; i < render.size(); i++)
	{
		render[i]->draw(target, states);
	}

	for (size_t i = 0; i < UI.size(); i++)
	{
		UI[i]->draw(target, states);
	}

	if (TransitionController::playing != nullptr && TransitionController::playing->isDone() == false)
	{
		TransitionController::playing->draw(target, states);
		return;
	}
}

char Tutorial::inputHandler()
{
	return 'h';
}

void Tutorial::exitScene()
{
	Global::curScene = prevScene;
}

void Tutorial::closeScene()
{
	exitScene();
	delete this;
}

void Tutorial::loadScene(scene* load)
{
	Global::curScene = load;

}