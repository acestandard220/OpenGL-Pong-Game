#pragma once
#include "Gameobject.h"
#include "glm/glm.hpp"

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define PONG_UNBIND_VAO() glBindVertexArray(0);

namespace SpriteRenderer
{
	struct VertexData
	{
		glm::vec3 position{ 0.0f, 0.0f, 0.0f };
		glm::vec2 texture_coord{ 0.0f, 0.0f };
	};

	struct RendererData
	{
		uint32_t vbo;
		uint32_t vao;

		Sprite* sprite;
		uint32_t program;
	
		glm::mat4 model = glm::mat4(1.0);
		glm::mat4 view;
		glm::mat4 projection; 

		float quad_vertex[30] =
		{
			-1.0f,  1.0f, 0.0, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0, 1.0f, 0.0f,

			-1.0f,  1.0f, 0.0, 0.0f, 1.0f,
			 1.0f, -1.0f, 0.0, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0, 0.0f, 0.0f
		};

	

		VertexData* vertex_data;
	
		const char* vertexSource = R"(
			#version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTex;

			out vec2 TexCoord;

			uniform mat4 vp;
			uniform mat4 model;

            void main()
            {
                gl_Position = vp * model * vec4(aPos,1.0f);
                TexCoord = aTex;
            }

        )";
		const char* fragmentSource = R"(

			#version 330 core
			out vec4 FragColor;

            uniform sampler2D sprite_texture;
			
            in vec2 TexCoord;

			void main()
			{
   
				vec4 texture_color = texture(sprite_texture,TexCoord);
				if(texture_color.a < 0.1f)
				{
					discard;
				}

				FragColor = texture_color;

			}
		)";

		~RendererData();

	};

	

	void Initizialize();
	
	void InitBuffers();

	void InitShaders();

	void InitializeTransforms();
	
	void ShutDown();


	void DrawSprite(Gameobject& object);

	void DrawQuadRaw(Texture2D& texture);

}