#include "readTriangleObj.h"
//triangle polygon
void readTriangleObj(const std::string objfilename, std::vector<glm::vec3>& vertex, std::vector<glm::vec3>& vertexNomal)
{
	std::vector<glm::vec3> vertexFace;
	std::vector<glm::vec3> vertexNomalFace;
	std::string line;
	int vertexNum = 0;
	int vertexNomalNum = 0;
	std::ifstream inFile(objfilename);

	while (std::getline(inFile, line)) {
		if (line[0] == 'v' && line[1] == ' ')
			vertexNum++;
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			vertexNomalNum++;
		std::cout << line << std::endl;
	}
	glm::vec4* vertexData = new glm::vec4[vertexNum];
	glm::vec4* vertexNomalData = new glm::vec4[vertexNomalNum];
	inFile.clear();
	inFile.seekg(0, std::ios::beg);
	vertexNum = 0;
	vertexNomalNum = 0;
	char head[3];
	int vertexFaceNum[3];
	int vertexNomalFaceNum[3];
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
			head[1] = '\0';
		}
		if (head[0] == 'f') {
			inFile >> std::noskipws >> head[1];
			if (head[1] == ' ') {
				char tempC;
				int tempi;
				inFile >> std::skipws >> vertexFaceNum[0];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> tempi;
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[0];
				inFile >> std::skipws >> vertexFaceNum[1];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> tempi;
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[1];				
				inFile >> std::skipws >> vertexFaceNum[2];
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> tempi;
				inFile >> std::skipws >> tempC;
				inFile >> std::skipws >> vertexNomalFaceNum[2];				
				glm::vec3 vertexFaceTemp = { vertexFaceNum[0], vertexFaceNum[1], vertexFaceNum[2]};
				glm::vec3 vertexNomalFaceTemp = { vertexNomalFaceNum[0], vertexNomalFaceNum[1], vertexNomalFaceNum[2]};
				vertexFace.push_back(vertexFaceTemp);
				vertexNomalFace.push_back(vertexNomalFaceTemp);
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
	delete[] vertexData;
	delete[] vertexNomalData;
	inFile.close();
	
}
