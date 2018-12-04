#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"
#include "TextureManager.h"
#include "PlayState.h"

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
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
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

	if (!TheTextureManager::Instance()->load("assets/vayne play.png",
		"playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/vayne exit.png",
		"exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	
	GameObject* button1 = new MenuButton(
		new LoaderParams(190, 220, 250, 100, "playbutton"),
		s_menuToPlay);

	GameObject* button2 = new MenuButton(
		new LoaderParams(190, 330, 250, 100, "exitbutton"),
		s_exitFromMenu);

	GameObject* title = new MenuButton(
		new LoaderParams(190, 100, 260, 70, "title"),
		s_image);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(title);

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