#include "MyMesh.h"

MyMesh::MyMesh()
{
	//
}

MyMesh::~MyMesh()
{
	glDeleteShader(m_uShaderProgramID);
	glDeleteBuffers(1, &m_uVBO);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_uVAO);
}

void MyMesh::Init()
{
	glGenVertexArrays(1, &m_uVAO);
	glGenBuffers(1, &m_uVBO);

	glBindVertexArray(m_uVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);

	// Shader set up
	InitShader();

	glBindVertexArray(0);
}

void MyMesh::InitShader()
{
	m_uShaderProgramID = LoadShaders("Shaders//BasicColor.vs", "Shaders//BasicColor.fs");
	glUseProgram(m_uShaderProgramID);
}

void MyMesh::InitTriangle()
{
	glBindVertexArray(m_uVAO);

	// Consists of 3 vertices

	float triSize = m_scale;

	// Vertex 1 (Top)
	vertex vertexTopPoint;
	vertexTopPoint.position = glm::vec3(-triSize, -triSize, 0.0f);
	vertexTopPoint.color = glm::vec3(1.0f, 0.0f, 0.0f);
	m_vertices.push_back(vertexTopPoint);

	// Vertex 2 (Left Bottom)
	vertex vertexLeftBottom;
	vertexLeftBottom.position = glm::vec3(triSize, -triSize, 0.0f);
	vertexLeftBottom.color = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vertices.push_back(vertexLeftBottom);

	// Vertex 3 (Right Bottom)
	vertex vertexRightBottom;
	vertexRightBottom.position = glm::vec3(0.0f, triSize, 0.0f);
	vertexRightBottom.color = glm::vec3(0.0f, 0.0f, 1.0f);
	m_vertices.push_back(vertexRightBottom);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

	// Count the attributes
	int attributeCount = 2;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(1 * sizeof(glm::vec3)));

	glBindVertexArray(0);
}

void MyMesh::InitQuad()
{
	glBindVertexArray(m_uVAO);

	// Consists of 3 vertices

	float quadSize = 0.5f;

	// Vertex 1 (Top Left)
	vertex vertexTopLeft;
	vertexTopLeft.position = glm::vec3(-quadSize, quadSize, 0.0f);
	vertexTopLeft.color = glm::vec3(1.0f, 0.0f, 0.0f);

	// Vertex 2 (Top Right)
	vertex vertexTopRight;
	vertexTopRight.position = glm::vec3(quadSize, quadSize, 0.0f);
	vertexTopRight.color = glm::vec3(0.0f, 1.0f, 0.0f);

	// Vertex 3 (Bottom Left)
	vertex vertexBottomLeft;
	vertexBottomLeft.position = glm::vec3(-quadSize, -quadSize, 0.0f);
	vertexBottomLeft.color = glm::vec3(0.0f, 0.0f, 1.0f);

	// Vertex 4 (Bottom Right)
	vertex vertexBottomRight;
	vertexBottomRight.position = glm::vec3(quadSize, -quadSize, 0.0f);
	vertexBottomRight.color = glm::vec3(1.0f, 0.0f, 1.0f);

	// Work counterclockwise
	m_vertices.push_back(vertexTopRight);
	m_vertices.push_back(vertexTopLeft);
	m_vertices.push_back(vertexBottomLeft);
	
	m_vertices.push_back(vertexBottomLeft);
	m_vertices.push_back(vertexBottomRight);
	m_vertices.push_back(vertexTopRight);
	
	//glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

	// Count the attributes
	int attributeCount = 2;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(1 * sizeof(glm::vec3)));

	glBindVertexArray(0);
}

void MyMesh::InitCircle(float subDivisions)
{
	glBindVertexArray(m_uVAO);

	// Consists of 3 vertices

	float circleRadius = 1.0f;
	float theta = PI * 2 / (subDivisions < 3 ? 3 : subDivisions);

	// Vertex 1 (Center)
	vertex center;
	center.position = glm::vec3(0.0f, 0.0f, 0.0f);
	center.color = glm::vec3(1.0f, 0.0f, 0.0f);

	// Vertex 2
	vertex prev;
	prev.position = glm::vec3(m_scale * cos(0), m_scale * sin(0), 0.0f);
	prev.color = glm::vec3(0.0f, 1.0f, 0.0f);

	vertex first = prev;

	for (int i = 1; i <= subDivisions; i++) {

		// Next vertex
		vertex next;
		if (i == subDivisions) {
			next = first;
		}
		else {
			next.position = glm::vec3(m_scale * cos(theta * i), m_scale * sin(theta * i), 0.0f);
			next.color = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		m_vertices.push_back(center);
		m_vertices.push_back(prev);
		m_vertices.push_back(next);

		prev = next;
	}

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

	// Count the attributes
	int attributeCount = 2;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(1 * sizeof(glm::vec3)));

	glBindVertexArray(0);
}

