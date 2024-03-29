#include "Game.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)


#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "MovementComponent.h"
#include "GameScoreBoardComponent.h"
#include "Scene.h"
#include "MessageCommand.h"
#include "Locator.h"
#include "AudioProvider.h"
#include "LoggedAudioProvider.h"
#include "MapComponent.h"
#include "BulletHandlerComponent.h"

#include "MidCrystalComponent.h"

#include "TankComponent.h"
#include <SpriteGroup.h>

#include <SDL_mixer.h>



void Game::LoadGame() const
{
	using namespace dae;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	{
		auto& input = dae::InputManager::GetInstance();
		//input.AddKeyboardInput(0);
		input.AddKeyboardInput(0);
		input.AddControllerInput(1, 0);
	}

	{
		dae::Audio_API* service = new dae::AudioProvider();
		dae::Locator::Provide(service);
	}
	//{
	//	dae::Audio_API* service = new dae::LoggedAudioProvider(dae::Locator::GetAudio()); //log audio
	//	dae::Locator::Provide(service);
	//}

	//dae::Locator::GetAudio().LoadSound(1, "../Data/04_Lose_Life.mp3");
	dae::Locator::GetAudio().LoadSound(1, "../Data/pew-pew-lame-sound-effect.mp3");
	dae::Locator::GetAudio().LoadSound(2, "../Data/Woosh-Mark_DiAngelo-4778593.mp3");


	auto go = std::make_shared<dae::GameObject>();

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//scene.Add("-Text", go);
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<dae::TextComponent>("TextComponent", new dae::TextComponent("Programming 4 Assignment", font));
	//go->SetAbsoluteTransform(80, 20);

	//////////////

	go = std::make_shared<dae::GameObject>();
	scene.Add("-Map", go);
	//go->AddComponent<MapComponent>("MapComponent", new MapComponent("../Data/Level1.txt", "SpriteSheetUpdated.png"/*"TronSpriteSheet.png"*/));
	go->AddComponent<MapComponent>("MapComponent", new MapComponent("../Data/Level1.txt", "TronSpriteSheetUpdated.png"));
	go->SetAbsoluteTransform(0, 0);

	//TankBulletsComponent::s_Map = go->GetComponent<MapComponent>("MapComponent");

	go = std::make_shared<dae::GameObject>();
	scene.Add("_BulletHandler", go);
	//go->AddComponent<MapComponent>("MapComponent", new MapComponent("../Data/Level1.txt", "SpriteSheetUpdated.png"/*"TronSpriteSheet.png"*/));
	go->AddComponent<BulletHandlerComponent>("BulletHandlerComponent", new BulletHandlerComponent());


	go = std::make_shared<dae::GameObject>();
	scene.Add("Tank", go);
	go->SetAbsoluteTransform(32, 32);
	go->AddComponent<TankComponent>("TankComponent", new TankComponent(0, 0, 0));

	go = std::make_shared<dae::GameObject>();
	scene.Add("Tank2", go);
	go->SetAbsoluteTransform(32 * 24, 32 * 22);
	go->AddComponent<TankComponent>("TankComponent", new TankComponent(1, 1, 6));



	go = std::make_shared<dae::GameObject>();
	scene.Add("FPSDisplay", go);
	go->AddComponent<dae::FPSComponent>("FPSComponent", new dae::FPSComponent());
	go->SetRelativeTransform(934, 20);

	go = std::make_shared<dae::GameObject>();
	scene.Add("Scoreboard", go);
	go->AddComponent<dae::GameScoreBoardComponent>("GameScoreBoardComponent", new dae::GameScoreBoardComponent(2, "Tank"));
	go->SetParent(scene.GetGameObject("FPSDisplay"));
	go->SetRelativeTransform(0, 40);



	go = std::make_shared<dae::GameObject>();
	scene.Add("_Logo", go);
	go->AddComponent<dae::TextureComponent>("TextureComponent", new dae::TextureComponent("MidCrystal.png", dae::Transform(-64, -64)));
	go->AddComponent<MidCrystalComponent>("MidCrystalComponent", new MidCrystalComponent(128/4*3, 128 / 4 * 3));
	go->SetAbsoluteTransform(464, 432);


	{
		auto& input = dae::InputManager::GetInstance();
		//input.AddCommandsToController(0, ControllerButton::A, ButtonStates::Down, new MessageCommand(std::string("oo")));
		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Pressed, new MessageCommand(std::string("Pressed")));
		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Released , new MessageCommand(std::string("Released")));
		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Up, new MessageCommand(std::string("Up")));
		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Down, new MessageCommand(std::string("Down")));
		input.AddCommandsToController(1, dae::ControllerButton::A, dae::ButtonStates::Down, new dae::MessageCommand(std::string("oo")));
	}
}