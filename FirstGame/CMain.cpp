#include "CExample.h"
#include "SGameConfig.h"
#include "CDevice.h"
#define _CRTDBG_MAP_ALLOC        // For detecting memory leaks 
#include <stdlib.h>              // For detecting memory leaks 
#include <crtdbg.h>              // For detecting memory leaks 

int main()
{
	// Check for memory leak if debug build    
#if defined(DEBUG) | defined(_DEBUG)        
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	SGameConfig cnf = {
		640,
		480,
		false,
		"Hello",
		new CExample()
	};
	GameTutor::StartApp(cnf);
	//while (true);
	return 0;
}