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
#include"ShaderFunc.h"
#include"Camera.h"
#include"Player.h"
#include"Light.h"
#include"Projection.h"
#include"Pistol.h"//Gun
#include"Rifle.h"
#include"Sniper.h"
#include"Enum.h"
#include"Map.h"//map
#include"stair.h"
#include"Wall.h"
//#include"LoadImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

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


void loadITextureImage();
int Wwidth = 800;
int Wheight = 600;

ShaderFunc shaderfunc;
Light defaultLight;
Projection perspective;

pair<int, int> curreuntMouse = { Wwidth / 2 , Wheight / 2 };
pair<int, int> preMouse = { Wwidth / 2 , Wheight / 2 };
float xAxis = 0.0f;
float yAxis = 0.0f;

bool isClick = false;

//Camera camera(glm::vec3(0, 1.0f, 3.0f));

//weapon

Pistol* pistol = new Pistol(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos() + glm::vec3(0.05f, -0.2f, -0.2f));
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

	loadITextureImage();
	pistol->bindingGun(shaderfunc);
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), 0);

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

	glutTimerFunc(10, timercall, (int)MOUSE);
	glutTimerFunc(10, timercall, (int)GUNMOTION);
	glutTimerFunc(10, timercall, (int)GUN);
	glutMainLoop();
	Camera::destoy();
}

void timercall(int value)
{
	switch (value)
	{
	case MOUSE:
		xAxis = ((float)preMouse.first - (float)curreuntMouse.first) * 0.7f;
		yAxis = ((float)preMouse.second - (float)curreuntMouse.second) * 0.7f;
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateY(xAxis);
		pistol->moveRevoluY(xAxis);
		rifle->moveRevoluY(xAxis);
		sniper->moveRevoluY(xAxis);
		if (Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis <= 60.0f && Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis >= -60.0f) {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateX(yAxis);
			pistol->moveRevoluX(yAxis);
			rifle->moveRevoluX(yAxis);
			sniper->moveRevoluX(yAxis);
		}
		if (curreuntMouse.first >= 4 * Wwidth / 5)
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
	case GUN:		
		pistol->AttackMotion();
		rifle->AttackMotion();
		sniper->AttackMotion();
		Camera::getInst(glm::vec3(0,0,0))->attackMotion(0.0f);
		pistol->setStatusAttack(false);
		rifle->setStatusAttack(false);
		sniper->setStatusAttack(false);
		Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(false, myGun->getRecoil());
		glutPostRedisplay();
		glutTimerFunc(10, timercall, value);
		break;
	case GUNMOTION:
		if (isClick) {
			rifle->setStatusAttack(true);
			if(myGun->getRecoil() <= 0.6f)
				Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(true, myGun->getRecoil());
		}
		glutPostRedisplay();
		glutTimerFunc(100, timercall, value);
		break;
	default:
		break;
	}
}

void DrawSceneCall()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	defaultLight.renderLight(shaderfunc);
	Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->renderCamera(shaderfunc);
	perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight);
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), 0);

	map->renderMap(shaderfunc);
	stair->renderMap(shaderfunc);
	wall->renderMap(shaderfunc);
	myGun->renderGun(shaderfunc);

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
		myGun->initRecoilRotate();
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->initRecoilRotate();
		break;
	case'2':
		myGun = dynamic_cast<Rifle*> (rifle);
		myGun->initRecoilRotate();
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->initRecoilRotate();
		break;
	case'3':
		myGun = dynamic_cast<Sniper*> (sniper);
		myGun->initRecoilRotate();
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->initRecoilRotate();
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
		isClick = true;
		pistol->setStatusAttack(true);
		sniper->setStatusAttack(true);
		Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(true, myGun->getRecoil());
	}
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		isClick = false;
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

void loadITextureImage()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int pistolwidthImage, pistolheightImage, pistolnumberOfChannel;
	unsigned char* pistolData = stbi_load("texture_pistol.jpg", &pistolwidthImage, &pistolheightImage, &pistolnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pistolwidthImage, pistolheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, pistolData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pistolData);
}
