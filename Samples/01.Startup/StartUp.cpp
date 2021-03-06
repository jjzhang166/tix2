// StartUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TiX.h"

class MyTestThread : public TThread
{
public:
	MyTestThread(const TString& Name)
		: TThread(Name)
	{}

	virtual void Run()
	{
		static int32 a = 0;
		printf("MyTestThread says hello ... %d\n", a++);
		TThread::ThreadSleep(10);
	}
};

void TestNormalRun()
{
	// Start Loop
	TEngine::Get()->Start();
}

void TestThread()
{
	// Test thread
	MyTestThread* tt = ti_new MyTestThread("TestTixThreadddd");
	tt->Start();

	// Start Loop
	TEngine::Get()->Start();

	// When quit
	tt->Stop();
	ti_delete tt;
}
class MyTestTaskThread : public TTaskThread
{
public:
	MyTestTaskThread(const TString& Name)
		: TTaskThread(Name)
	{}
};

class MyTestTask : public TTask
{
	virtual void Execute()
	{
		static int32 aa = 0;
		_LOG(Log, "Task index: %d\n", aa++);
	}
};
void TestTask()
{
	// Test task thread
	MyTestTaskThread* tt = ti_new MyTestTaskThread("TestTaskThread");
	tt->Start();

	for (int32 i = 0; i < 4; ++i)
	{
		MyTestTask* task1 = ti_new MyTestTask;
		tt->AddTask(task1);
	}

	// Start Loop
	TEngine::Get()->Start();

	// When quit
	tt->Stop();
	ti_delete tt;
}

#include <sstream>
class TMyTicker : public TTicker
{
public:
	virtual void Tick(float Dt)
	{
		_LOG(Log, "TMyTestTicker is Ticking, Dt is %f.\n", Dt);
	}
};

class FMyTestRenderer : public FRenderer
{
public:
	virtual void Render(FRHI * RHI)
	{
		_LOG(Log, "My Test Renderer is rendering.\n");
	}
};

void TestTickerAndRenderer()
{
	TEngine::Get()->AddTicker(ti_new TMyTicker());
	TEngine::Get()->AddRenderer(ti_new FMyTestRenderer());

	// Start Loop
	TEngine::Get()->Start();
}

int main()
{
	{
		TEngineConfiguration Config;
		Config.Name = "First TiX Test App";
		Config.Width = 1280;
		Config.Height = 720;

		TEngine::InitEngine(Config);

		//TestNormalRun();
		//TestThread();
		//TestTask();
		TestTickerAndRenderer();

	}

	_CrtDumpMemoryLeaks();

    return 0;
}

