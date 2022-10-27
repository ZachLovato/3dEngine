#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>
#include <string>

#include "VertexBuffer.h" 
#include "Math/MathUtils.h" 

#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h> 

namespace wrap
{
	class Model : public Resource
	{
	public:
		struct vertex_t
		{
			glm::vec3 position;
			glm::vec2 texcoord;
			glm::vec3 normal;
		};

	public:
		bool Create(std::string filename, ...) override;

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		VertexBuffer m_vertexBuffer;

		/*Model() = default;
		Model(const std::vector<wrap::Vector2>& points, const wrap::Color& color) :
			m_points{ points },
			m_color{ color }
		{
		}
		Model(const std::string& filename);

		bool Create(std::string filename, ...) override;

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale = Vector2{ 1, 1 });
		void Draw(Renderer& renderer, const Transform& transform);

		bool Load(const std::string& filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }*/

	private:
		wrap::Color m_color{ 0, 0, 0, 0 };
		std::vector<wrap::Vector2> m_points;

		float m_radius = 0;
	};
}
