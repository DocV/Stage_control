#ifndef PLANE_H
#define PLANE_H

#include "stdafx.h"
#include <vector>
#include <glm\glm.hpp>

namespace stage_control{
	static std::vector<glm::vec3> plane_vertices = {
		glm::vec3(-1.000000, 0.000000, 1.000000),
		glm::vec3(1.000000, 0.000000, 1.000000),
		glm::vec3(-1.000000, 0.000000, - 1.000000),
		glm::vec3(1.000000, 0.000000, - 1.000000)
	};

	static std::vector<int> plane_faces = {
		2, 4, 3,
		1, 2, 3
	};

	static std::vector<glm::vec3> generate_plane_vertices(){
		std::vector<glm::vec3> ret;
		for (unsigned int i = 0; i < plane_faces.size(); i++){
			ret.push_back(plane_vertices[plane_faces[i] - 1]);
		}
		return ret;
	}

	static std::vector<glm::vec3> generate_plane_colors(){
		std::vector<glm::vec3> ret;
		for (unsigned int i = 0; i < plane_faces.size(); i++){
			ret.push_back(glm::vec3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
				static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
				static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
		}
		return ret;
	}
}

#endif