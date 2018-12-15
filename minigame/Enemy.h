#pragma once

#include "GameObject.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision(GameObject* object);

private:
	bool checkCollision = false;
	int hp = 3;
	void handleInput();
};