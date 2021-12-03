#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<random>
#include<vector>
#include<utility>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include"filetobuf.h"
#include"ShaderFunc.h"
#include"Camera.h"
#include"Player.h"
#include"Light.h"
#include"Projection.h"
#include"Bullet.h"//weapon
#include"Pistol.h"//Gun
#include"Rifle.h"
#include"Sniper.h"
#include"Enum.h"
#include"Map.h"//map
#include"stair.h"
#include"Wall.h"
#include"Enemy.h"
#include"FlyRobot.h"
#include"GameSound.h"
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

//texture load Func
void loadITextureImage();

//bullet queue render
//render func
void renderObjs();

//cross header
void initBuffer();
void drawPoint();

GLuint dotVao;
GLuint dotVbo;
GLuint dotNormalVbo;

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
Pistol* pistol = new Pistol(Camera::getInst(glm::vec3(0, 1.0f, 9.0f))->getPos());
Rifle* rifle = new Rifle(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
Sniper* sniper = new Sniper(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
Gun* myGun = pistol;

//Bullet
Bullet bullets;

//Map
Map* map = new Map;
Stair* stair = new Stair;
Wall* wall = new Wall;

//Enemy
Enemy* enemy = new Enemy;
Flyrobot* flyrobot = new Flyrobot;

//sound
GameSound sounds;
Flyrobot* flyrobotbody = new Flyrobot;
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


	/*int num;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS ,&num);
	cout << num;*/

	shaderfunc.makeVertexShader();
	shaderfunc.makeFragmentShader();
	shaderfunc.makeShaderID();
	initBuffer();

	defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());

	loadITextureImage();
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), 0);

	pistol->bindingGun(shaderfunc);
	rifle->bindingGun(shaderfunc);
	sniper->bindingGun(shaderfunc);
	map->bindingMap(shaderfunc);
	stair->bindingMap(shaderfunc);
	wall->bindingMap(shaderfunc);
	bullets.bindingBullet(shaderfunc);
	enemy->bindingEnemy(shaderfunc);
	flyrobotbody->bindingEnemy(shaderfunc);

	//display
	glutDisplayFunc(DrawSceneCall);
	glutReshapeFunc(ReshapeCall);
	//key
	glutKeyboardFunc(keyboardCall);
	glutSpecialFunc(specialkeycall);
	//mouse
	glutPassiveMotionFunc(motionCall);
	glutMotionFunc(motionCall);
	glutMouseFunc(mouseCall);

	//glutIdleFunc(IdleCall);

	glutSetCursor(GLUT_CURSOR_NONE);

	glutTimerFunc(10, timercall, (int)MOUSE);
	glutTimerFunc(10, timercall, (int)GUNMOTION);
	glutTimerFunc(10, timercall, (int)GUN);
	glutTimerFunc(17, timercall, (int)BULLET);
	glutTimerFunc(1000, timercall, (int)WALK);
	sounds.backGroundMusic();
	glutMainLoop();
	//Camera::destoy();
}

void timercall(int value)
{
	switch (value)
	{
	case MOUSE:
		xAxis = ((float)preMouse.first - (float)curreuntMouse.first) * 0.5f;
		yAxis = ((float)preMouse.second - (float)curreuntMouse.second) * 0.5f;
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
		Camera::getInst(glm::vec3(0, 0, 0))->attackMotion(0.0f);
		pistol->setStatusAttack(false);
		rifle->setStatusAttack(false);
		sniper->setStatusAttack(false);
		Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(false, myGun->getRecoil());
		glutPostRedisplay();
		glutTimerFunc(10, timercall, value);
		break;
	case GUNMOTION:
		if (isClick && myGun->getRecoil() <= 1.2f) {
			bullets.addBullet(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), myGun->getAngles());
			rifle->setStatusAttack(true);
			Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(true, myGun->getRecoil());
			sounds.shootingSound();				
		}
		glutPostRedisplay();
		glutTimerFunc(100, timercall, value);
		break;
	case BULLET:
		bullets.moveBullets();
		glutPostRedisplay();
		glutTimerFunc(17, timercall, value);
		break;
	case WALK:
		sounds.pauseWalking();
		sounds.pauseRunning();
		glutTimerFunc(1000, timercall, value);
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

	drawPoint();

	defaultLight.renderLight(shaderfunc);
	Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->renderCamera(shaderfunc);
	perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight);

	renderObjs();



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
	int mod = 0;
	switch (key)
	{
	case'1':
		myGun = dynamic_cast<Pistol*> (pistol);
		myGun->initRecoilRotate();
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->initRecoilRotate();
		sounds.pauseWalking();
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
	case'W':
		 mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT) {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->runFrontCamera();
			sounds.runningSound();
		}
		else {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveFrontCamera();
		sounds.walkingSound();
		}
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case's':
	case'S':
		 mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT) {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->runBackCamera();
			sounds.runningSound();
		}
		else {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveBackCamera();
			sounds.walkingSound();
		}
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case'a':
	case'A':
		 mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT) { 
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->runLeftCamera(); 
			sounds.runningSound();
		}
		else {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveLeftCamera();
			sounds.walkingSound();
		}
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		break;
	case'd':
	case'D':
		 mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_SHIFT) {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->runRightCamera();
			sounds.runningSound();
		}
		else {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRightCamera();
			sounds.walkingSound();
		}
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
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
	case GLUT_KEY_END:
		sounds.~GameSound();
		glutLeaveMainLoop();
		break;
	case GLUT_KEY_LEFT:
		break;
	default:
		break;
	}
}

