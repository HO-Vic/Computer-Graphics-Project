#include "readTriangleObj.h"
//triangle polygon
void readTriangleObj(const std::string objfilename, std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& vertexTexture, std::vector<glm::vec3>& vertexNomal)
{
	std::vector<glm::vec4> vertexFace;
	std::vector<glm::vec4> vertexNomalFace;
	std::vector<glm::vec4> vertexTextureFace;
	std::string line;
	int vertexNum = 0;
	int vertexNomalNum = 0;
	int vertexTextureNum = 0;
	std::ifstream inFile(objfilename);

	while (std::getline(inFile, line)) {
		if (line[0] == 'v' && line[1] == ' ')
			vertexNum++;
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			vertexNomalNum++;
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			vertexTextureNum++;
	}
	glm::vec4* vertexData = new glm::vec4[vertexNum];
	glm::vec4* vertexNomalData = new glm::vec4[vertexNomalNum];
	glm::vec2* vertexTextureData = new glm::vec2[vertexTextureNum];
	inFile.clear();
	inFile.seekg(0, std::ios::beg);
	vertexNum = 0;
	vertexNomalNum = 0;
	vertexTextureNum = 0;
	char head[3];
	int vertexFaceNum[3];
	int vertexNomalFaceNum[3];
	int vertexTextureFaceNum[3];
	std::string nt;
	while (inFile >> std::noskipws >> head[0]) {
		if (head[0] == 'v') {
			inFile >> std::noskipws >> head[1];
			if (head[1] == ' ') {
				inFile >> std::skipws >> vertexData[vertexNum].x >> vertexData[vertexNum].y >> vertexData[vertexNum].z;
				vertexNum++;
			}
			else if (head[1] == 'n') {
				inFile >> std::noskipws >> head[2];
				if (head[2] == ' ') {
					inFile >> std::skipws >> vertexNomalData[vertexNomalNum].x >> vertexNomalData[vertexNomalNum].y >> vertexNomalData[vertexNomalNum].z;
					vertexNomalNum++;
				}
			}
			else if (head[1] == 't') {
				inFile >> std::noskipws >> head[2];
				if (head[2] == ' ') {
					float tr;
					inFile >> std::skipws >> vertexTextureData[vertexTextureNum].x >> vertexTextureData[vertexTextureNum].y >> tr;
					vertexTextureNum++;
				}
			}
			head[1] = '\0';
		}
		if (head[0] == 'f') {
			inFile >> std::noskipws >> head[1];
			if (head[1] == ' ') {
				char tempC;
				int tempi;
				inFile >> std::skipws >> vertexFaceNum[0];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexTextureFaceNum[0];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[0];

				inFile >> std::skipws >> vertexFaceNum[1];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexTextureFaceNum[1];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[1];

				inFile >> std::skipws >> vertexFaceNum[2];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexTextureFaceNum[2];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[2];

				glm::vec4 vertexFaceTemp = { vertexFaceNum[0], vertexFaceNum[1], vertexFaceNum[2], 1 };
				glm::vec4 vertexNomalFaceTemp = { vertexNomalFaceNum[0], vertexNomalFaceNum[1], vertexNomalFaceNum[2],1 };
				glm::vec4 vertexTextureFaceTemp = { vertexTextureFaceNum[0], vertexTextureFaceNum[1], vertexTextureFaceNum[2],1 };
				vertexFace.push_back(vertexFaceTemp);
				vertexNomalFace.push_back(vertexNomalFaceTemp);
				vertexTextureFace.push_back(vertexTextureFaceTemp);
			}
			head[1] = '\0';
		}
	}
	for (auto iter = vertexFace.begin(); iter < vertexFace.end(); iter++) {
		vertex.push_back(vertexData[(int)(iter->x) - 1]);
		vertex.push_back(vertexData[(int)(iter->y) - 1]);
		vertex.push_back(vertexData[(int)(iter->z) - 1]);
	}
	for (auto iter = vertexNomalFace.begin(); iter < vertexNomalFace.end(); iter++) {
		vertexNomal.push_back(vertexNomalData[(int)(iter->x) - 1]);
		vertexNomal.push_back(vertexNomalData[(int)(iter->y) - 1]);
		vertexNomal.push_back(vertexNomalData[(int)(iter->z) - 1]);
	}
	for (auto iter = vertexTextureFace.begin(); iter < vertexTextureFace.end(); iter++) {
		vertexTexture.push_back(vertexTextureData[(int)(iter->x) - 1]);
		vertexTexture.push_back(vertexTextureData[(int)(iter->y) - 1]);
		vertexTexture.push_back(vertexTextureData[(int)(iter->z) - 1]);
	}
	delete[] vertexData;
	delete[] vertexNomalData;
	delete[] vertexTextureData;
	inFile.close();

}
