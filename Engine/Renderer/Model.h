#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Math/MathUtils.h"

#include "Resource/Resource.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include<assimp/scene.h>
#include <assimp/postprocess.h>

namespace neu
{
	class Model : public Resource
	{
	public:

		struct vertex_t
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
		};

		Model() = default;
		Model(const std::vector<neu::Vector2>& points, const neu::Color& color) :
			m_points{ points },
			m_color{ color }
		{
		}
		Model(const std::string& filename);

		bool Create(std::string filename, ...) override;
		//bool Create(std::string filename, ...) override;

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale = Vector2{ 1, 1 });
		void Draw(Renderer& renderer, const Transform& transform);

		bool Load(const std::string& filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }

		VertexBuffer m_vertexBuffer;

	private:
		neu::Color m_color{ 0, 0, 0, 0 };
		std::vector<neu::Vector2> m_points;

		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

		float m_radius = 0;
	};
}
