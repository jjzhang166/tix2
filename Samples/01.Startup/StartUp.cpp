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
		printf("hello ... %d\n", a++);
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
		_LOG("Task index: %d\n", aa++);
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

class FMyTestRenderer : public FRenderer
{
public:
	virtual void Render(FRHI * RHI)
	{
		_LOG("My Test Renderer is rendering.\n");
	}
};

void TestAddRenderer()
{
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
		TestAddRenderer();

	}

	_CrtDumpMemoryLeaks();

    return 0;
}

