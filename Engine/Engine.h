#pragma once

#include "Serialization/Json.h"
#include "Renderer/Model.h"
#include "Renderer/GUI.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Core/Utilities.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"
#include "Framework/EventManager.h"

#include "Components/PlayerComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/TextComponent.h"
#include "Components/TilemapComponent.h"
#include "Components/CharacterComponent.h"
#include "Components/CameraComponent.h"
#include "Components/CameraController.h"
#include "Components/LightComponent.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"
#include "Physics/PhysicsSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Program.h"
#include "Renderer/Material.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Cubemap.h"
#include "Renderer/FrameBuffer.h"

#include "glm/glm.hpp"

#include <memory>
#include <vector>
#include <list>
#include <variant>

namespace neu
{
	extern Renderer g_renderer;
	extern InputSystem g_inputSystem;
	extern AudioSystem g_audioSystem;
	extern Time g_time;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physicsSystem;
	extern EventManager g_eventManager;
	extern GUI g_gui;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();

		void Initialize();
		void Shutdown();

		void Update();
	};
}
