#include "obj_reader.h"

#include <cstdio>
#include <vector>
#include <memory>

namespace meow {


template<typename T>
int relativeIndexToAbsoluteIndex(const std::vector<std::shared_ptr<T>> &list, int index) {
	if (index == 0 || index > static_cast<int>(list.size()))
		throw new IOBJReader::IllFormedOBJFile();
	if (index < 0)
		return list.size() + index;
	else
		return index - 1;
}

template<typename T>
Optional<T> findVector(const std::vector<std::shared_ptr<T>> &list, const Optional<int> &index) {
	if (!index.exists())
		return Optional<T>();
	auto i = relativeIndexToAbsoluteIndex(list, index.get());
	return Optional<T>(*list[i]);
}

OBJReader::OBJReader(const std::string &path) : m_filePath(path) {
}

std::shared_ptr<Model> OBJReader::read() {
	createNewModelWithOneMesh();
	auto lineReader = m_fileSystemService->getLineReader(m_filePath);
	for (auto line = lineReader->nextLine(); line.exists(); line = lineReader->nextLine()) {
		tryReadVector(line.get().c_str());
		tryReadFace(line.get().c_str());
	}
	return m_model;
}

void OBJReader::createNewModelWithOneMesh() {
	m_model = std::make_shared<Model>();
	m_model->meshes = std::make_shared<MeshList>();
	m_activeMesh = std::make_shared<Mesh>();
	m_activeMesh->indices = std::make_shared<IndexList>();
	m_activeMesh->vertices = std::make_shared<VertexList>();
	m_model->meshes->push_back(m_activeMesh);
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
	if (success) 
		m_positions.push_back(std::make_shared<glm::vec3>(v[0], v[1], v[2]));
	return success;
}

bool OBJReader::tryReadNormal(const char *line) {
	float v[3];
	auto success = sscanf(line, "vn %20f %20f %20f", &v[0], &v[1], &v[2]) == 3;
	if (success) 
		m_normals.push_back(std::make_shared<glm::vec3>(v[0], v[1], v[2]));
	return success;
}

bool OBJReader::tryReadUV(const char *line) {
	float v[2];
	auto success = sscanf(line, "vt %20f %20f %20f", &v[0], &v[1]) == 2;
	if (success) 
		m_uvs.push_back(std::make_shared<glm::vec2>(v[0], v[1]));
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
	int p[3];
	auto success = sscanf(line, "f %10i %10i %10i", &p[0], &p[1], &p[2]) == 3;
	if (success) {
		addVertex(std::make_shared<VertexIndices>(p[0], createOptional<int>(), createOptional<int>()));
		addVertex(std::make_shared<VertexIndices>(p[1], createOptional<int>(), createOptional<int>()));
		addVertex(std::make_shared<VertexIndices>(p[2], createOptional<int>(), createOptional<int>()));
	}
	return success;
}

bool OBJReader::tryReadPositionUVFace(const char *line) {
	int p[3], t[3];
	auto success = sscanf(line, "f %10i/%10i %10i/%10i %10i/%10i", &p[0], &t[0], &p[1], &t[1], &p[2], &t[2]) == 6;
	if (success) {
		addVertex(std::make_shared<VertexIndices>(p[0], createOptional<int>(), t[0]));
		addVertex(std::make_shared<VertexIndices>(p[1], createOptional<int>(), t[1]));
		addVertex(std::make_shared<VertexIndices>(p[2], createOptional<int>(), t[2]));
	}
	return success;
}

bool OBJReader::tryReadPositionNormalFace(const char *line) {
	int p[3], n[3];
	auto success = sscanf(line, "f %10i//%10i %10i//%10i %10i//%10i", &p[0], &n[0], &p[1], &n[1], &p[2], &n[2]) == 6;
	if (success) {
		addVertex(std::make_shared<VertexIndices>(p[0], n[0], createOptional<int>()));
		addVertex(std::make_shared<VertexIndices>(p[1], n[1], createOptional<int>()));
		addVertex(std::make_shared<VertexIndices>(p[2], n[2], createOptional<int>()));
	}
	return success;
}

bool OBJReader::tryReadPositionUVNormalFace(const char *line) {
	int p[3], n[3], t[3];
	auto success = sscanf(line, "f %10i/%10i/%10i %10i/%10i/%10i %10i/%10i/%10i", &p[0], &t[0], &n[0], &p[1], &t[1], &n[1], &p[2], &t[2], &n[2]) == 9;
	if (success) {
		addVertex(std::make_shared<VertexIndices>(p[0], n[0], t[0]));
		addVertex(std::make_shared<VertexIndices>(p[1], n[1], t[1]));
		addVertex(std::make_shared<VertexIndices>(p[2], n[2], t[2]));
	}
	return success;
}

void OBJReader::addVertex(std::shared_ptr<VertexIndices> vertexIndices) {
	auto keyValue = m_vertexIndicesMap.find(vertexIndices);
	if (keyValue == m_vertexIndicesMap.end()) {
		auto vertexIndex = m_activeMesh->vertices->size();
		m_vertexIndicesMap[vertexIndices] = vertexIndex;
		m_activeMesh->indices->push_back(vertexIndex);
		m_activeMesh->vertices->push_back(createVertex(*vertexIndices));
	} else {
		m_activeMesh->indices->push_back(keyValue->second);
	}
}


std::shared_ptr<Vertex> OBJReader::createVertex(const VertexIndices &vertexIndices) {
	auto pos = findVector(m_positions, vertexIndices.position);
	if (!pos.exists())
		throw new IOBJReader::IllFormedOBJFile();
	return std::make_shared<Vertex>(
		pos.get(),
		findVector(m_normals, vertexIndices.normal), 
		findVector(m_uvs, vertexIndices.uv));
}

} //namespace meow

