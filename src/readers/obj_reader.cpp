#include "obj_reader.h"

#include <cstdio>
#include <vector>
#include <memory>

namespace meow {

OBJReader::OBJReader() : m_file(nullptr), m_buffer(nullptr), m_model(nullptr) {

}

Model *OBJReader::read(const char *path) {
	openFile(path);
	allocateBuffer();
	createNewModel();

	while (auto line = readLine()) {
		tryReadVector(line);
		tryReadFace(line);
	};
	
	closeFile();
	destroyBuffer();
	return nullptr;
}

void OBJReader::createNewModel() {
	m_model = new Model();
	model->meshes = new Model::MeshList();
}

const char *OBJReader::readLine() {
	m_fileSystemService->readLine(m_file, m_buffer);
	return m_buffer->contentSize > 0 ? m_buffer->buffer : nullptr;
}

void OBJReader::openFile(const char *path) {
	m_file = m_fileSystemService->open(path, "r");
}

void OBJReader::allocateBuffer() {
	m_buffer = m_bufferAllocator->allocate(BUFFER_SIZE);
}

void OBJReader::closeFile() {
	if (m_file == nullptr)
		return;
	m_fileSystemService->close(m_file);
	m_file = nullptr;
}
void OBJReader::destroyBuffer() {
	if (m_buffer == nullptr)
		return;
	m_bufferAllocator->destroy(m_buffer);
	m_buffer = nullptr;
}

bool OBJReader::tryReadVector(const char *line) {
	if (tryReadPosition(line))
		return true;
	else if (tryReadNormal(line))
		return true;
	else if (tryReadUV(line))
		return true;
	else
		return false;
}

bool OBJReader::tryReadPosition(const char *line) {
	float v[3];
	auto success = sscanf(line, "v %20f %20f %20f", &v[0], &v[1], &v[2]) == 3;
	if (success)  {
		auto vector3 = new float[3];
		vector3[0] = v[0];
		vector3[1] = v[1];
		vector3[2] = v[2];
		m_positions.push_back(vector3);
	}
	return success;
}

bool OBJReader::tryReadNormal(const char *line) {
	float v[3];
	auto success = sscanf(line, "vn %20f %20f %20f", &v[0], &v[1], &v[2]) == 3;
	if (success) {
		auto vector3 = new float[3];
		vector3[0] = v[0];
		vector3[1] = v[1];
		vector3[2] = v[2];
		m_normals.push_back(vector3);
	}
	return success;
}

bool OBJReader::tryReadUV(const char *line) {
	float v[2];
	auto success = sscanf(line, "vt %20f %20f %20f", &v[0], &v[1]) == 2;
	if (success) {
		auto vector3 = new float[2];
		vector3[0] = v[0];
		vector3[1] = v[1];
		m_uvs.push_back(v);
	}
	return success;
} 

bool OBJReader::tryReadFace(const char *line) {
	if (tryReadPositionFace(line))
		return true;
	else if (tryReadPositionUVFace(line))
		return true;
	else if (tryReadPositionNormalFace(line))
		return true;
	else if (tryReadPositionUVNormalFace(line))
		return true;
	else
		return false;
}

bool OBJReader::tryReadPositionFace(const char *line) {
	uint16_t p[3];
	auto success = sscanf(line, "f %10i %10i %10i", &p[0], &p[1], &p[2]) == 3;
	if (success) {
		addVertex(createVertex(&p[0], nullptr, nullptr));
		addVertex(createVertex(&p[1], nullptr, nullptr));
		addVertex(createVertex(&p[2], nullptr, nullptr));
	}
	return success;
}

bool OBJReader::tryReadPositionUVFace(const char *line) {
	uint16_t p[3], t[3];
	auto success = sscanf(line, "f %10i/%10i %10i/%10i %10i/%10i", &p[0], &t[0], &p[1], &t[1], &p[2], &t[2]) == 6;
	if (success) {
		addVertex(createVertex(&p[0], nullptr, &t[0]));
		addVertex(createVertex(&p[1], nullptr, &t[1]));
		addVertex(createVertex(&p[2], nullptr, &t[2]));
	}
	return success;
}

bool OBJReader::tryReadPositionNormalFace(const char *line) {
	uint16_t p[3], n[3];
	auto success = sscanf(line, "f %10i//%10i %10i//%10i %10i//%10i", &p[0], &n[0], &p[1], &n[1], &p[2], &n[2]) == 6;
	if (success) {
		addVertex(createVertex(&p[0], &n[0], nullptr));
		addVertex(createVertex(&p[1], &n[1], nullptr));
		addVertex(createVertex(&p[2], &n[2], nullptr));
	}
	return success;
}

bool OBJReader::tryReadPositionUVNormalFace(const char *line) {
	uint16_t p[3], n[3], t[3];
	auto success = sscanf(line, "f %10i/%10i/%10i %10i/%10i/%10i %10i/%10i/%10i", &p[0], &t[0], &n[0], &p[1], &t[1], &n[1], &p[2], &t[2], &n[2]) == 9;
	if (success) {
		addVertex(createVertex(&p[0], &n[0], &t[0]));
		addVertex(createVertex(&p[1], &n[1], &t[1]));
		addVertex(createVertex(&p[2], &n[2], &t[2]));
	}
	return success;
}

Vertex *OBJReader::createVertex(uint16_t *position, uint16_t *normal, uint16_t *uv) {
	auto vertex = new Vertex;
	vertex->position = position == nullptr ? findPosition(*position) : nullptr;
	vertex->normal = normal == nullptr ? findNormal(*normal) : nullptr;
	vertex->uv = uv == nullptr ? findUV(*uv) : nullptr;
	return vertex;
}

float *OBJReader::findPosition(int32_t index) {
	if (index < 0)
		index = m_positions.size() + index;
	if (index >= m_positions.size())
		return nullptr;
	return m_positions[index];
}

float *OBJReader::findNormal(int32_t index) {
	if (index < 0)
		index = m_normals.size() + index;
	if (index >= m_normals.size())
		return nullptr;
	return m_normals[index];
}

float *OBJReader::findUV(int32_t index) {
	if (index < 0)
		index = m_uvs.size() + index;
	if (index >= m_uvs.size())
		return nullptr;
	return m_uvs[index];
}

void OBJReader::addVertex(Vertex *vertex) {
	auto keyValue = m_vertexMap.find(vertex);
	if (keyValue == m_vertexMap.end()) {
		m_vertexMap[vertex] = m_vertices.size();
		m_indices.push_back(m_vertices.size());
		m_vertices.push_back(vertex);
	} else {
		m_indices.push_back(keyValue->second);
	}
}

} //namespace meow

