#include "TetrisPiece.h"

TetrisPiece::TetrisPiece(std::shared_ptr<Mesh> mesh, glm::vec2 position, glm::vec2 scale, GLuint modelLocation, GLuint shaderID,
	glm::vec4 color,
	Tetromino tetromino, unsigned int gridSize)
	: Object(mesh, position, scale, modelLocation, shaderID, color)
{
	m_CurrentRotation = 0;
	m_GridSize = gridSize;

	m_GridStart = position;
	m_Position = position += glm::vec2(20 * m_GridSize, 0.0f);

	glm::vec2 right = glm::vec2(1.0f, 0.0f) * (float)m_GridSize;
	glm::vec2 left = glm::vec2(-1.0f, 0.0f) * (float)m_GridSize;
	glm::vec2 up = glm::vec2(0.0f, 1.0f) * (float)m_GridSize;
	glm::vec2 down = glm::vec2(0.0f, -1.0f) * (float)m_GridSize;

	if (tetromino == Tetromino::I)
	{
		std::vector<Object> iRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 3.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
		};

		std::vector<Object> iRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 3.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		 
		m_Rotations.push_back(iRotation0);
		m_Rotations.push_back(iRotation1);
		m_NumberOfRotations = 2;
	}
	else if (tetromino == Tetromino::O)
	{
		std::vector<Object> oRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
		};

		
		m_Rotations.push_back(oRotation0);
		m_NumberOfRotations = 1;
	}
	else if (tetromino == Tetromino::T)
	{
		std::vector<Object> tRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> tRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> tRotation2 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};
		
		std::vector<Object> tRotation3 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		m_Rotations.push_back(tRotation0);
		m_Rotations.push_back(tRotation1);
		m_Rotations.push_back(tRotation2);
		m_Rotations.push_back(tRotation3);
		m_NumberOfRotations = 4;
	}
	else if (tetromino == Tetromino::J)
	{
		std::vector<Object> jRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 2.0f) + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> jRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 2.0f) + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> jRotation2 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (up * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (up * 2.0f) + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> jRotation3 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (left * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (left * 2.0f) + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		
		m_Rotations.push_back(jRotation0);
		m_Rotations.push_back(jRotation1);
		m_Rotations.push_back(jRotation2);
		m_Rotations.push_back(jRotation3);
		m_NumberOfRotations = 4;
	}
	else if (tetromino == Tetromino::L)
	{
		std::vector<Object> lRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (down * 2.0f) + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> lRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (right * 2.0f) + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> lRotation2 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + up , m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (up * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (up * 2.0f) + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> lRotation3 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + left , m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (left * 2.0f), m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + (left * 2.0f) + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		m_Rotations.push_back(lRotation0);
		m_Rotations.push_back(lRotation1);
		m_Rotations.push_back(lRotation2);
		m_Rotations.push_back(lRotation3);
		m_NumberOfRotations = 4;
	}
	else if (tetromino == Tetromino::S)
	{
		std::vector<Object> sRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right + up, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right + up + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> sRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down + right + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		 
		m_Rotations.push_back(sRotation0);
		m_Rotations.push_back(sRotation1);
		m_NumberOfRotations = 2;
	}

	else if (tetromino == Tetromino::Z)
	{
		std::vector<Object> zRotation0 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + right + down + right, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		std::vector<Object> zRotation1 =
		{
			Object(m_Mesh, m_Position, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down + left, m_Scale, m_ModelLocation, m_ShaderID, m_Color),
			Object(m_Mesh, m_Position + down + left + down, m_Scale, m_ModelLocation, m_ShaderID, m_Color)
		};

		m_Rotations.push_back(zRotation0);
		m_Rotations.push_back(zRotation1);
		m_NumberOfRotations = 2;
	}

	m_IsFalling = true;
}

void TetrisPiece::Start()
{
	m_Position = m_GridStart;
	for (auto& i : m_Rotations)
		for (auto& j : i)
			j.SetPosition(j.GetPosition() - glm::vec2(15.0f * (float) m_GridSize, 0.0f));
}

void TetrisPiece::Update(bool* keys, GLfloat& deltaTime, GLfloat& moveSpeed, GLfloat& fallSpeed, GLfloat& rotationSpeed,
	std::shared_ptr<Object> grid, 
	std::list<Object*> fallenTiles, GLfloat initFallSpeed)
{
	m_TimeAcc1 += deltaTime;
	m_TimeAcc2 += deltaTime;
	m_TimeAcc3 += deltaTime;

	// Check that rotation works
	if (m_TimeAcc3 > rotationSpeed && m_IsFalling)
	{
		m_TimeAcc3 = 0.0f;

		if (keys[GLFW_KEY_SPACE])
		{
			m_CurrentRotation = ++m_CurrentRotation % m_NumberOfRotations;
		}
	}

	glm::vec2 directionVector = glm::vec2(0.0f, 0.0f);
	if (m_TimeAcc1 > moveSpeed && m_IsFalling)
	{
		m_TimeAcc1 = 0.0f;

		if (keys[GLFW_KEY_A])
		{
			directionVector.x = -(float)m_GridSize;
		}

		if (keys[GLFW_KEY_D])
		{
			directionVector.x = m_GridSize;
		}
		if (keys[GLFW_KEY_S])
		{
			fallSpeed = initFallSpeed / 3;
		}
		else if (!keys[GLFW_KEY_S])
			fallSpeed = initFallSpeed;
	}

	if (m_TimeAcc2 > fallSpeed && m_IsFalling)
	{
		m_TimeAcc2 = 0.0f;
		directionVector.y = -(float)m_GridSize;
	}

	bool hasMoved = false;
	for (int i = 0; i < 4; i++)
	{
		if (m_Rotations[m_CurrentRotation][i].GetPosition().x + directionVector.x >
			grid->GetPosition().x + (grid->GetScale().x / 2.0f) && !hasMoved)
		{
			directionVector.x -= 1.0f * m_GridSize;
			hasMoved = true;
		}
		if (m_Rotations[m_CurrentRotation][i].GetPosition().x + directionVector.x <
			grid->GetPosition().x - (grid->GetScale().x / 2.0f) && !hasMoved)
		{
			directionVector.x += 1.0f * m_GridSize;
			hasMoved = true;
		}
		if (m_Rotations[m_CurrentRotation][i].GetPosition().y + directionVector.y <
			grid->GetPosition().y - (grid->GetScale().y / 2.0f) && !hasMoved)
		{
			directionVector.y = 0.0f;
			m_IsFalling = false;
			hasMoved = true;
		}
	}

	hasMoved = false;
	for (auto& j : fallenTiles)
	{
		for (auto& k : m_Rotations[m_CurrentRotation])
		{
			if (k.GetPosition() + directionVector == j->GetPosition())
			{
				if (k.GetPosition().y > j->GetPosition().y && m_IsFalling)
				{
					m_IsFalling = false;
					directionVector.y += m_GridSize;
				}
				if (k.GetPosition().x < j->GetPosition().x && m_IsFalling)
					directionVector.x -= m_GridSize;
				else if (k.GetPosition().x > j->GetPosition().x && m_IsFalling)
					directionVector.x += m_GridSize;
			}
		}
	}

	for (auto& i : m_Rotations)
		for (auto& j : i)
			j.SetPosition(j.GetPosition() + directionVector);
}

void TetrisPiece::Render()
{
	for (auto& i : m_Rotations[m_CurrentRotation])
		i.Render();
}
