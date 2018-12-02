#include "Ball.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Game.h"

Ball::Ball(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
	m_velocity.setX(-2);
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
	//벽과 충돌시
	if (((SDLGameObject*)pGameObject)->GetTextureID() == "animate5" || ((SDLGameObject*)pGameObject)->GetTextureID() == "animate6")
	{
		//ball을 없엔다
		std::vector<GameObject*>::iterator iter = TheGame::Instance()->GetGameObjects()->begin();
		std::vector<GameObject*>::iterator iterEnd = TheGame::Instance()->GetGameObjects()->end();
		for (; iter != iterEnd; iter++)
		{
			if (*iter == this)
			{
				TheGame::Instance()->GetGameObjects()->erase(iter);
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