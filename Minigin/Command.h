#pragma once

namespace dae {
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
	};
}