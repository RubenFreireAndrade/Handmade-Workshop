#include "BufferManager.h"
#include "Camera.h"
#include "DebugManager.h"
#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "ShaderManager.h"
#include "SplashScreen.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that creates VBO objects, loads sprite image and assigns all defaults 
//------------------------------------------------------------------------------------------------------
SplashScreen::SplashScreen(std::string filename)
{

	//create a vertex, color and texture VBO for the splash screen
	TheBuffer::Instance()->Create(BufferManager::VERTEX_BUFFER, "SPLASH_VERTEX_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::COLOR_BUFFER, "SPLASH_COLOR_BUFFER");
	TheBuffer::Instance()->Create(BufferManager::TEXTURE_BUFFER, "SPLASH_TEXTURE_BUFFER");

	//load splash screen sprite image from file based on filename passed
	TheTexture::Instance()->LoadFromFile(filename, "SPLASH_TEXTURE");

	//set dimension, texture, buffer and shader attribute properties of sprite object
	m_sprite.SetSpriteDimension(1024, 768);
	m_sprite.SetTextureID("SPLASH_TEXTURE");
	m_sprite.SetBufferID("SPLASH_VERTEX_BUFFER", "SPLASH_COLOR_BUFFER", "SPLASH_TEXTURE_BUFFER");
	m_sprite.SetShaderAttribute("vertexIn", "colorIn", "textureIn");

	//get texture flag ID from fragment shader
	m_textureFlagUniformID = TheShader::Instance()->GetUniformID("isTextured");

	//set screen position for sprite object to be screen centre
	m_transform = glm::translate(m_transform, glm::vec3(512.0f, 384.0f, 0.0f));

	//set sprite alpha channel to 0 so that it fades in later
	//it will also need to be dynamic so that the alpha updates
	m_sprite.SpriteColor().A = 0.0f;
	m_sprite.SetSpriteType(Sprite::DYNAMIC);
	
	//set fading flag to fade in by default
	m_fade = FADE_IN;

}
//------------------------------------------------------------------------------------------------------
//function that updates image's alpha to fade in and out
//------------------------------------------------------------------------------------------------------
void SplashScreen::Update()
{

	//store keyboard key states in a temp variable for processing below
	const Uint8* keyState = TheInput::Instance()->GetKeyStates();

	//if TAB key was pressed, deactivate splash screen 
	if (keyState[SDL_SCANCODE_TAB])
	{
		m_isActive = false;
	}

	//if image is set to fade in and image is not yet fully opaque then fade in image
	if (m_sprite.SpriteColor().A <= 1.0f && m_fade == FADE_IN)
	{
		m_sprite.SpriteColor().A += 0.5f * (float)TheGame::Instance()->GetElapsedTimeSeconds();
	}

	//otherwise once image becomes opaque set flag to fade out and begin fading out
	else
	{
		m_fade = FADE_OUT;
		m_sprite.SpriteColor().A -= 0.5f * (float)TheGame::Instance()->GetElapsedTimeSeconds();
	}
	
	//once image becomes transparent again deactivate this splash screen
	if (m_sprite.SpriteColor().A <= 0.0f && m_fade == FADE_OUT)
	{
		m_isActive = false;
	}
	
}
//------------------------------------------------------------------------------------------------------
//function that displays the 2D splash screen
//------------------------------------------------------------------------------------------------------
bool SplashScreen::Draw()
{

	//setup screen in 2D orthographic mode because all splash screens are 2D 
	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

	//reset model matrix to identity so we don't accumulate transformations
	GameObject::SetIdentity();

	//apply splash screen position transformation to model matrix
	GameObject::MultiplyMatrix(m_transform);

	//send model matrix data to vertex shader 
	GameObject::ApplyMatrix();
	        
	//send texture flag to fragment shader
	TheShader::Instance()->SetUniformData(m_textureFlagUniformID, true);

	//draw splash screen image
	m_sprite.Draw();

	return true;

}
//------------------------------------------------------------------------------------------------------
//destructor that destroys VBO objects and unloads sprite image from memory 
//------------------------------------------------------------------------------------------------------
SplashScreen::~SplashScreen()
{

	//destroy vertex, color and texture VBOs for splash screen
	TheBuffer::Instance()->
	Destroy(BufferManager::VERTEX_BUFFER, BufferManager::CUSTOM_BUFFER, "SPLASH_VERTEX_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::COLOR_BUFFER, BufferManager::CUSTOM_BUFFER, "SPLASH_COLOR_BUFFER");
	TheBuffer::Instance()->
	Destroy(BufferManager::TEXTURE_BUFFER, BufferManager::CUSTOM_BUFFER, "SPLASH_TEXTURE_BUFFER");

	//free splash screen sprite image from memory
	TheTexture::Instance()->UnloadFromMemory(TextureManager::CUSTOM_TEXTURE, "SPLASH_TEXTURE");

}