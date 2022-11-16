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
	neu::g_gui.Initialize(neu::g_renderer);

	// load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/test.scn");

	float x = 0;
	glm::vec3 pos = { 0,0,0 };

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		neu::g_gui.BeginFrame(neu::g_renderer);

		auto actor = scene->GetActorFromName("Light");
		if (actor)
		{
			actor->m_transform.position = pos;
		}
		
		ImGui::Begin("Howdy :D");
		ImGui::Button("Press Me!");
		ImGui::SliderFloat3("pos", &pos[0], -10.0f, 10.0f);
		ImGui::End();

		scene->Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);
		neu::g_gui.Draw();

 		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	LOG("Emptying Scene...");
	neu::Engine::Instance().Shutdown();
	LOG("Successfully Shut Down...");
	return 0;
}