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
#include"readQuadObj.h"//юс╫ц
#include"ShaderFunc.h"
#include"Camera.h"
#include"Player.h"
#include"Light.h"
#include"Projection.h"
#include"Pistol.h"//Gun
#include"Rifle.h"
#include"Sniper.h"
#include"Enum.h"
#include"Map.h"
#include"stair.h"
#include"Wall.h"

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


//Camera camera(glm::vec3(0, 1.0f, 3.0f));

//weapon

Pistol* pistol = new Pistol(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos()+ glm::vec3(0.05f, -0.2f, -0.2f));
Rifle* rifle = new Rifle(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos() + glm::vec3(0.1f, -0.3f, -0.2f));
Sniper* sniper = new Sniper(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos() + glm::vec3(0.02f, -0.5f, -0.4f));
Gun* myGun = pistol;
Map* map = new Map;
Stair* stair = new Stair;
Wall* wall = new Wall;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("FPS");
	glutFullScreen();
	
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
	map->bindingMap(shaderfunc);
	stair->bindingMap(shaderfunc);
	wall->bindingMap(shaderfunc);
		

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
	Camera::destoy();
}

void timercall(int value)
{
	switch (value)
	{
	case TIMER:
		xAxis = ((float)preMouse.first - (float)curreuntMouse.first)  * 0.7f;
		yAxis = ((float)preMouse.second - (float)curreuntMouse.second) * 0.7f;
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateY(xAxis);
		pistol->moveRevoluY(xAxis);
		rifle->moveRevoluY(xAxis);
		sniper->moveRevoluY(xAxis);
		if (Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis <=60.0f && Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis >= -60.0f) {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateX(yAxis);
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
	Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->renderCamera(shaderfunc);
	perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight);

	myGun->renderGun(shaderfunc);
	map->renderMap(shaderfunc);
	stair->renderMap(shaderfunc);
	wall->renderMap(shaderfunc);

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
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveFrontCamera();
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case's':
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveBackCamera();
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case'a':
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveLeftCamera();
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case'd':
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRightCamera();
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case'q':
		glutLeaveMainLoop();
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
