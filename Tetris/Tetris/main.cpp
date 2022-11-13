#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <list>

#include "Window.h"
#include "Shader.h"
#include "Rectangle.h"
#include "Object.h"
#include "TetrisPiece.h"

glm::vec4 iColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
glm::vec4 oColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
glm::vec4 tColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
glm::vec4 jColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
glm::vec4 lColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 sColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
glm::vec4 zColor = glm::vec4(0.5f, 0.2f, 1.4f, 1.0f);
glm::vec4 gridColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

TetrisPiece::Tetromino genRandomTetromino(glm::vec4& color)
{
	int randNum = (float)(rand() % 7);

	switch (randNum)
	{
	case 0:
		color = iColor;
		break;
	case 1:
		color = oColor;
		break;
	case 2:
		color = tColor;
		break;
	case 3:
		color = jColor;
		break;
	case 4:
		color = lColor;
		break;
	case 5:
		color = sColor;
		break;
	case 6:
		color = zColor;
		break;
	}

	return (TetrisPiece::Tetromino) randNum;
}

int main()
{
	srand(time(NULL));
	// Delta time
	GLfloat now;
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	Window window;

	int gridSize = 22;
	int gridWidth = 5;
	int gridHeight = 10;

	float width = (gridWidth + 18) * gridSize;
	float height = (gridHeight + 21) * gridSize;

	glm::vec2 gridPos = glm::vec2(-4 * (float)gridSize, 0.0f);
	glm::vec2 gridStart = gridPos + glm::vec2(-(float)((gridWidth / 2) * gridSize), (gridHeight * gridSize) - gridSize) 
		- glm::vec2(-gridSize / 2, -gridSize / 2);
	
	// Window
	window = Window(width, height);
	window.CreateNewWindow();

	// Shader
	Shader shader = Shader();
	shader.CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
	shader.UseShader();
	shader.Validate();

	// Projection matrix uniform
	glm::mat4 projection = glm::ortho((GLfloat)(-(window.GetBufferWidth() / 2)), (GLfloat)(window.GetBufferWidth() / 2),
		(GLfloat)(-(window.GetBufferHeight() / 2)), (GLfloat)(window.GetBufferHeight() / 2));

	GLuint uProjection = shader.GetProjectionLocation();

	glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projection));

	// Get model matrix location
	GLuint uModel = shader.GetModelLocation();

	std::shared_ptr<Rectangle> rect(new Rectangle());

	GLenum keyUp = GLFW_KEY_W;
	GLenum keyDown = GLFW_KEY_S;
	GLenum keyRight = GLFW_KEY_D;
	GLenum keyLeft = GLFW_KEY_A;
	// Main loop
	window.GetKeys()[keyUp] = false;
	window.GetKeys()[keyDown] = false;
	window.GetKeys()[keyLeft] = false;
	window.GetKeys()[keyRight] = false;

	std::deque<TetrisPiece> pieces;

	glm::vec4 currentColor;
	TetrisPiece::Tetromino tetromino;
	tetromino = genRandomTetromino(currentColor);
	pieces.push_back(TetrisPiece(rect, gridStart, glm::vec2(gridSize, gridSize), uModel, shader.GetShaderID(), 
		currentColor, tetromino, gridSize));
	tetromino = genRandomTetromino(currentColor);
	pieces.push_back(TetrisPiece(rect, gridStart, glm::vec2(gridSize, gridSize), uModel, shader.GetShaderID(),
		currentColor, tetromino, gridSize));
	pieces.front().Start();

	std::list <Object*> fallenTiles;

	GLfloat moveSpeed = 0.4f;
	GLfloat fallSpeed = 0.5f;
	GLfloat rotationSpeed = 0.25f;
	GLfloat initFallSpeed = fallSpeed;

	std::shared_ptr<Object> grid(new Object(rect, gridPos, 
		glm::vec2(gridWidth * gridSize * 2, gridHeight * gridSize * 2), uModel, shader.GetShaderID(), gridColor));

	window.GetKeys()[GLFW_KEY_SPACE] = false;
	window.GetKeys()[GLFW_KEY_A] = false;
	window.GetKeys()[GLFW_KEY_D] = false;
	window.GetKeys()[GLFW_KEY_S] = false;

	Object line = Object(rect, glm::vec2(0.0f, 0.0f), glm::vec2(gridSize * gridWidth * 2, gridSize), uModel, shader.GetShaderID(),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;

	int flashTime = 5;
	float animationTimeAccumulator = 0.0f;
	float duration1 = flashTime;
	float duration2 = flashTime + duration1;
	float duration3 = flashTime + duration2;
	float duration4 = flashTime + duration3;
	unsigned int numberOfTilesInThisLine = 0;
	bool justCompletedAnimation = 0;
	float completedAnimationLocation = 0.0f;

	while (!window.GetShouldClose())
	{
		now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		grid->Render();

		pieces.front().Update(window.GetKeys(), deltaTime, moveSpeed, fallSpeed, rotationSpeed, grid, fallenTiles, initFallSpeed);
		pieces.front().Render();

		pieces[pieces.size() - 1].Render();

		if (!pieces.front().IsFalling())
		{
			for (auto& i : pieces.front().GetTiles())
			{
				if (i.GetPosition().y > gridStart.y)
				{
					std::cout << "GAME OVER" << std::endl;
					return 0;
				}
			}

			for (auto &i : pieces.front().GetTiles())
				fallenTiles.push_back(new Object(i));
			pieces.pop_front();

			pieces.front().Start();

			glm::vec4 currentColor;
			TetrisPiece::Tetromino tetromino;
			tetromino = genRandomTetromino(currentColor);
			pieces.push_back(TetrisPiece(rect, gridStart, glm::vec2(gridSize, gridSize), uModel, shader.GetShaderID(),
				currentColor, tetromino, gridSize));

			fallSpeed -= 0.004f;
			initFallSpeed -= 0.004f;
			rotationSpeed -= 0.00005f;
			moveSpeed -= 0.00055f;
			if (initFallSpeed < 0.1f)
			{
				fallSpeed = 0.01;
				initFallSpeed = 0.01f;
			}
			if (rotationSpeed < 0.05f)
				rotationSpeed = 0.05f;
			if (moveSpeed < 0.06f)
				moveSpeed = 0.06f;
		}

		for (int height = gridStart.y; height > gridStart.y - (gridHeight * 2 * gridSize); height -= gridSize)
		{
			numberOfTilesInThisLine = 0;

			if (justCompletedAnimation)
			{
				animationTimeAccumulator = 0.0f;

				for (std::list<Object*>::iterator tilej = fallenTiles.begin(); tilej != fallenTiles.end(); tilej++)
					if ((*tilej)->GetPosition().y > completedAnimationLocation)
						(*tilej)->SetPosition((*tilej)->GetPosition() - glm::vec2(0.0f, gridSize));

				justCompletedAnimation = false;
			}

			line.SetPosition(glm::vec2((4.0f * -(float)gridSize), height));
			for (std::list<Object*>::iterator tile = fallenTiles.begin(); tile != fallenTiles.end(); tile++)
			{
				if ((*tile)->GetPosition().y < line.GetPosition().y + (line.GetScale().y / 2) &&
					(*tile)->GetPosition().y > line.GetPosition().y - (line.GetScale().y / 2))
					numberOfTilesInThisLine++;
				else
					continue;
			}

			if (numberOfTilesInThisLine == gridWidth * 2)
			{
				for (std::list<Object*>::iterator tile = fallenTiles.begin(); tile != fallenTiles.end(); tile++)
				{
					if ((*tile)->GetPosition().y < line.GetPosition().y + (line.GetScale().y / 2) &&
						(*tile)->GetPosition().y > line.GetPosition().y - (line.GetScale().y / 2))
					{
						// Animation
						animationTimeAccumulator += deltaTime;
						if (animationTimeAccumulator < duration1 && animationTimeAccumulator > 0.0f)
						{
							(*tile)->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
						}
						else if (animationTimeAccumulator < duration2 && animationTimeAccumulator > duration1)
						{
							(*tile)->SetColor(gridColor);
						}
						else if (animationTimeAccumulator < duration3 && animationTimeAccumulator > duration2)
						{
							(*tile)->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
						}
						else if (animationTimeAccumulator < duration4 && animationTimeAccumulator > duration3)
						{
							(*tile)->SetColor(gridColor);
						}
						else if (animationTimeAccumulator > duration4)
						{
							for (std::list<Object*>::iterator tile = fallenTiles.begin(); tile != fallenTiles.end(); tile++)
							{
								if ((*tile)->GetPosition().y < line.GetPosition().y + (line.GetScale().y / 2) &&
									(*tile)->GetPosition().y > line.GetPosition().y - (line.GetScale().y / 2))
								{
									delete (*tile);
									fallenTiles.erase(tile);
								}

								justCompletedAnimation = true;
								completedAnimationLocation = line.GetPosition().y;
							}
						}
					}
					else
						continue;
				}
			}
		}

		for (auto& i : fallenTiles)
			i->Render();

		window.SwapBuffers();
	}
}