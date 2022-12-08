#include "Engine.h" 
#include <iostream>

#define POST_PROCESS

int main(int argc, char** argv)
{
	LOG("Application Started...");

	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	LOG("Window Initialized...");
	neu::g_gui.Initialize(neu::g_renderer);

	// Create FrameBuffer Texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	// create framebuffer
 	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	// load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/final.scn");

	float x = 0;
	glm::vec3 rot{ 0,0,0 };
	float ri = 1;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_gui.BeginFrame(neu::g_renderer);

		auto actor = scene->GetActorFromName("Oscar");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		auto program = neu::g_resources.Get<neu::Program>("shaders/unlit/texture.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}
		
		ImGui::Begin("Howdy :D");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::End();

		scene->Update();

		neu::g_renderer.BeginFrame();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		////render pass 1 (render to framebuffer)
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}

		// render pass 2 (render to screen)
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}