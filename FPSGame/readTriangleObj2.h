#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include<random>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<stdio.h>
bool readTriangleObj2(const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals);