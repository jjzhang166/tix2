/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "TTaskThread.h"

namespace tix
{
	TTask::TTask()
	{
	}

	TTask::~TTask()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	TTaskThread::TTaskThread(const TString& Name)
		: TThread(Name)
	{
	}

	TTaskThread::~TTaskThread()
	{
	}

	void TTaskThread::Run()
	{
		unique_lock<mutex> TaskLock(TaskMutex);
		TaskCond.wait(TaskLock);

		TTask* Task;
		while (Tasks.GetSize() > 0)
		{
			Tasks.PopFront(Task);
			DoTask(Task);
		}
	}

	void TTaskThread::Stop()
	{
		if (Thread != nullptr)
		{
			unique_lock<mutex> CLock(TaskMutex);
			IsRunning = false;
			TaskCond.notify_one();
			Thread->join();

			ti_delete Thread;
			Thread = nullptr;
		}
	}

	void TTaskThread::DoTask(TTask* Task)
	{
		TI_TODO("Check DoTask in correct thread.");
		Task->Execute();

		// release task memory
		ti_delete Task;
	}

	void TTaskThread::AddTask(TTask* Task)
	{
		TI_TODO("Check AddTask in correct thread.");

		unique_lock<mutex> CLock(TaskMutex);
		Tasks.PushBack(Task);
		TaskCond.notify_one();
	}
}