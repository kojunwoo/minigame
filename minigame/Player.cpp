#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include "Ball.h"

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

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		TheInputHandler::Instance()->right = true;
		
		m_velocity.setX(1);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		TheInputHandler::Instance()->right = false;

		m_velocity.setX(-1);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}

	
	
		if (isflip == true)
		{
			if(TheInputHandler::Instance()->ispush(SDL_SCANCODE_SPACE))
			TheGame::Instance()->GetGameObjects()->push_back(new Ball(new LoaderParams(m_position.getX() + 54, m_position.getY() + 18, 12, 5, "animate4")));
		}
		else if (isflip == false)
		{
			if (TheInputHandler::Instance()->ispush(SDL_SCANCODE_SPACE))
			TheGame::Instance()->GetGameObjects()->push_back(new Ball(new LoaderParams(m_position.getX() - 14, m_position.getY() + 18, 12, 5, "animate4")));
		}
		
	

	//Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = *target - m_position;
	//m_velocity /= 50;
}