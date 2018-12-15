#include "Ball.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Game.h"

Ball::Ball(const LoaderParams* pParams,bool right) :
	SDLGameObject(pParams)
{
	if (right)
	{
		m_velocity.setX(4);
	}
	else
	{
		m_velocity.setX(-4);
	}
}

void Ball::draw()
{
	SDLGameObject::draw();
}

void Ball::update()
{
	handleInput();

	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	SDLGameObject::update();


}

void Ball::collision(GameObject * pGameObject)
{
	if (((SDLGameObject*)pGameObject)->GetTextureID() == "monster")
	{
		

		//ball을 없엔다
		std::vector<GameObject*>::iterator iter = PlayState::Instance()->getGameObjects()->begin();
		std::vector<GameObject*>::iterator iterEnd = PlayState::Instance()->getGameObjects()->end();
		for (; iter != iterEnd; iter++)
		{
			if (*iter == this)
			{
				PlayState::Instance()->getGameObjects()->erase(iter);
				break;
			}
		}
	}
}

void Ball::clean()
{

}

void Ball::handleInput()
{
}