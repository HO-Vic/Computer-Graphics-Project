#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<random>
#include<vector>
#include<utility>
#include"filetobuf.h"
#include"readQuadObj.h"//임시
#include"ShaderFunc.h"
#include"Camera.h"
#include"Player.h"
#include"Light.h"
#include"Projection.h"
#include"Pistol.h"//Gun
#include"Rifle.h"
#include"Sniper.h"
#include"Enum.h"

using namespace std;

//call_back
void timercall(int value);
void DrawSceneCall();
void ReshapeCall(int w, int h);
void keyboardCall(unsigned char key, int x, int y);
void specialkeycall(int key, int x, int y);
void mouseCall(int button, int state, int x, int y);
void motionCall(int x, int y);
void IdleCall();

int Wwidth = 800;
int Wheight = 600;

ShaderFunc shaderfunc;
Light defaultLight;
Projection perspective;

pair<int, int> curreuntMouse = { Wwidth / 2 , Wheight / 2 };
pair<int, int> preMouse = { Wwidth / 2 , Wheight / 2 };
float xAxis = 0.0f;
float yAxis = 0.0f;


Camera camera(glm::vec3(0, 1.0f, 3.0f));

//weapon
Pistol* pistol = new Pistol(camera.getPos()+ glm::vec3(0.05f, -0.2f, -0.2f));
Rifle* rifle = new Rifle(camera.getPos() + glm::vec3(0.1f, -0.3f, -0.2f));
Sniper* sniper = new Sniper(camera.getPos() + glm::vec3(0.02f, -0.5f, -0.4f));
Gun* myGun = pistol;

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
	glutFullScreen();
	
	
	/*glutGameModeString("1920x1080:32@60");
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		glutEnterGameMode();*/
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cerr << "fail Initialize" << endl;
	else cout << "Initialize" << endl;

	shaderfunc.makeVertexShader();	
	shaderfunc.makeFragmentShader();
	shaderfunc.makeShaderID();
	pistol->bindingGun(shaderfunc);
	rifle->bindingGun(shaderfunc);
	sniper->bindingGun(shaderfunc);
	
	//임시
	InitBuffer();
	

	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(ReshapeCall);
	glutKeyboardFunc(keyboardCall);
	glutSpecialFunc(specialkeycall);
	glutPassiveMotionFunc(motionCall);
	glutMotionFunc(motionCall);
	glutIdleFunc(IdleCall);
	glutMouseFunc(mouseCall);
	
	//glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glutTimerFunc(10, timercall, (int)TIMER);
	glutMainLoop();
}

void timercall(int value)
{
	switch (value)
	{
	case TIMER:
		xAxis = ((float)preMouse.first - (float)curreuntMouse.first)  * 0.7f;
		yAxis = ((float)preMouse.second - (float)curreuntMouse.second) * 0.7f;
		camera.moveRoateY(xAxis);
		pistol->moveRevoluY(xAxis);
		rifle->moveRevoluY(xAxis);
		sniper->moveRevoluY(xAxis);
		if (camera.getRotateX() + yAxis <=60.0f && camera.getRotateX() + yAxis >= -60.0f) {
			camera.moveRoateX(yAxis);
			pistol->moveRevoluX(yAxis);
			rifle->moveRevoluX(yAxis);
			sniper->moveRevoluX(yAxis);
		}
		if(curreuntMouse.first >= 4 * Wwidth / 5)
			glutWarpPointer(1 * Wwidth / 5, curreuntMouse.second);
		if (curreuntMouse.first <= 1 * Wwidth / 5)
			glutWarpPointer(4 * Wwidth / 5, curreuntMouse.second);
		if (curreuntMouse.second >= 4 * Wheight / 5)
			glutWarpPointer(curreuntMouse.first, Wheight / 5);
		if (curreuntMouse.second <= 1 * Wheight / 5)
			glutWarpPointer(curreuntMouse.first, 4 * Wheight / 5);
		preMouse = curreuntMouse;
		glutPostRedisplay();
		glutTimerFunc(10, timercall, value);
		break;
	default:
		break;
	}
}


void DrawSceneCall()
{
	glClearColor(1,1,1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	defaultLight.renderLight(shaderfunc);
	camera.renderCamera(shaderfunc);
	perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight);

	//pistol->renderGun(shaderfunc);
	myGun->renderGun(shaderfunc);
	//임시
	drawPlane();


	glutSwapBuffers();
}

void ReshapeCall(int w, int h)
{
	glViewport(0, 0, w, h);
	Wwidth = w;
	Wheight = h;
	curreuntMouse = { Wwidth / 2 , Wheight / 2 };
	preMouse = { Wwidth / 2 , Wheight / 2 };
}

void keyboardCall(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'1':
		myGun = dynamic_cast<Pistol*> (pistol);
		break;
	case'2':
		myGun = dynamic_cast<Rifle*> (rifle);
		break;
	case'3':
		myGun = dynamic_cast<Sniper*> (sniper);
		break;
	case'w':
		camera.moveFrontCamera();
		pistol->setPos(camera.getPos());
		rifle->setPos(camera.getPos());
		sniper->setPos(camera.getPos());
		break;
	case's':
		camera.moveBackCamera();
		pistol->setPos(camera.getPos());
		rifle->setPos(camera.getPos());
		sniper->setPos(camera.getPos());
		break;
	case'a':
		camera.moveLeftCamera();
		pistol->setPos(camera.getPos());
		rifle->setPos(camera.getPos());
		sniper->setPos(camera.getPos());
		break;
	case'd':
		camera.moveRightCamera();
		pistol->setPos(camera.getPos());
		rifle->setPos(camera.getPos());
		sniper->setPos(camera.getPos());
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

void mouseCall(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {


	}
	glutPostRedisplay();
}
 
void motionCall(int x, int y)
{
	preMouse = curreuntMouse;
	curreuntMouse = pair<int, int>(x, y);
	glutPostRedisplay();
}

void IdleCall()
{
	glutPostRedisplay();
}

//임시
void InitBuffer()
{
	readQuadObj("obj_plane.obj", planeVertexData, planeNormalData);
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
	planeMatrix = glm::scale(planeMatrix, glm::vec3(20, 20, 20));
	unsigned int planeMatrixLocation = glGetUniformLocation(shaderfunc.getShaderID(), "modelTransform");
	glUniformMatrix4fv(planeMatrixLocation, 1, GL_FALSE, glm::value_ptr(planeMatrix));
	glm::mat4 planeNormalMatrix = glm::mat4(1.0f);
	unsigned int planeNormalLocation = glGetUniformLocation(shaderfunc.getShaderID(), "normalTransform");
	glUniformMatrix4fv(planeNormalLocation, 1, GL_FALSE, glm::value_ptr(planeNormalMatrix));
	glBindVertexArray(planeVao);
	glm::vec3 planeColor = glm::vec3(0, 0.5, 0);
	unsigned int planeColorLocation = glGetUniformLocation(shaderfunc.getShaderID(), "objColor");
	glUniform3fv(planeColorLocation, 1, glm::value_ptr(planeColor));
	glDrawArrays(GL_QUADS, 0, planeVertexData.size());
}


