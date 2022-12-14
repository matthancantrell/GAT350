#pragma once
#include "Framework/Component.h"
namespace neu
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		void Initialize() override;
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		float speed = 0;
		float sensitivity = 0.1f;

		float m_yaw = 0;
		float m_pitch = 0;
	};
}