#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
}

bool MainMenuState::OnEnter()
{
    Screen::Instance()->SetColor(30U, 30U, 30U);
    return true;
}

State* MainMenuState::Update(int deltaTime)
{
    return nullptr;
}

bool MainMenuState::Render()
{
    ImGui::Text("TESTING STATE");
    return true;
}

void MainMenuState::OnExit()
{
}