void MyMesh::InitCube()
{
	glBindVertexArray(m_uVAO);

	// Consists of 3 vertices

	float quadSize = 0.5f;

	// Vertex 1 (Top Left Front)
	vertex vertexTopLeftFront;
	vertexTopLeftFront.position = glm::vec3(-quadSize, quadSize, 0.0f);
	vertexTopLeftFront.color = glm::vec3(1.0f, 0.0f, 0.0f);

	// Vertex 2 (Top Right Front)
	vertex vertexTopRightFront;
	vertexTopRightFront.position = glm::vec3(quadSize, quadSize, 0.0f);
	vertexTopRightFront.color = glm::vec3(0.0f, 1.0f, 0.0f);

	// Vertex 3 (Bottom Left Front)
	vertex vertexBottomLeftFront;
	vertexBottomLeftFront.position = glm::vec3(-quadSize, -quadSize, 0.0f);
	vertexBottomLeftFront.color = glm::vec3(0.0f, 0.0f, 1.0f);

	// Vertex 4 (Bottom Right Front)
	vertex vertexBottomRightFront;
	vertexBottomRightFront.position = glm::vec3(quadSize, -quadSize, 0.0f);
	vertexBottomRightFront.color = glm::vec3(1.0f, 0.0f, 1.0f);

	// Vertex 5 (Top Left Back)
	vertex vertexTopLeftBack;
	vertexTopLeftBack.position = glm::vec3(-quadSize, quadSize, 0.0f);
	vertexTopLeftBack.color = glm::vec3(1.0f, 0.0f, 0.0f);

	// Vertex 6 (Top Right Back)
	vertex vertexTopRightBack;
	vertexTopRightBack.position = glm::vec3(quadSize, quadSize, 0.0f);
	vertexTopRightBack.color = glm::vec3(0.0f, 1.0f, 0.0f);

	// Vertex 7 (Bottom Left Back)
	vertex vertexBottomLeftBack;
	vertexBottomLeftBack.position = glm::vec3(-quadSize, -quadSize, 0.0f);
	vertexBottomLeftBack.color = glm::vec3(0.0f, 0.0f, 1.0f);

	// Vertex 8 (Bottom Right Back)
	vertex vertexBottomRightBack;
	vertexBottomRightBack.position = glm::vec3(quadSize, -quadSize, 0.0f);
	vertexBottomRightBack.color = glm::vec3(1.0f, 0.0f, 1.0f);

	// Work counterclockwise
	// Front Face
	m_vertices.push_back(vertexTopRightFront);
	m_vertices.push_back(vertexTopLeftFront);
	m_vertices.push_back(vertexBottomLeftFront);

	m_vertices.push_back(vertexBottomLeftFront);
	m_vertices.push_back(vertexBottomRightFront);
	m_vertices.push_back(vertexTopRightFront);

	// Back Face
	m_vertices.push_back(vertexTopRightFront);
	m_vertices.push_back(vertexTopLeftFront);
	m_vertices.push_back(vertexBottomLeftFront);

	m_vertices.push_back(vertexBottomLeftFront);
	m_vertices.push_back(vertexBottomRightFront);
	m_vertices.push_back(vertexTopRightFront);

	//glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

	// Count the attributes
	int attributeCount = 2;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(1 * sizeof(glm::vec3)));

	glBindVertexArray(0);
}

void MyMesh::Draw()
{
	glBindVertexArray(m_uVAO);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	glBindVertexArray(0);
}

void MyMesh::SetScale(float size) 
{
	m_scale = size;
}

MyMesh* MyMesh::MakeTriangle(float size)
{
	MyMesh* pMesh = nullptr;

	pMesh = new MyMesh;
	pMesh->Init();

	// Set up triangle here
	pMesh->InitTriangle();

	pMesh->SetScale(size);

	return pMesh;
}

MyMesh* MyMesh::MakeQuad(float size)
{
	MyMesh* pMesh = nullptr;

	pMesh = new MyMesh;
	pMesh->Init();

	// Set up quad here
	pMesh->InitQuad();

	return pMesh;
}

MyMesh* MyMesh::MakeCircle(float radius, float subDivs)
{
	MyMesh* pMesh = nullptr;

	pMesh = new MyMesh;
	pMesh->Init();

	// Set up circle here
	pMesh->InitCircle(subDivs);

	return pMesh;
}

MyMesh* MyMesh::MakeCube(float size)
{
	MyMesh* pMesh = nullptr;

	pMesh = new MyMesh;
	pMesh->Init();

	// Set up circle here
	pMesh->InitCube();

	return pMesh;
}

MyMesh* MyMesh::Make(MyMesh::type meshType, float size, float subDivs)
{
	MyMesh* pMesh = nullptr;

	switch (meshType) {
		case MyMesh::type::TRIANGLE:
			pMesh = MyMesh::MakeTriangle(size);
			break;
		case MyMesh::type::QUAD:
			pMesh = MyMesh::MakeQuad(size);
			break;
		case MyMesh::type::CIRCLE:
			pMesh = MyMesh::MakeCircle(size, subDivs);
			break;
		case MyMesh::type::CUBE:
			pMesh = MyMesh::MakeCube(size);
			break;
		case MyMesh::type::INVALID:
			pMesh = nullptr;
			// Error
			break;
		default:
			break;
	}

	return pMesh;
}