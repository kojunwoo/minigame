#pragma once

#include "GameObject.h"
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision(GameObject* object);

	bool getIsDie() { return isDie; }
private:
	void handleInput();

	bool isDie = false;
	Uint32 cbTimer(Uint32 interval);
};     