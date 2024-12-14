#include "SpriteRenderer.h"

#define PONG_UNBIND_VAO() glBindVertexArray(0);

namespace SpriteRenderer
{
	RendererData* renderer_data = nullptr;

	RendererData::~RendererData()
	{
		glDeleteBuffers(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteProgram(program);

		delete sprite;
		delete vertex_data;

	}

	void InitBuffers()
	{
		glGenVertexArrays(1, &renderer_data->vao);
		glBindVertexArray(renderer_data->vao);

		glGenBuffers(1, &renderer_data->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, renderer_data->vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InitShaders()
	{
		uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader, 1, &renderer_data->vertexSource, nullptr);
		glShaderSource(fragment_shader, 1, &renderer_data->fragmentSource, nullptr);

		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);

		renderer_data->program = glCreateProgram();
		glAttachShader(renderer_data->program, vertex_shader);
		glAttachShader(renderer_data->program, fragment_shader);

		glLinkProgram(renderer_data->program);

		int success;
		char infoLog[512];
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(renderer_data->program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(renderer_data->program, 512, NULL, infoLog);
			std::cout << infoLog;
		}
	}

	void Initizialize()
	{
		renderer_data = new RendererData;
		glEnable(GL_BLEND);
		InitBuffers();
		InitShaders();
		InitializeTransforms();

	}

	void check()
	{
	
	}

	void InitializeTransforms()
	{
		renderer_data->view = glm::lookAt(glm::vec3(0.0f,0.0f,5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		renderer_data->projection = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);

		glm::mat4 vp = renderer_data->projection * renderer_data->view;

		glUseProgram(renderer_data->program);
		glUniformMatrix4fv(glGetUniformLocation(renderer_data->program, "vp"), 1, GL_FALSE, &vp[0][0]);
		glUseProgram(0);
	}

	void ShutDown()
	{
		delete renderer_data;
		
	}

	void compute_model(glm::vec2 position, int width, int height)
	{
		renderer_data->model = glm::mat4(1.0f);
		//renderer_data->model = glm::translate(renderer_data->model, {position,0.0f});

		glUseProgram(renderer_data->program);
		glUniformMatrix4fv(glGetUniformLocation(renderer_data->program, "model"), 1, GL_FALSE, &renderer_data->model[0][0]);
	}

	void DrawSprite(Gameobject& object)
	{
		renderer_data->vertex_data = new VertexData[6];

		renderer_data->vertex_data[0].position = { object.position,0.0f};
		renderer_data->vertex_data[0].texture_coord = { 0.0f, 0.0f };

		renderer_data->vertex_data[1].position = { object.position.x, object.position.y + object.size.y, 0.0f };
		renderer_data->vertex_data[1].texture_coord = { 0.0f, 1.0f };

		renderer_data->vertex_data[2].position = { object.position.x + object.size.x, object.position.y + object.size.y, 0.0f };
		renderer_data->vertex_data[2].texture_coord = { 1.0f, 1.0f };


		renderer_data->vertex_data[3].position = { object.position.x,object.position.y,0.0f };
		renderer_data->vertex_data[3].texture_coord = { 0.0f, 0.0f };

		renderer_data->vertex_data[4].position = { object.position.x + object.size.x,object.position.y,0.0f };
		renderer_data->vertex_data[4].texture_coord = {1.0f, 0.0f };

		renderer_data->vertex_data[5].position = { object.position.x + object.size.x, object.position.y + object.size.y, 0.0f };
		renderer_data->vertex_data[5].texture_coord = { 1.0f, 1.0f};

		glBindBuffer(GL_ARRAY_BUFFER, renderer_data->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, renderer_data->vertex_data, GL_DYNAMIC_DRAW);

		glUseProgram(renderer_data->program);

		compute_model(object.position, 1, 1);
		
		glUniform1i(glGetUniformLocation(renderer_data->program, "sprite_texture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object.sprite->get_texture_id());
		
		glBindVertexArray(renderer_data->vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void SpriteRenderer::DrawQuadRaw(Texture2D& texture)
	{
		renderer_data->view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.50f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		renderer_data->projection = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);

		glm::mat4 vp = renderer_data->projection * renderer_data->view;

		glUseProgram(renderer_data->program);
		glUniformMatrix4fv(glGetUniformLocation(renderer_data->program, "vp"), 1, GL_FALSE, &vp[0][0]);
		glUseProgram(0);

		glBindBuffer(GL_ARRAY_BUFFER, renderer_data->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(renderer_data->quad_vertex), renderer_data->quad_vertex, GL_DYNAMIC_DRAW);

		glUseProgram(renderer_data->program);
		glUniform1i(glGetUniformLocation(renderer_data->program, "sprite_texture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.get_id());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindVertexArray(renderer_data->vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}




}