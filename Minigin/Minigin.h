#pragma once
struct SDL_Window;
namespace dae
{
	static float fixedTimeStep{ 0.02f };
	class Minigin
	{
	public:
		void Initialize();
		virtual void LoadGame() const = 0;
		void Cleanup();
		void Run();
		void GameLoop();

	private:
		static const int MsPerFrame = 8; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}