#pragma once

#include <tchar.h>
#include <exception>
#include <string>

using namespace std;

class ApplicationException : public exception
{
public: 
	ApplicationException() : exception() {}
	
	ApplicationException(const char* szMessage)
	{
		m_message = szMessage;
	}

	const char* what() const
	{
		return m_message.c_str();
	}

protected:
	string m_message;
};
