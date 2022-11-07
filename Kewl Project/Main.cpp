#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	LOG("Application Started...");

	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_audioSystem.Initialize();
	LOG("Audio System Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");

	// load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/emissive.scn");

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		auto actor = scene->GetActorFromName("Spot");
		if (actor)
		{
			actor->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}
		

		scene->Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

 		neu::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}