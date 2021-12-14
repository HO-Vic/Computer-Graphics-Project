#include"Headers.h"



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
void bindingObj();

//bullet queue render
//render func
void renderObjs();



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

//cross head
bool changeCrossHead = true;
CrossHead CR;
float mouseSpeed = 2.0f;

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

glm::vec3 FLpostion[20] = {};
glm::vec3 FLTrpostion[20] = {};
bool FLXCheck[20] = { 0 };
bool FLYCheck[20] = { 0 };
bool FLZCheck[20] = { 0 };

glm::vec3 Rpostion[20] = {};
glm::vec3 RTrpostion[20] = {};
FlyRobotManager flyManager;
RobotManager robotManager;
int Gundamge = 0;
bool isRenderChang = false;
bool isRenderRobot = true;
bool isRenderBoss = false;
glm::vec3 bossMove;
int robotSound = 0;

Boss boss;

//Boss

 


//sound
GameSound sounds;

//particle
ParticleManager particle;



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

	defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());

	loadITextureImage();
	glUniform1i(glGetUniformLocation(shaderfunc.getShaderID(), "isTexture"), 0);
	bindingObj();



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
	glutTimerFunc(10, timercall, (int)WALK);
	glutTimerFunc(17, timercall, (int)CRASH);
	glutTimerFunc(17, timercall, (int)PARTICLE);
	glutTimerFunc(17, timercall, (int)ROBOTPARTICLE);
	glutTimerFunc(10, timercall, (int)FlYROBOT);
	glutTimerFunc(10, timercall, (int)CNTROBOTS);
	glutTimerFunc(10, timercall, (int)BOSSMOVE);
	glutTimerFunc(10, timercall, (int)RESETROBOTMOVE);
	sounds.backGroundMusic();
	glutMainLoop();
}

