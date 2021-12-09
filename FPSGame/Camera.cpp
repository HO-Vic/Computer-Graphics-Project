#include "Camera.h"

Camera* Camera::cameraInst = NULL;

void Camera::setCameraDir()
{	
	glm::vec3 tempCameraDir = pos - AT;//n
	glm::mat4 rotateMat = glm::mat4(1.0f);
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.x + attackRotateX), glm::vec3(1, 0, 0));
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	cameraDir = glm::vec3(rotateMat * glm::vec4(-tempCameraDir, 1));

}

void Camera::attackMotion(float recoil)
{
	if (attackRotateX >= recoil)
		attackRotateX -= 0.1f;
}

void Camera::setStatusAttack(bool f, float recoil)
{
	isAttack = f;
	if(isAttack)
		attackRotateX += recoil;
}

Camera* Camera::getInst(glm::vec3 pos)
{
	if (cameraInst == NULL) 
		setInst(pos);
	return cameraInst;
}

void Camera::destoy()
{
	if(cameraInst)
		delete cameraInst;
}

void Camera::setInst(glm::vec3 pos)
{
	cameraInst = new Camera(pos);
}

void Camera::setCameraRight()
{
	cameraRight= glm::normalize(glm::cross(up, glm::normalize(-cameraDir)));//v
}

void Camera::setCameraUp()
{
	cameraUp = glm::cross(glm::normalize(-cameraDir), cameraRight);
}

void Camera::renderCamera(ShaderFunc&  ShaderID)
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	glm::mat4 cameraView = glm::mat4(1.0f);
	cameraView = glm::lookAt(pos, cameraDir + pos, cameraUp);
	unsigned int cameraViewLocation = glGetUniformLocation(ShaderID.getShaderID(), "viewTransform");
	glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(cameraView));
	unsigned int cameraPosLocation = glGetUniformLocation(ShaderID.getShaderID(), "cameraPos");
}

void Camera::moveFrontCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += walkRatio * glm::vec3(glm::normalize(cameraDir).x, 0, glm::normalize(cameraDir).z);
	AT.x += walkRatio * glm::normalize(cameraDir).x;
	AT.z += walkRatio * glm::normalize(cameraDir).z;
	//std::cout << "x ÁÂÇ¥" << getPos().x << "y ÁÂÇ¥" << getPos().y << "z ÁÂÇ¥" << getPos().z<<std::endl;
}

void Camera::moveBackCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= walkRatio * glm::vec3(glm::normalize(cameraDir).x, 0, glm::normalize(cameraDir).z);
	AT.x -= walkRatio * glm::normalize(cameraDir).x;
	AT.z -= walkRatio * glm::normalize(cameraDir).z;
}

void Camera::moveLeftCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= walkRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT.x -= walkRatio * cameraRight.x;
	AT.z -= walkRatio * cameraRight.z;
}

void Camera::moveRightCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += walkRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT.x += walkRatio * cameraRight.x;
	AT.z += walkRatio * cameraRight.z;
}

void Camera::moveUpCamera(float y)
{
	pos.y = y;
	AT.y = y-0.9f;
}

void Camera::runFrontCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += runRatio * glm::vec3(glm::normalize(cameraDir).x, 0, glm::normalize(cameraDir).z);
	AT.x += runRatio * glm::normalize(cameraDir).x;
	AT.z += runRatio * glm::normalize(cameraDir).z;
}

void Camera::runBackCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= runRatio * glm::vec3(glm::normalize(cameraDir).x, 0, glm::normalize(cameraDir).z);
	AT.x -= runRatio * glm::normalize(cameraDir).x;
	AT.z -= runRatio * glm::normalize(cameraDir).z;
}

void Camera::runLeftCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= runRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT.x -= runRatio * cameraRight.x;
	AT.z -= runRatio * cameraRight.z;
}

void Camera::runRightCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += runRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT.x += runRatio * cameraRight.x;
	AT.z += runRatio * cameraRight.z;
}

void Camera::moveRoateY(float Angle)
{
	rotateAngle.y += Angle;
}

void Camera::moveRoateX(float Angle)
{
	rotateAngle.x += Angle;
}

void Camera::setCameraAngleY(float Angle)
{
	rotateAngle.y = Angle;
}

void Camera::setCameraAngleX(float Angle)
{
	rotateAngle.x = Angle;
}

void Camera::setCameraAngleZ(float Angle)
{
	rotateAngle.z = Angle;
}

void Camera::initRecoilRotate()
{
	attackRotateX = 0.0f;
}

glm::vec3 Camera::getPos()
{
	return pos;
}

float Camera::getRotateX()
{
	return rotateAngle.x;
}

glm::vec3 Camera::getDir()
{
	setCameraDir();
	return glm::normalize(cameraDir);
}

glm::vec3 Camera::getRight()
{
	return glm::vec3(cameraRight);
}

glm::vec3 Camera::getUp()
{
	return glm::vec3(cameraUp);
}
