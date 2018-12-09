#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MenuState.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char*title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{


		m_pWindow = SDL_CreateWindow("minigame",

			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640, 480, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
	}
	else {
		m_bRunning = false;
		return false;
	}
	TheTextureManager::Instance()->load("assets/arrow.png", "animate4", m_pRenderer);

	//TheTextureManager::Instance()->load("assets/dog sprite.png", "animate2", m_pRenderer);
	//TheTextureManager::Instance()->load("assets/eyemonster.png", "animate3", m_pRenderer);

	SDL_SetRenderDrawColor(m_pRenderer, 40, 40, 50, 0);

	//m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 43, 110, "animate2")));
	//m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 71, 46, "animate3")));

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(MenuState::Instance());


	m_bRunning = true;
	return true;
}




void Game::render()
{
	
	SDL_RenderClear(m_pRenderer);
	
	m_pGameStateMachine->render();
	for (std::vector<GameObject*>::size_type i = 0;
		i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	SDL_RenderPresent(m_pRenderer);
}


void Game::update() {
	m_pGameStateMachine->update();
	for (std::vector<GameObject*>::size_type i = 0;
		i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(PlayState::Instance());
	}

}

void Game::quit() {
	m_bRunning = false;
}