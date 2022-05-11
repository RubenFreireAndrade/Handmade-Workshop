#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
}

bool MainMenuState::OnEnter()
{
    Screen::Instance()->SetColor(30U, 30U, 30U);

    m_mainShader = std::make_unique<Shader>();
    m_sceneCamera = std::make_unique<FreeCamera>("mainCam");
    //m_textShader = std::make_unique<Shader>();

    if (!m_mainShader->Create("Shaders/Main.vert", "Shaders/Main.frag"))
    {
        return false;
    }
    m_mainShader->BindAttribute("vertexIn");
    m_mainShader->BindAttribute("colorIn");
    m_mainShader->BindAttribute("textureIn");

    m_mainShader->BindUniform("model");
    m_mainShader->BindUniform("view");
    m_mainShader->BindUniform("projection");
    m_mainShader->BindUniform("isTextured");

    m_sceneCamera->SetVelocity(0.0f);
    m_sceneCamera->SetSensitivity(0.0f);
    m_sceneCamera->GetTransform().SetPosition(0.0f, 0.0f, 50.0f);
    m_sceneCamera->SetBackgroundColor(207U, 207U, 207U);

    /*if (!m_textShader->Create("Shaders/Text.vert", "Shaders/Text.frag"))
    {
        return false;
    }
    m_textShader->BindAttribute("vertexIn");
    m_textShader->BindAttribute("colorIn");
    m_textShader->BindAttribute("textureIn");

    m_textShader->BindUniform("model");
    m_textShader->BindUniform("view");
    m_textShader->BindUniform("projection");
    m_textShader->BindUniform("textureImage");*/

    //===========================================================================

    //Material::Load("Defaults", "Defaults.mtl");

    //===========================================================================

    /*if (!(Text::Initialize()))
    {
        return false;
    }

    if (!(Audio::Initialize()))
    {
        return false;
    }*/
    return true;
}

State* MainMenuState::Update(int deltaTime)
{
    return this;
}

bool MainMenuState::Render()
{
    auto& mainShader = *m_mainShader.get();
   /* auto& textShader = *m_textShader.get();
    auto& lightShader = *m_lightShader.get();
    auto& testShader = *m_testShader.get();*/

    auto SetViewport = [](const glm::ivec4& viewport, const glm::uvec4& color)
    {
        Screen::Instance()->SetViewport(viewport.x, viewport.y, viewport.z, viewport.w);
        Screen::Instance()->SetColor(color);
        Screen::Instance()->Refresh();
    };

    mainShader.Use();

   /* for (const auto& object : m_objects)
    {
        object->Render(mainShader);
    }*/

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //Call features here.
    //RenderPlay();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return true;
}

void MainMenuState::OnExit()
{
}

void MainMenuState::RenderPlay()
{
    ImGui::Begin("Game Window", nullptr);
    ImGui::Text("TESTING STATE");
    ImGui::End();
}
