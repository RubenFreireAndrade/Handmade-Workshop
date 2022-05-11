#pragma once
#include <memory>
#include <vector>
#include "State.h"
#include "Text.h"
#include "Audio.h"
#include "Object.h"
#include "Shader.h"
#include "Screen.h"
#include "Material.h"
#include "FreeCamera.h"

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

	void RenderPlay();

private:
	std::unique_ptr<Shader> m_mainShader;
	std::unique_ptr<Shader> m_textShader;
	std::unique_ptr<Shader> m_lightShader;
	std::unique_ptr<Shader> m_testShader;
	std::unique_ptr<FreeCamera> m_sceneCamera;

	std::vector<std::unique_ptr<Object>> m_objects;
};

