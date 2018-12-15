#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"
#include "TextureManager.h"
#include "PlayState.h"
#include "Background.h"

const std::string MenuState::s_menuID = "MENU";
MenuState* MenuState::s_pInstance = nullptr;
void MenuState::update()

{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
	std::cout << "Play button clicked\n";
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
	std::cout << "Exit button clicked\n";
}

void MenuState::s_image()
{
}

bool MenuState::onEnter()
{

	if (!TheTextureManager::Instance()->load("assets/vayne play2.png",
		"playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/vayne exit2.png",
		"exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/vayne3.png",
		"title", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/background.png",
		"deco", TheGame::Instance()->getRenderer()))
	{
		return false;
	}


	GameObject* button1 = new MenuButton(
		new LoaderParams(198, 250, 250, 100, "playbutton"),
		s_menuToPlay);

	GameObject* button2 = new MenuButton(
		new LoaderParams(198, 330, 250, 100, "exitbutton"),
		s_exitFromMenu);

	GameObject* button3 = new Background(
		new LoaderParams(60, 30, 520, 220, "title"));

	GameObject* button4 = new Background(
		new LoaderParams(0, 0, 640, 480, "deco"));


	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);
	m_gameObjects.push_back(button4);

	std::cout << "entering MenuState\n";
	return true;
}


bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("exitbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("title");
	std::cout << "exiting MenuState\n";
	return true;
}