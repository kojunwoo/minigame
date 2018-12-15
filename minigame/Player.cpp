#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include "Ball.h"
#include"PlayState.h"
#include"GameObject.h"


Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

 	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::collision(GameObject * object)
{
	if (((SDLGameObject*)object)->GetTextureID() == "monster")
	{
		isDie = true;
	}
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{	
		m_velocity.setX(0.001);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-0.001);
	}

	if (isflip == true)
	{
		if (TheInputHandler::Instance()->ispush(SDL_SCANCODE_SPACE))
		{
			PlayState::Instance()->getGameObjects()->push_back(new Ball(new LoaderParams(m_position.getX() + 54, m_position.getY() + 18, 12, 5, "arrow"), true));
		}
	}
	else if (isflip == false)
	{
		if (TheInputHandler::Instance()->ispush(SDL_SCANCODE_SPACE))
		{
 			GameObject* ball = new Ball(new LoaderParams(m_position.getX() - 14, m_position.getY() + 18, 12, 5, "arrow"), false);
     		PlayState::Instance()->getGameObjects()->push_back(ball);
		}
	}
}