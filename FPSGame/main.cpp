#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<random>
#include<vector>
#include"filetobuf.h"
#include"readQuadObj.h"//임시
#include"ShaderFunc.h"
#include"Camera.h"
#include"Player.h"
#include"Light.h"
#include"Projection.h"

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
Light defaultLight;
Projection perspective;

GLuint shaderID;

//임시
GLuint planeVao;
GLuint planeVertexVbo;
GLuint planeNormalVbo;
vector<glm::vec3> planeVertexData;
vector<glm::vec3> planeNormalData;
void InitBuffer();
void drawPlane();

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

	shaderfunc.makeVertexShader();
	shaderfunc.makeFragmentShader();
	shaderfunc.makeShaderID();


	//임시
	InitBuffer();


	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(ReshapeCall);
	//glutKeyboardFunc(keyboardCall);
	//glutSpecialFunc(specialkeycall);
	//glutTimerFunc(1, timercall, 1);
	glutMainLoop();
}

void timercall(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, timercall, value);
}


void DrawSceneCall()
{
	glClearColor(0,0,0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	defaultLight.renderLight(shaderfunc);
	camera.renderCamera(shaderfunc, glm::vec3(0, 0, 0));
	perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight);


	//임시
	drawPlane();


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

//임시
void InitBuffer()
{
	readQuadsObj("obj_plane.obj", planeVertexData, planeNormalData);
	glGenVertexArrays(1, &planeVao);
	glBindVertexArray(planeVao);
	glGenBuffers(1, &planeVertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, planeVertexVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * planeVertexData.size(), &planeVertexData[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &planeNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, planeNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * planeNormalData.size(), &planeNormalData[0], GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
}

//임시
void drawPlane()
{
	glm::mat4 planeMatrix = glm::mat4(1.0f);
	unsigned int planeMatrixLocation = glGetUniformLocation(shaderfunc.getShaderID(), "modelTransform");
	glUniformMatrix4fv(planeMatrixLocation, 1, GL_FALSE, glm::value_ptr(planeMatrix));
	glm::mat4 planeNormalMatrix = glm::mat4(1.0f);
	unsigned int planeNormalLocation = glGetUniformLocation(shaderfunc.getShaderID(), "normalTransform");
	glUniformMatrix4fv(planeNormalLocation, 1, GL_FALSE, glm::value_ptr(planeNormalMatrix));
	glBindVertexArray(planeVao);
	glm::vec3 planeColor = glm::vec3(1, 0, 0);
	unsigned int planeColorLocation = glGetUniformLocation(shaderfunc.getShaderID(), "objColor");
	glUniform3fv(planeColorLocation, 1, glm::value_ptr(planeColor));
	glDrawArrays(GL_QUADS, 0, planeVertexData.size());
}


