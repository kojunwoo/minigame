#include "Background.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

Background::Background(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	
}

void Background::draw()
{
	TextureManager::Instance()->draw(m_textureID,
		(Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height,TheGame::Instance()->getRenderer());
}

void Background::update()
{
}

void Background::clean()
{
}

void Background::handleInput()
{
	
}