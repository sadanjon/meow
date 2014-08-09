#ifndef FACE_NORMALS_GENERATOR_H 
#define FACE_NORMALS_GENERATOR_H

#include <vector>

#include "glm/vec3.hpp"

#include "model.h"

namespace meow {

typedef std::vector<glm::vec3> Vec3List;
	
class FaceNormalsGenerator {
	typedef std::vector<std::shared_ptr<VertexList>> VertexListList;
	
	Mesh &m_mesh;
	std::shared_ptr<IndexList> m_newIndices;
	std::shared_ptr<VertexList> m_newVertices;
	Vec3List m_triangle;
	const bool m_clockwiseFaces;

public:
	FaceNormalsGenerator(Mesh &mesh, bool clockwiseFaces);
	FaceNormalsGenerator(const FaceNormalsGenerator&) = delete;
	FaceNormalsGenerator &operator=(FaceNormalsGenerator) = delete;

	void generate();
private:
	std::shared_ptr<VertexListList> createTriangles();
	void createFaceNormal(const VertexList &triangle);
	void pushNewTriangle(const VertexList &triangle, IndexType triangleIndex);
	
};

} // namespace meow

#endif // FACE_NORMALS_GENERATOR_H