#pragma once

#include "GameObject.h"
#include "SDLGameObject.h"

class Background : public SDLGameObject
{
public:
	Background(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision(GameObject* object) {};
private:
	void handleInput();
};