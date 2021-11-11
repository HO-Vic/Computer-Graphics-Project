#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<random>
#include<vector>
#include"filetobuf.h"
#include"readObj.h"
#include"Camera.h"
#include"ShaderFunc.h"
#include"Player.h"

using namespace std;

//call_back
void timercall(int value);
void DrawSceneCall();
void ReshapeCall(int w, int h);
void keyboardCall(unsigned char key, int x, int y);
void specialkeycall(int key, int x, int y);


int Wwidth = 800;
int Wheight = 600;

ShaderFunc shaderfunc;
Camera camera;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("FPS");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;


	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(ReshapeCall);
	glutKeyboardFunc(keyboardCall);
	glutSpecialFunc(specialkeycall);
	glutTimerFunc(1, timercall, 1);
	glutMainLoop();
}

void timercall(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, timercall, value);
}


void DrawSceneCall()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//카메라
	
	glm::mat4 cameraView = camera.getCameraViewMatrix(glm::vec3 AT);//오브젝트 위치 인자로 넣어야 됨
	unsigned int cameraViewLocation = glGetUniformLocation(shaderfunc.getShaderID(), "viewTransform");
	glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(cameraView));
	//카메라#
	//투영
	//원근 투영
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::translate(projection, glm::vec3(0, 0, -5.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)Wwidth / (float)Wheight, 0.1f, 50.0f);
	unsigned int projectionLocation = glGetUniformLocation(shaderfunc.getShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glutSwapBuffers();
}

void ReshapeCall(int w, int h)
{
	glViewport(0, 0, w, h);
	Wwidth = w;
	Wheight = h;
}

void keyboardCall(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'a':
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void specialkeycall(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	default:
		break;
	}
}


