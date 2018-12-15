#pragma once

#include "GameObject.h"
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision(GameObject* object) {};
	int m_animSpeed;
	int m_numFrames;
private:
	void handleInput();
};