#include "FlyRobotManager.h"

void FlyRobotManager::renderEnemys(ShaderFunc& shaderID)
{
	for (int i = 0; i < 20; i++) {
		flyrobotbody[i].renderEnemy(shaderID, robotBodyVAO, robotBodyVertexData.size());
		flyrobotlarm[i].renderEnemy(shaderID, robotArmLVAO, robotArmLVertexData.size());
		flyrobotrarm[i].renderEnemy(shaderID, robotArmRVAO, robotArmRVertexData.size());
		flyrobotspin[i].renderEnemy(shaderID, robotSpinVAO, robotSpinVertexData.size());
		flyrobotweapon[i].renderEnemy(shaderID, robotWeaponVAO, robotWeaponVertexData.size());
	}
}

void FlyRobotManager::bindingEnemy(ShaderFunc& shaderID, string name)
{
	if (name == "Obj_FlyRobot_Body.obj") {
		readTriangleObj(name, robotBodyVertexData, robotBodyTextureData, robotBodyNormalData);
		shaderID.InitBuffer(robotBodyVAO, robotBodyVertexVBO, robotBodyTextureVBO, robotBodyNormalVBO, robotBodyVertexData, robotBodyTextureData, robotBodyNormalData);
	}
	if (name == "Obj_FlyRobot_Larm.obj") {
		readTriangleObj(name, robotArmLVertexData, robotArmLTextureData, robotArmLNormalData);
		shaderID.InitBuffer(robotArmLVAO, robotArmLVertexVBO, robotArmLTextureVBO, robotArmLNormalVBO, robotArmLVertexData, robotArmLTextureData, robotArmLNormalData);
	}
	if (name == "Obj_FlyRobot_Rarm.obj") {
		readTriangleObj(name, robotArmRVertexData, robotArmRTextureData, robotArmRNormalData);
		shaderID.InitBuffer(robotArmRVAO, robotArmRVertexVBO, robotArmRTextureVBO, robotArmRNormalVBO, robotArmRVertexData, robotArmRTextureData, robotArmRNormalData);
	}
	if (name == "Obj_FlyRobot_Spin.obj") {
		readTriangleObj(name, robotSpinVertexData, robotSpinTextureData, robotSpinNormalData);
		shaderID.InitBuffer(robotSpinVAO, robotSpinVertexVBO, robotSpinTextureVBO, robotSpinNormalVBO, robotSpinVertexData, robotSpinTextureData, robotSpinNormalData);
	}
	if (name == "Obj_weapon.obj") {
		readTriangleObj(name, robotWeaponVertexData, robotWeaponTextureData, robotWeaponNormalData);
		shaderID.InitBuffer(robotWeaponVAO, robotWeaponVBO, robotWeaponTextureVBO, robotWeaponNormalVBO, robotWeaponVertexData, robotWeaponTextureData, robotWeaponNormalData);
	}

}

Flyrobot* FlyRobotManager::getFlyRobot()
{
	return flyrobotbody;
}

void FlyRobotManager::setParent()
{
	for (int i = 0; i < 20; i++) {
		flyrobotlarm[i].Apply_Parent(&flyrobotbody[i]);
		flyrobotrarm[i].Apply_Parent(&flyrobotbody[i]);
		flyrobotspin[i].Apply_Parent(&flyrobotbody[i]);
		flyrobotweapon[i].Apply_Parent(&flyrobotbody[i]);
	}
}

FlyRobotManager::FlyRobotManager()
{
	for (int i = 0; i < 20; i++){
		flyrobotbody[i].Change_Scale(4, 4, 4);
		flyrobotweapon[i].Change_Scale(0.2, 0.2, 0.2);
}
}

void FlyRobotManager::bindingEnemys(ShaderFunc& shaderID)
{
	bindingEnemy(shaderID, "Obj_FlyRobot_Body.obj");
	bindingEnemy(shaderID, "Obj_FlyRobot_Larm.obj");
	bindingEnemy(shaderID, "Obj_FlyRobot_Spin.obj");
	bindingEnemy(shaderID, "Obj_FlyRobot_Rarm.obj");
	bindingEnemy(shaderID, "Obj_weapon.obj");
}
