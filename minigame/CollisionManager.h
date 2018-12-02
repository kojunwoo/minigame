#pragma once
#include "GameObject.h"

class CollisionManager
{
private:

	static CollisionManager* s_pInstance;

public:
	CollisionManager();
	~CollisionManager();

	bool Coll(GameObject* object1, GameObject* object2);

	static CollisionManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CollisionManager();
			return s_pInstance;
		}
		return s_pInstance;
	}



};

typedef CollisionManager TheCollisionManager;