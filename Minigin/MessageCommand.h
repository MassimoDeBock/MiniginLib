#pragma once
#include "Command.h"

namespace dae {
	class MessageCommand :	public Command
	{
	public:
		MessageCommand(const std::string& text);
		void Execute() override;
	private:
		std::string m_OutputString;
	};

}