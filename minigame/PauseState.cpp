#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";
PauseState* PauseState::s_pInstance = nullptr;

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}


bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/restart2.png",
		"resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main menu2.png",
		"mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	GameObject* button1 = new MenuButton(new
		LoaderParams(200, 130, 200, 80, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new
		LoaderParams(200, 250, 200, 80, "resumebutton"), s_resumePlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");

	
	TheInputHandler::Instance()->reset();
	std::cout << "exiting PauseState\n";
	return true;
}