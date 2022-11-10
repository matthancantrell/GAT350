#pragma once
#include "Framework/Component.h"

namespace neu
{
	class LightComponent : public Component
	{
	public:

	public:
		enum class Type
		{
			Point, // 00
			Directional, // 01
			Spot // 02
		};

		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Type type = Type::Point;
		glm::vec3 color{ 0 };

		float cutoff{ 45.0f };
		float exponent{ 50.0f };
	};
}