#include "RobotManager.h"

void RobotManager::bindingEnemy(ShaderFunc& shaderID, std::string name)
{
	if (name == "obj_Robot_body.obj") {
		readTriangleObj(name, robotBodyVertexData, robotBodyTextureData, robotBodyNormalData);
		shaderID.InitBuffer(robotBodyVAO, robotBodyVertexVBO, robotBodyTextureVBO, robotBodyNormalVBO, robotBodyVertexData, robotBodyTextureData, robotBodyNormalData);
	}
	if (name == "obj_Robot_larm.obj") {
		readTriangleObj(name, robotArmLVertexData, robotArmLTextureData, robotArmLNormalData);
		shaderID.InitBuffer(robotArmLVAO, robotArmLVertexVBO, robotArmLTextureVBO, robotArmLNormalVBO, robotArmLVertexData, robotArmLTextureData, robotArmLNormalData);
	}
	if (name == "obj_Robot_rarm.obj") {
		readTriangleObj(name, robotArmRVertexData, robotArmRTextureData, robotArmRNormalData);
		shaderID.InitBuffer(robotArmRVAO, robotArmRVertexVBO, robotArmRTextureVBO, robotArmRNormalVBO, robotArmRVertexData, robotArmRTextureData, robotArmRNormalData);
	}
	if (name == "obj_Robot_head.obj") {
		readTriangleObj(name, robotHeadVertexData, robotHeadTextureData, robotHeadNormalData);
		shaderID.InitBuffer(robotHeadVAO, robotHeadVertexVBO, robotHeadTextureVBO, robotHeadNormalVBO, robotHeadVertexData, robotHeadTextureData, robotHeadNormalData);
	}
	if (name == "obj_Robot_lleg.obj") {
		readTriangleObj(name, robotLegLVertexData, robotLegLTextureData, robotLegLNormalData);
		shaderID.InitBuffer(robotLegLVAO, robotLegLVertexVBO, robotLegLTextureVBO, robotLegLNormalVBO, robotLegLVertexData, robotLegLTextureData, robotLegLNormalData);
	}
	if (name == "obj_Robot_rleg.obj") {
		readTriangleObj(name, robotLegRVertexData, robotLegRTextureData, robotLegRNormalData);
		shaderID.InitBuffer(robotLegRVAO, robotLegRVertexVBO, robotLegRTextureVBO, robotLegRNormalVBO, robotLegRVertexData, robotLegRTextureData, robotLegRNormalData);
	}
}

void RobotManager::bindingEnemys(ShaderFunc& shaderID)
{
	bindingEnemy(shaderID, "obj_Robot_body.obj");
	bindingEnemy(shaderID, "obj_Robot_head.obj");
	bindingEnemy(shaderID, "obj_Robot_larm.obj");
	bindingEnemy(shaderID, "obj_Robot_rarm.obj");
	bindingEnemy(shaderID, "obj_Robot_lleg.obj");
	bindingEnemy(shaderID, "obj_Robot_rleg.obj");

}

void RobotManager::renderEnemys(ShaderFunc& shaderID)
{
	for (int i = 0; i < 20; i++) {
		robotbody[i].renderEnemy(shaderID, robotBodyVAO, robotBodyVertexData.size());
		robotLArm[i].renderEnemy(shaderID, robotArmLVAO, robotArmLVertexData.size());
		robotRArm[i].renderEnemy(shaderID, robotArmRVAO, robotArmRVertexData.size());
		robotLegL[i].renderEnemy(shaderID, robotLegLVAO, robotLegLVertexData.size());
		robotLegR[i].renderEnemy(shaderID, robotLegRVAO, robotLegRVertexData.size());
		robotHead[i].renderEnemy(shaderID, robotHeadVAO, robotHeadVertexData.size());

	}
}

Robot* RobotManager::getRobot()
{
	return robotbody;
}

void RobotManager::setParent()
{
	for (int i = 0; i < 20; i++) {
		robotLArm[i].Apply_Parent(&robotbody[i]);
		robotRArm[i].Apply_Parent(&robotbody[i]);
		robotLegL[i].Apply_Parent(&robotbody[i]);
		robotLegR[i].Apply_Parent(&robotbody[i]);
		robotHead[i].Apply_Parent(&robotbody[i]);
	}
}

RobotManager::RobotManager()
{
	for (int i = 0; i < 20; i++)
		robotbody[i].Change_Scale(0.5, 0.5, 0.5);

}
