// COMP710 GP 2D Framework 2018

// This include:
#include "logmanager.h"

// Library includes:
#include <Windows.h>

// Static Members:
LogManager* LogManager::sm_pInstance = 0;

LogManager&
LogManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new LogManager();
	}

	return (*sm_pInstance);
}

void
LogManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

LogManager::LogManager()
{

}

LogManager::~LogManager()
{

}

void
LogManager::Log(const char* pcMessage)
{
	OutputDebugStringA(pcMessage);
	OutputDebugStringA("\n");
}

bool
LogManager::IsDebugging()
{
	return m_debugging;
}

void
LogManager::SetDebugging(bool debug)
{
	m_debugging = debug;
}

void
LogManager::Debug(const char* message)
{
	if (m_debugging)
	{
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
	}
}