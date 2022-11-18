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
	glm::vec3 rot{ 0,0,0 };
	float ri = 1;
	float interpolation = 1.0;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		neu::g_gui.BeginFrame(neu::g_renderer);

		auto actor = scene->GetActorFromName("Dog");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		auto program = neu::g_resources.Get<neu::Program>("shaders/unlit/rr.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
			program->SetUniform("interpolation", interpolation);
		}
		
		ImGui::Begin("Rotation");
		ImGui::DragFloat3("pos", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::DragFloat("Interpolation", &interpolation, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
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