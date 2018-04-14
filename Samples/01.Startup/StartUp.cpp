// StartUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TiX.h"


int main()
{
	{
		TEngineConfiguration Config;
		Config.Name = "First TiX Test App";
		Config.Width = 1280;
		Config.Height = 720;

		TEngine::InitEngine(Config);
		TEngine::Get()->Start();
	}

	_CrtDumpMemoryLeaks();

    return 0;
}

