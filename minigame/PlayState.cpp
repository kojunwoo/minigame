#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "Background.h"
#include "CollisionManager.h"
#include <SDL_mixer.h>

const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = 0;
Mix_Music* BackMusic;

void PlayState::update()
{
	Uint32 ticks = SDL_GetTicks();
	srand(ticks);
	if (ticks % 30 == 0)
	{
		if (rand() % 2 == 0)
		{
			m_gameObjects.push_back(new Enemy(new LoaderParams(640, 290, 71, 46, "monster")));
		}
		else
		{
			m_gameObjects.push_back(new Enemy(new LoaderParams(-71, 290, 71, 46, "monster")));
		}
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
 		m_gameObjects[i]->update();
	}

	for (int i = 0; i < m_gameObjects.size()-1; i++)
	{
		for (int j = i + 1; j < m_gameObjects.size(); j++)
		{
			if (TheCollisionManager::Instance()->Coll(m_gameObjects[i], m_gameObjects[j]))
			{
				m_gameObjects[i]->collision(m_gameObjects[j]);
				m_gameObjects[j]->collision(m_gameObjects[i]);
			}
		}
	}

	
	if (m_pPlayer->getIsDie() == true)
	{
		TheGame::Instance()->getStateMachine()->changeState(
			GameOverState::Instance());
		return;
	}
	
	if (TheInputHandler::Instance()->isKeyDown(
		SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(
			PauseState::Instance());
		return;
	}


}
void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
  		m_gameObjects[i]->draw();
	}

}
bool PlayState::onEnter()
{
	//if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
	//{
	//
	//	return 0;
	//}
	//
	//BackMusic = Mix_LoadMUS("die.mp3");
	//if (BackMusic == NULL)
	//{
	//	return 0;
	//}
	//
	//Mix_PlayMusic(BackMusic, 1);
	//Mix_VolumeMusic(128);

	if (!TheTextureManager::Instance()->load(
		"assets/idle vayne.png", "vayne",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/eyemonster.png","monster",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"assets/map.png", "ground",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"assets/arrow.png", "arrow",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}


	m_pPlayer = new Player(
		new LoaderParams(300, 290, 52, 63, "vayne"));

	GameObject* enemy = new Enemy(
		new LoaderParams(640, 290, 71, 46, "monster"));

	GameObject* enemy2 = new Enemy(
		new LoaderParams(-71, 290, 71, 46, "monster"));


	GameObject* ground = new Background(
		new LoaderParams(0, 0, 640, 480, "ground"));

	m_gameObjects.push_back(ground);
	m_gameObjects.push_back(m_pPlayer);
	m_gameObjects.push_back(enemy);
	m_gameObjects.push_back(enemy2);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
 	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("vayne");
	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }  
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}
