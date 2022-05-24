#include "MiniginPCH.h"
#include "MessageCommand.h"

dae::MessageCommand::MessageCommand(const std::string& text)
	: m_OutputString(text)
{
}

void dae::MessageCommand::Execute()
{
	std::cout << m_OutputString<<'\n';
}
