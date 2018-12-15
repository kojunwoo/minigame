#include "Enemy.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(1);
	m_velocity.setY(0.001);
}

void Enemy::draw()
{
	if (m_velocity.getX() < 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else {
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 7));
	if (m_position.getX() < 20) {
		m_velocity.setX(1);
	}
	else if (m_position.getX() > 640) {
		m_velocity.setX(-1);
	}
	if (checkCollision == true)
	{
		hp--;
		if (hp == 0)
		{
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
		checkCollision = false;
	}
	SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::collision(GameObject * object)
{
	if (((SDLGameObject*)object)->GetTextureID() == "arrow")
	{
		checkCollision = true;
	}
}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}

	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;
}
