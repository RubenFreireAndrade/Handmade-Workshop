#pragma once

/*===================================================================#
| 'FPSCamera' source files last updated on 19 May 2021               |
#===================================================================*/

#include <string>
#include "glad.h"
#include <glm.hpp>
#include "Camera.h"

//TODO - Refine class such that it follows newer design

class FPSCamera : public Camera
{

public:

	FPSCamera();
	virtual ~FPSCamera() {}

	bool IsFlying();
	void IsFlying(bool isFlying);

	void SetSensitivity(GLfloat sensitivity);
	void SetTarget(GLfloat x, GLfloat y, GLfloat z);

	virtual bool Create() { return true; }
	virtual void Update(int deltaTime);
	virtual void Destroy() {};

private:

	void RotateTrig();
	void RotateMatrix();

	bool m_isFlying;

	GLfloat m_yaw;
	GLfloat m_pitch;
	GLfloat m_sensitivity;

	glm::vec3 m_lookAt;
	glm::vec3 m_target;
	glm::mat4 m_rotationMatrixX;
	glm::mat4 m_rotationMatrixY;

};