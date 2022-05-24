#pragma once
struct SDL_Window;
namespace dae
{
	static float fixedTimeStep{ 0.02f };
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		void GameLoop();

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}