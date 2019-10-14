#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	m_pMesh->GenerateCone(1.5f, 3.0f, 6, C_RED);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	// timer
	//static uint uClock = m_pSystem->GenClock();
	//float fTimer = m_pSystem->GetTimeSinceStart(uClock);

	// calc cur position
	//static float theta = 0.0f;
	//theta += 0.06f;

	//matrix4 m4Rotation = glm::rotate(IDENTITY_M4, theta, vector3(0.0f, 0.0f, 1.0f));
	//matrix4 m4Rotation = glm::rotate(IDENTITY_M4, glm::radians(fTimer * 60.0f), vector3(0.0f, 0.0f, 1.0f));

	//for (uint i = 0; i < 2500; ++i)
		//m4Model = m4Rotation * glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 0.0f)) * glm::transpose(m4Rotation);

	matrix4 m4Model;

	matrix4 m4OrientX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.x), vector3(1.0f, 0.0f, 0.0f));
	matrix4 m4OrientY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.y), vector3(0.0f, 1.0f, 0.0f));
	matrix4 m4OrientZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.z), vector3(0.0f, 0.0f, 1.0f));

	matrix4 m4Orientation = m4OrientX * m4OrientY * m4OrientZ;

	m4Model = m4Orientation;

	//m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_m4Model));
	//m_qOrientation = m_qOrientation * glm::angleAxis(glm::radians(1.0f), vector3(1.0f));
	
	m_pMesh->Render(m4Projection, m4View, m4Model);
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}