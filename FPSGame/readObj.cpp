#include "readObj.h"

void ReadObj(const std::string objfilename, std::vector<glm::vec4>& vertex)
{
	std::vector<glm::vec4> face;
	std::string line;	
	int vertexNum = 0;
	std::ifstream inFile(objfilename);

	while (std::getline(inFile, line)) {
		if (line[0] == 'v' && line[1] == ' ')
			vertexNum++;
		std::cout << line << std::endl;
	}
	glm::vec4* vertexData = new glm::vec4[vertexNum];

	inFile.clear();
	inFile.seekg(0, std::ios::beg);
	vertexNum = 0;
	char head[2];
	int faceNum[4];
	std::string nt;
	while (inFile >> std::noskipws >> head[0]) {
		if (head[0] == 'v') {
			inFile >> std::noskipws >> head[1];
			if (head[1] == ' ') {
				inFile >> std::skipws >>vertexData[vertexNum].x >> vertexData[vertexNum].y >> vertexData[vertexNum].z;
				vertexNum++;
			}
			head[1] = '\0';
		}
		if (head[0] == 'f') {
			inFile >> std::noskipws >> head[1];
			if (head[1] == ' ') {
				inFile >> std::skipws >> faceNum[0];
				inFile >> std::skipws >> nt;
				inFile >> std::skipws >> faceNum[1];
				inFile >> std::skipws >> nt;
				inFile >> std::skipws >> faceNum[2];
				inFile >> std::skipws >> nt;
				inFile >> std::skipws >> faceNum[3];
				glm::vec4 temp = { faceNum[0], faceNum[1], faceNum[2], faceNum[3] };
				face.push_back(temp);
			}
			head[1] = '\0';
		}
	}
	for (auto iter = face.begin(); iter < face.end(); iter++) {
		vertex.push_back(vertexData[(int)(iter->x) - 1]);
		vertex.push_back(vertexData[(int)(iter->y) - 1]);
		vertex.push_back(vertexData[(int)(iter->z) - 1]);
		vertex.push_back(vertexData[(int)(iter->w) - 1]);
	}

}
