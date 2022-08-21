#include "MiniginPCH.h"
#include "Minigin.h"
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
#include "Scene.h"
#include "MessageCommand.h"
#include "Locator.h"
#include "AudioProvider.h"
#include "LoggedAudioProvider.h"

#include <SDL_mixer.h>

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1100,
		864,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	Locator::Initialize();
	InputManager::GetInstance().Initialize();
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 4096);
}

/**
 * Code constructing the scene world starts here
 */
//void dae::Minigin::LoadGame() const
//{
//	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
//
//	{
//		auto& input = InputManager::GetInstance();
//		input.AddKeyboardInput(0);
//		input.AddControllerInput(1,0);
//	}
//
//	{
//		Audio_API* service = new AudioProvider();
//		Locator::Provide(service);
//	}
//	{
//		Audio_API* service = new LoggedAudioProvider(Locator::GetAudio()); //log audio
//		Locator::Provide(service);
//	}
//
//	Locator::GetAudio().LoadSound(1, "../Data/04_Lose_Life.mp3");
//
//
//	auto go = std::make_shared<GameObject>();
//	scene.Add("--Background", go);
//	go->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("background.jpg"));
//
//
//
//	go = std::make_shared<GameObject>();
//	scene.Add("-Logo", go);
//	go->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("logo.png"));
//	go->AddComponent<DeathBox>("DeathBox", new DeathBox(glm::vec2(208, 65)));
//	go->SetAbsoluteTransform(216, 180);
//
//
//
//	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
//	scene.Add("-Text", go);
//	go = std::make_shared<GameObject>();
//	go->AddComponent<TextComponent>("TextComponent", new TextComponent("Programming 4 Assignment", font));
//	go->SetAbsoluteTransform(80, 20);
//
//	for (int i = 0; i < 10; ++i) {
//		go = std::make_shared<GameObject>();
//		scene.Add("PointsPickup"+to_string(i), go);
//		go->SetAbsoluteTransform(float(150 + i*20), 100);
//		go->AddComponent<PointsPickup>("PointsPickup", new PointsPickup(glm::vec2(10, 10), 100));
//	}
//
//	go = std::make_shared<GameObject>();
//	scene.Add("FPSDisplay", go);
//	go->AddComponent<FPSComponent>("FPSComponent", new FPSComponent());
//	go->SetRelativeTransform(50, 100);
//
//
//
//	go = std::make_shared<GameObject>();
//	scene.Add("Peter_Pepper", go);
//	go->SetAbsoluteTransform(400, 400);
//	go->AddComponent<PeterPepperBrainComponent>("PeterPepperBrainComponent", new PeterPepperBrainComponent(0));
//
//
//	go = std::make_shared<GameObject>();
//	scene.Add("Peter_Pepper1", go);
//	go->SetAbsoluteTransform(200, 400);
//	go->AddComponent<PeterPepperBrainComponent>("PeterPepperBrainComponent", new PeterPepperBrainComponent(1));
//
//
//	go = std::make_shared<GameObject>();
//	scene.Add("Scoreboard", go);
//	go->AddComponent<GameScoreBoardComponent>("GameScoreBoardComponent", new GameScoreBoardComponent(2, "Peter_Pepper"));
//	go->SetParent(scene.GetGameObject("FPSDisplay"));
//	go->SetRelativeTransform(0, 40);
//
//	{
//		auto& input = InputManager::GetInstance();
//		//input.AddCommandsToController(0, ControllerButton::A, ButtonStates::Down, new MessageCommand(std::string("oo")));
//		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Pressed, new MessageCommand(std::string("Pressed")));
//		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Released , new MessageCommand(std::string("Released")));
//		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Up, new MessageCommand(std::string("Up")));
//		//input.AddCommandsToKeyboard(0, SDL_SCANCODE_Q, ButtonStates::Down, new MessageCommand(std::string("Down")));
//		input.AddCommandsToController(1, ControllerButton::A, ButtonStates::Down, new MessageCommand(std::string("oo")));
//	}
//}

void dae::Minigin::Cleanup()
{

	Renderer::GetInstance().Destroy();
	Mix_CloseAudio();
	Locator::Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
	GameLoop();
	Cleanup();
}


void dae::Minigin::GameLoop()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetFixedTimeStep(fixedTimeStep);
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	input.CheckConnections();
	//input.AddCommandsToController(0, ControllerButton::A, ButtonStates::Down, new MessageCommand(std::string("oo")));


	sceneManager.BeginPlay();
	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
		while (lag >= fixedTimeStep) {
			sceneManager.FixedUpdate();
			lag -= fixedTimeStep;
		}
		sceneManager.Update(deltaTime);
		renderer.Render();

		const auto sleepTime = currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}