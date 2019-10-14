#ifndef MY_MESH_H_
#define MY_MESH_H_

#include "Definitions.h"
#include <vector>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>
#include <GL\glew.h>

struct vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class MyMesh {
public:
	typedef enum class TYPES {
		TRIANGLE,
		QUAD,
		CIRCLE,
		CUBE,
		INVALID
	} type;
public:
	MyMesh();
	~MyMesh();

	void Init();
	void InitShader();
	void InitTriangle();
	void InitQuad();
	void InitCircle(float subDivisions);
	void InitCube();

	void Draw();
	void SetScale(float size);

private:
	static MyMesh* MakeTriangle(float size);
	static MyMesh* MakeQuad(float size);
	static MyMesh* MakeCircle(float radius, float subDivisions = 6);
	static MyMesh* MakeCube(float size);

public:
	static MyMesh* Make(MyMesh::type meshType, float size, float subDivs = 6);
	

private:
	std::vector<vertex> m_vertices;
	GLuint m_uShaderProgramID = 0;
	GLuint m_uVAO = 0;
	GLuint m_uVBO = 0;

	float m_scale = 1.0f;
};

#endif // ! MY_MESH_H_