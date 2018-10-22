// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__

class LogManager
{
	// Member Methods:
public:
	static LogManager& GetInstance();
	static void	DestroyInstance();
	~LogManager();

	void Log(const char* pcMessage);
	void Debug(const char* message);

	bool IsDebugging();
	void SetDebugging(bool debug);

protected:

private:
	LogManager();
	LogManager(const LogManager& logManager);
	LogManager& operator=(const LogManager& logManager);

	// Member Fields:
public:

protected:
	static LogManager* sm_pInstance;
	bool m_debugging;

private:

};

#endif // !__LOGMANAGER_H__
