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
#include "PeterPepperBrainComponent.h"
#include "DeathBox.h"
#include "GameScoreBoardComponent.h"
#include "PointsPickup.h"
#include "Scene.h"
#include "MessageCommand.h"
#include "Locator.h"
#include "AudioProvider.h"
#include "LoggedAudioProvider.h"

#include <SDL_mixer.h>


void Game::LoadGame() const
{
	using namespace dae;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	{
		auto& input = dae::InputManager::GetInstance();
		input.AddKeyboardInput(0);
		input.AddControllerInput(1, 0);
	}

	{
		dae::Audio_API* service = new dae::AudioProvider();
		dae::Locator::Provide(service);
	}
	{
		dae::Audio_API* service = new dae::LoggedAudioProvider(dae::Locator::GetAudio()); //log audio
		dae::Locator::Provide(service);
	}

	dae::Locator::GetAudio().LoadSound(1, "../Data/04_Lose_Life.mp3");


	auto go = std::make_shared<dae::GameObject>();
	scene.Add("--Background", go);
	go->AddComponent<dae::TextureComponent>("TextureComponent", new dae::TextureComponent("background.jpg"));



	go = std::make_shared<dae::GameObject>();
	scene.Add("-Logo", go);
	go->AddComponent<dae::TextureComponent>("TextureComponent", new dae::TextureComponent("logo.png"));
	go->AddComponent<dae::DeathBox>("DeathBox", new dae::DeathBox(glm::vec2(208, 65)));
	go->SetAbsoluteTransform(216, 180);



	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	scene.Add("-Text", go);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("TextComponent", new dae::TextComponent("Programming 4 Assignment", font));
	go->SetAbsoluteTransform(80, 20);

	for (int i = 0; i < 10; ++i) {
		go = std::make_shared<dae::GameObject>();
		scene.Add("PointsPickup" + std::to_string(i), go);
		go->SetAbsoluteTransform(float(150 + i * 20), 100);
		go->AddComponent<dae::PointsPickup>("PointsPickup", new dae::PointsPickup(glm::vec2(10, 10), 100));
	}

	go = std::make_shared<dae::GameObject>();
	scene.Add("FPSDisplay", go);
	go->AddComponent<dae::FPSComponent>("FPSComponent", new dae::FPSComponent());
	go->SetRelativeTransform(50, 100);



	go = std::make_shared<dae::GameObject>();
	scene.Add("Peter_Pepper", go);
	go->SetAbsoluteTransform(400, 400);
	go->AddComponent<dae::PeterPepperBrainComponent>("PeterPepperBrainComponent", new dae::PeterPepperBrainComponent(0));


	go = std::make_shared<dae::GameObject>();
	scene.Add("Peter_Pepper1", go);
	go->SetAbsoluteTransform(200, 400);
	go->AddComponent<dae::PeterPepperBrainComponent>("PeterPepperBrainComponent", new dae::PeterPepperBrainComponent(1));


	go = std::make_shared<dae::GameObject>();
	scene.Add("Scoreboard", go);
	go->AddComponent<dae::GameScoreBoardComponent>("GameScoreBoardComponent", new dae::GameScoreBoardComponent(2, "Peter_Pepper"));
	go->SetParent(scene.GetGameObject("FPSDisplay"));
	go->SetRelativeTransform(0, 40);

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