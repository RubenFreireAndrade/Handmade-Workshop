#pragma once
#include "State.h"
#include "Screen.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

class MainMenuState : public State
{
public:
	MainMenuState();
	virtual ~MainMenuState() {}

	// Inherited via State
	virtual bool OnEnter();
	virtual State* Update(int deltaTime) override;
	virtual bool Render() override;
	virtual void OnExit() override;

private:

};

