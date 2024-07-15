#pragma once

#include "Vertex.h"

#include <vector>

struct Circle {
	std::vector<Vertex> circle;
	glm::mat4 model;
	glm::mat4 mvp;
};