void timercall(int value)
{
	int changDoongCnt = 0;
	int robotCnt = changDoongCnt;
	switch (value)
	{
	case MOUSE:
		if (changeCrossHead)
			mouseSpeed = 0.2f;
		else mouseSpeed = 0.05f;
		xAxis = ((float)preMouse.first - (float)curreuntMouse.first) * mouseSpeed;
		yAxis = ((float)preMouse.second - (float)curreuntMouse.second) * mouseSpeed;
		if (xAxis >= 70.0f) {}
		else {
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateY(xAxis);
			pistol->moveRevoluY(xAxis);
			rifle->moveRevoluY(xAxis);
			sniper->moveRevoluY(xAxis);
			if (Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis <= 80.0f && Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getRotateX() + yAxis >= -60.0f) {
				Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveRoateX(yAxis);
				pistol->moveRevoluX(yAxis);
				rifle->moveRevoluX(yAxis);
				sniper->moveRevoluX(yAxis);
			}
			if (curreuntMouse.first >= 4 * Wwidth / 5)
				glutWarpPointer(1 * Wwidth / 5 + 10, curreuntMouse.second);
			if (curreuntMouse.first <= 1 * Wwidth / 5)
				glutWarpPointer(4 * Wwidth / 5 - 10, curreuntMouse.second);
			if (curreuntMouse.second >= 4 * Wheight / 5)
				glutWarpPointer(curreuntMouse.first, Wheight / 5 + 10);
			if (curreuntMouse.second <= 1 * Wheight / 5)
				glutWarpPointer(curreuntMouse.first, 4 * Wheight / 5 - 10);
			preMouse = curreuntMouse;
		}
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
			particle.Makeparticle(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), Camera::getInst(glm::vec3(0, 0, 0))->getRight(), Camera::getInst(glm::vec3(0, 0, 0))->getUp());
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
		glutTimerFunc(1, timercall, value);
		break;
	case WALK:
		sounds.pauseWalking();
		sounds.pauseRunning();
		glutTimerFunc(1000, timercall, value);
		break;
	case CRASH:
		Crash(Camera::getInst(glm::vec3(0, 1, 3))->getPos());
		Crash2(Camera::getInst(glm::vec3(0, 1, 3))->getPos());
		Crash3(Camera::getInst(glm::vec3(0, 1, 3))->getPos());
		//std::cout << "x ÁÂÇ¥" << Camera::getInst(glm::vec3(0, 1, 3))->getPos().x << "y ÁÂÇ¥" << Camera::getInst(glm::vec3(0, 1, 3))->getPos().y << "z ÁÂÇ¥" << Camera::getInst(glm::vec3(0, 1, 3))->getPos().z << std::endl;
		myGun->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		pistol->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		rifle->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		sniper->setPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		defaultLight.setLightPos(Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->getPos());
		for (int i = 0; i < 20; i++) {
			if (bullets.collideBullet(flyManager.getFlyRobot()[i].get_Position(), 0.2, 0.3, 0.3) == 1) {
				if (flyManager.getFlyRobot()[i].Minushp(Gundamge)) {
					particle.flyRobotParticle(flyManager.getFlyRobot()[i].get_Position());
					flyManager.getFlyRobot()[i].Gotozero_Positon(0, -1000, 0);
				}
			}
		}
		for (int i = 0; i < 20; i++) {
			if (bullets.collideBullet(robotManager.getRobot()[i].get_Position(), 0.4, 0.5, 0.4) == 1) {
				if (robotManager.getRobot()[i].MinusHp(Gundamge)) {
					particle.flyRobotParticle(robotManager.getRobot()[i].get_Position() + glm::vec3(0, 1, 0));
					robotManager.getRobot()[i].Gotozero_Positon(0, -1000, 0);
				}
			}
		}
		if (bullets.collideBullet(boss.get_Position(), 13, 20, 13) == 1) {
			if (boss.minusHp(Gundamge)) {
				particle.makeBossParticle(boss.get_Position());
				boss.Gotozero_Positon(0, -1000, 0);
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1, timercall, value);
		break;
	case PARTICLE:
		particle.parLife();
		particle.parBossLife();
		glutPostRedisplay();
		glutTimerFunc(20, timercall, value);
		break;
	case ROBOTPARTICLE:
		particle.parFlyRobotLife();
		glutPostRedisplay();
		glutTimerFunc(20, timercall, value);
		break;
	case FlYROBOT:		
		for (int i = 0; i < 20; i++) {
			if (FLTrpostion[i].x > 5) {
				FLXCheck[i] = 1;
			}
			else if (FLTrpostion[i].x < -5) {
				FLXCheck[i] = 0;
			}
			if (FLTrpostion[i].y > 3) {
				FLYCheck[i] = 1;
			}
			else if (FLTrpostion[i].y < -3) {
				FLYCheck[i] = 0;
			}
			if (FLTrpostion[i].z > 5) {
				FLZCheck[i] = 1;
			}
			else if (FLTrpostion[i].z < -5) {
				FLZCheck[i] = 0;
			}
			if (FLXCheck[i] == 1) {
				FLTrpostion[i].x -= RandomFl(0, 0.03);
			}
			else if (FLXCheck[i] == 0) {
				FLTrpostion[i].x += RandomFl(0, 0.03);
			}
			if (FLYCheck[i] == 1) {
				FLTrpostion[i].y -= RandomFl(0, 0.03);;
			}
			else {
				FLTrpostion[i].y += RandomFl(0, 0.03);;
			}
			if (FLZCheck[i] == 1) {
				FLTrpostion[i].z -= RandomFl(0, 0.03);
			}
			else {
				FLTrpostion[i].z += RandomFl(0, 0.03);
			}
			flyManager.getFlyRobot()[i].move_Positon(FLTrpostion[i].x, FLTrpostion[i].y, FLTrpostion[i].z);
			robotManager.getRobot()[i].move_Positon(FLTrpostion[i].x, 0, FLTrpostion[i].z);
		}
		glutPostRedisplay();
		glutTimerFunc(10, timercall, value);
		break;
	case CNTROBOTS:		
		for (int i = 0; i < 20; i++) {
			if (flyManager.getFlyRobot()[i].getHp() <= 0)
				changDoongCnt++;
			if (robotManager.getRobot()[i].getHp() <= 0)
				robotCnt++;
		}
		if (robotCnt == 20 && changDoongCnt == 20) {
			isRenderBoss = true;
			isRenderRobot = false;
			isRenderChang = false;
		}
		else if (robotCnt == 20) {
			isRenderRobot = false;
			isRenderChang = true;
			isRenderBoss = false;
		}
		else if (changDoongCnt == 20) {
			isRenderRobot = false;
			isRenderChang = false;
			isRenderBoss = false;
		}
		glutPostRedisplay();
		glutTimerFunc(100, timercall, value);
		break;
	case BOSSMOVE:
		if (isRenderBoss) {
			robotSound++;
			if (robotSound == 1) {
				sounds.startBossSound();
			}
			if (boss.getBossYF() >= 1.0f)
				boss.decreaseBossYF();
			else {
				sounds.pauseBossSound();	
				boss.Trans_Positon(bossMove);
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, timercall, value);
		break;
	case RESETROBOTMOVE:
		if (boss.get_Position().y >= 25) {
			if (boss.get_Position().x >= 25) {
				if (boss.get_Position().z >= 25) {
					bossMove = glm::vec3(-0.2, -0.1, -0.2);
				}
				else if (boss.get_Position().z <= -25) {
					bossMove = glm::vec3(-0.2, -0.1, 0.2);
				}
				else bossMove = glm::vec3(-0.2, -0.1, RandomFl(-0.2, 0.2));
			}
			else if (boss.get_Position().x <= -25) {
				if (boss.get_Position().z >= 25) {
					bossMove = glm::vec3(0.2, -0.1, -0.2);
				}
				else if (boss.get_Position().z <= -25) {
					bossMove = glm::vec3(0.2, -0.1, 0.2);
				}
				else bossMove = glm::vec3(0.2, -0.1, RandomFl(-0.2, 0.2));
			}
			else{
				bossMove = glm::vec3(RandomFl(-0.2, 0.2), -0.1, RandomFl(-0.2, 0.2));
			}
		}
		else if (boss.get_Position().y <= 18) {
			if (boss.get_Position().x >= 25) {
				if (boss.get_Position().z >= 25) {
					bossMove = glm::vec3(-0.2, 0.1, -0.2);
				}
				else if (boss.get_Position().z <= -25) {
					bossMove = glm::vec3(-0.2, 0.1, 0.2);
				}
				else bossMove = glm::vec3(-0.2, 0.1, RandomFl(-0.2, 0.2));
			}
			else if (boss.get_Position().x <= -25) {
				if (boss.get_Position().z >= 25) {
					bossMove = glm::vec3(0.2, 0.1, -0.2);
				}
				else if (boss.get_Position().z <= -25) {
					bossMove = glm::vec3(0.2, 0.1, 0.2);
				}
				else bossMove = glm::vec3(0.2, 0.1, RandomFl(-0.2, 0.2));
			}
			else {
				bossMove = glm::vec3(RandomFl(-0.2, 0.2), 0.1, RandomFl(-0.2, 0.2));
			}
		}
		else
			bossMove = glm::vec3(RandomFl(-0.2, 0.2), RandomFl(-0.05, 0.05), RandomFl(-0.2, 0.2));
		glutTimerFunc(1500, timercall, value);
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
	if (changeCrossHead)
		perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight, 45.0f);
	else {
		perspective.perspectriveProjection(shaderfunc, Wwidth, Wheight, 12.0f);
	}
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
		Gundamge = 2;
		changeCrossHead = true;				
		pistol->setRevoluMotion(myGun->getRevolu() , myGun->getMotionX());
		myGun = dynamic_cast<Pistol*> (pistol);
		sounds.pauseWalking();
		break;
	case'2':
		Gundamge = 1;
		changeCrossHead = true;
		rifle->setRevoluMotion(myGun->getRevolu(), myGun->getMotionX());
		myGun = dynamic_cast<Rifle*> (rifle);	
		break;
	case'3':
		Gundamge = 6;
		sniper->setRevoluMotion(myGun->getRevolu(), myGun->getMotionX());
		myGun = dynamic_cast<Sniper*> (sniper);
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
	case 27://esc
		sounds.~GameSound();
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
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			if (myGun->getRecoil() >= 4.9f)
				changeCrossHead = !changeCrossHead;
		}
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			if (myGun->getRecoil() <= 1.2f) {
				particle.Makeparticle(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), Camera::getInst(glm::vec3(0, 0, 0))->getRight(), Camera::getInst(glm::vec3(0, 0, 0))->getUp());
			}
			else if (myGun->getRecoil() <= 1.4f) {
				particle.Makeparticle(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), Camera::getInst(glm::vec3(0, 0, 0))->getRight(), Camera::getInst(glm::vec3(0, 0, 0))->getUp());
			}
			else {
				particle.Makeparticle(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), Camera::getInst(glm::vec3(0, 0, 0))->getRight(), Camera::getInst(glm::vec3(0, 0, 0))->getUp());
			}
			bullets.addBullet(Camera::getInst(glm::vec3(0, 0, 0))->getPos(), Camera::getInst(glm::vec3(0, 0, 0))->getDir(), myGun->getAngles());
			pistol->setStatusAttack(true);
			sniper->setStatusAttack(true);
			rifle->setStatusAttack(true);
			Camera::getInst(glm::vec3(0, 0, 0))->setStatusAttack(true, myGun->getRecoil());
			sounds.shootingSound();
			isClick = true;
		}
		else if (state == GLUT_UP) {
			isClick = false;
			if (myGun->getRecoil() <= 1.1f) {
				rifle->controlRecoil();
				Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->controlRtateX(1.0f);
			}
		}
		break;
	default:
		break;
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
	unsigned char* sniperData = stbi_load("texture_sniper_2.jpg", &sniperwidthImage, &sniperheightImage, &snipernumberOfChannel, 0);
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
	//sniper Texture
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int sniperDotwidthImage, sniperDotheightImage, sniperDotnumberOfChannel;
	unsigned char* sniperDotData = stbi_load("texture_sniperDot2.jpg", &sniperDotwidthImage, &sniperDotheightImage, &sniperDotnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sniperDotwidthImage, sniperDotheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, sniperDotData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(sniperDotData);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int smallmapwidthImage, smallmapheightImage, smallmapnumberOfChannel;
	unsigned char* smallmapData = stbi_load("texture_smallmap.bmp", &smallmapwidthImage, &smallmapheightImage, &smallmapnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, smallmapwidthImage, smallmapheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, smallmapData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(smallmapData);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int pistolMapwidthImage, pistolMapheightImage, pistolMapnumberOfChannel;
	unsigned char* pistolMapData = stbi_load("texture_pistol_n.jpg", &pistolMapwidthImage, &pistolMapheightImage, &pistolMapnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pistolMapwidthImage, pistolMapheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, pistolMapData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pistolMapData);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int sniperMapwidthImage, sniperMapheightImage, sniperMapnumberOfChannel;
	unsigned char* sniperMapData = stbi_load("texture_sniper_n.jpg", &sniperMapwidthImage, &sniperMapheightImage, &sniperMapnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sniperMapwidthImage, sniperMapheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, sniperMapData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(sniperMapData);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int RobotwidthImage, RobotheightImage, RobotnumberOfChannel;
	unsigned char* RobotData = stbi_load("texture_Robot.bmp", &RobotwidthImage, &RobotheightImage, &RobotnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RobotwidthImage, RobotheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, RobotData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(RobotData);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int BosswidthImage, BossheightImage, BossnumberOfChannel;
	unsigned char* BossData = stbi_load("test1.png", &BosswidthImage, &BossheightImage, &BossnumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BosswidthImage, BossheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, BossData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(BossData);


	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int yellowwidthImage, yellowheightImage, yellownumberOfChannel;
	unsigned char* yellowData = stbi_load("texture_yellow.bmp", &yellowwidthImage, &yellowheightImage, &yellownumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, yellowwidthImage, yellowheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, yellowData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(yellowData);

	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int greywidthImage, greyheightImage, greynumberOfChannel;
	unsigned char* greyData = stbi_load("texture_grey.bmp", &greywidthImage, &greyheightImage, &greynumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, greywidthImage, greyheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, greyData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(greyData);


	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int hazyredwidthImage, hazyredheightImage, hazyrednumberOfChannel;
	unsigned char* hazyredData = stbi_load("texture_hazyred.bmp", &hazyredwidthImage, &hazyredheightImage, &hazyrednumberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, hazyredwidthImage, hazyredheightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, hazyredData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(hazyredData);



}

void bindingObj()
{
	pistol->bindingGun(shaderfunc);
	rifle->bindingGun(shaderfunc);
	sniper->bindingGun(shaderfunc);
	map->bindingMap(shaderfunc);
	wall->bindingMap(shaderfunc);
	bullets.bindingBullet(shaderfunc);
	

	flyManager.bindingEnemys(shaderfunc);
	robotManager.bindingEnemys(shaderfunc);
	for (int i = 0; i < 20; i++)
		flyManager.getFlyRobot()[i].Trans_Positon(RandomFl(-30, 30.0), RandomFl(15.0, 25.0), RandomFl(-30, 30.0));
	flyManager.setParent();
	for (int i = 0; i < 20; i++)
		robotManager.getRobot()[i].Trans_Positon(RandomFl(-30, 30.0), 0, RandomFl(-30, 30.0));
	robotManager.setParent();

	boss.bindingEnemys(shaderfunc);
	boss.Change_Positon(-10, 20, -5);
	
	CR.binding(shaderfunc);
	particle.bindingParticle(shaderfunc);
}

void renderObjs()
{
	particle.renderParticles(shaderfunc);
	particle.renderFlyRobotParticles(shaderfunc);
	glUniform1f(glGetUniformLocation(shaderfunc.getShaderID(), "ambientLight"), 0.45f);
	map->renderMap(shaderfunc);
	

	glUniform1f(glGetUniformLocation(shaderfunc.getShaderID(), "ambientLight"), 0.3f);

	bullets.renderBullets(shaderfunc);
	if(isRenderChang)
		flyManager.renderEnemys(shaderfunc);
	if(isRenderRobot)
		robotManager.renderEnemys(shaderfunc);

	
	boss.renderBoss(shaderfunc);

	if (changeCrossHead)
		myGun->renderGun(shaderfunc);
	
	if (changeCrossHead)
		CR.drawdotCrossHead(shaderfunc);
	else if (!changeCrossHead) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		CR.drawSniperCrossHead(shaderfunc);
		glDisable(GL_BLEND);
	}
}