void mouseCall(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		bullets.addBullet(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), myGun->getAngles());
		pistol->setStatusAttack(true);
		sniper->setStatusAttack(true);
		rifle->setStatusAttack(true);
		Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(true, myGun->getRecoil());
		sounds.shootingSound();
		isClick = true;
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
	unsigned char* pistolData = stbi_load("texture_pistol_2.jpg", &pistolwidthImage, &pistolheightImage, &pistolnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pistolwidthImage, pistolheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, pistolData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pistolData);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int riflewidthImage, rifleheightImage, riflenumberOfChannel;
	unsigned char* rifleData = stbi_load("texture_rifle.jpg", &riflewidthImage, &rifleheightImage, &riflenumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, riflewidthImage, rifleheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, rifleData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(rifleData);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int sniperwidthImage, sniperheightImage, snipernumberOfChannel;
	unsigned char* sniperData = stbi_load("texture_sniper.jpg", &sniperwidthImage, &sniperheightImage, &snipernumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sniperwidthImage, sniperheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, sniperData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(sniperData);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int bulletwidthImage, bulletheightImage, bulletnumberOfChannel;
	unsigned char* bulletData = stbi_load("texture_bullet.jpg", &bulletwidthImage, &bulletheightImage, &bulletnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bulletwidthImage, bulletheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, bulletData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bulletData);
	//FlyRobot Texture
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int FlyrobotwidthImage, FlyrobotheightImage, FlyrobotnumberOfChannel;
	unsigned char* FlyrobotData = stbi_load("texture_Flyrobot.jpg", &FlyrobotwidthImage, &FlyrobotheightImage, &FlyrobotnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FlyrobotwidthImage, FlyrobotheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, FlyrobotData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(FlyrobotData);
}

void renderObjs()
{
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), 0);
	map->renderMap(shaderfunc);
	stair->renderMap(shaderfunc);
	wall->renderMap(shaderfunc);

	myGun->renderGun(shaderfunc);
	bullets.renderBullets(shaderfunc);

	//enemy
	enemy->renderEnemy(shaderfunc);
	flyrobotbody->renderEnemy(shaderfunc);
}

void initBuffer()
{
	glm::vec3 poitDot = glm::vec3(0, 0, -0.5);
	glm::vec3 normalDot = glm::vec3(0, 0, 1);
	glUseProgram(shaderfunc.getShaderID());
	glGenVertexArrays(1, &dotVao);
	glBindVertexArray(dotVao);
	glGenBuffers(1, &dotVbo);
	glBindBuffer(GL_ARRAY_BUFFER, dotVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &poitDot, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &dotNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, dotNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &normalDot, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
}

void drawPoint()
{
	glm::mat4 dotM = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderfunc.getShaderID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniformMatrix4fv(glGetUniformLocation(shaderfunc.getShaderID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniformMatrix4fv(glGetUniformLocation(shaderfunc.getShaderID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), -1);
	glUniform3f(glGetUniformLocation(shaderfunc.getShaderID(), "objColor"), 1, 0, 0);
	glBindVertexArray(dotVao);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(7.0f);
	glDrawArrays(GL_POINTS, 0, 1);
}
