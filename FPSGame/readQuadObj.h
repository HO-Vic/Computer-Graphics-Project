#pragma once
#include<string>
#include"include/glm/glm.hpp"
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
void readQuadObj(const std::string objfilename, std::vector<glm::vec3>& vertex, std::vector<glm::vec3>& vertexNomal);