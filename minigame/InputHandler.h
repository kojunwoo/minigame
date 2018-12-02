#pragma once

#include "SDL.h"
#include "vector"
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	void update();
	void clean();
	void reset();
	bool isKeyDown(SDL_Scancode key);
	bool getMouseButtonState(int buttonNumber);
	Vector2D* getMousePosition()
	{
		return m_mousePosition;
	}

private:
	InputHandler();
	~InputHandler() {}
	
	Vector2D* m_mousePosition;
	std::vector<bool> m_mouseButtonStates;
	static InputHandler* s_pInstance;
	const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;