#pragma once

#include "GameObject.h"
#include "SDLGameObject.h"

class Ball : public SDLGameObject
{
public:
	Ball(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void collision(GameObject* pGameObject);
	virtual void clean();

private:
	void handleInput();
};