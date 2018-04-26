/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	class FRenderThread;

	class TEngine
	{
	public:      
        
		TI_API static TEngine* Get();
		TI_API static void	InitEngine(const TEngineConfiguration& Config);
		TI_API static void	Destroy();

		TI_API void Start();
		TI_API TDevice*	GetDevice();
		TI_API FRenderThread* GetRenderThread();
		TI_API void AddRenderer(FRenderer* Renderer);
	private:
		TEngine();
		~TEngine();
		static TEngine* s_engine;

	protected:
		// Init every thing for engine
		void Init(const TEngineConfiguration& Config);

	private:
		TDevice * Device;
		FRenderThread * RenderThread;
	};
}
