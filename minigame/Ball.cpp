#include "Ball.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Game.h"

Ball::Ball(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(4);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-4);
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
	//벽과 충돌시
	if (((SDLGameObject*)pGameObject)->GetTextureID() == "Monster")
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