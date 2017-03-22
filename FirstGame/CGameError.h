// CGameError.h
// Error class thrown by game engine
#ifndef __CGAMEERROR_H__
#define __CGAMEERROR_H__
//#define WIN32_LEAN_AND_MEAN

#include <string>
#include <exception>

namespace gameErrorNS
{
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

class CGameError : public std::exception
{

private:
	int errorCode;
	std::string message;
	
public:
	// Default Constructor
	CGameError() throw() :errorCode(gameErrorNS::FATAL_ERROR),
		message("Undefined Error in game.") {}

	// Copy Constructor
	CGameError(const CGameError& e) throw() : std::exception(e),
		errorCode(e.errorCode), message(e.message) {}

	// Constructor with args
	CGameError(int code, const std::string &s) throw() : errorCode(code), message(s) {}

	//Assignment operator
	CGameError& operator= (const CGameError& rhs) throw ()
	{
		std::exception::operator= (rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}

	//Destructor
	virtual ~CGameError() throw() {}
	
	// Override what from base class 
	virtual const char* what() const throw() { return this->getMessage(); }
	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return this->errorCode; }

};

/*if (FAILED(result))    
throw(GameError(gameErrorNS::FATAL_ERROR,                     
"Error creating Direct3D device")); */

#endif 