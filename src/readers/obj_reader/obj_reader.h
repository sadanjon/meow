#ifndef OBJ_READER_H 
#define OBJ_READER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "infra/di.h"
#include "model.h"
#include "file_system/ifile_system_service.h"
#include "ilog_service.h"
#include "iobj_reader.h"
#include "vertex_indices_map.h"
#include "math/vector3.h"
#include "math/vector2.h"

namespace meow {

class OBJReader : public IOBJReader {
	static const int BUFFER_SIZE = 512;
	typedef std::vector<std::shared_ptr<Vector3>> Vector3List;
	typedef std::vector<std::shared_ptr<Vector2>> Vector2List;

	di::Component<IFileSystemService> m_fileSystemService;
	di::Component<ILogService> m_logService;

	const std::string m_filePath;
	std::shared_ptr<Model> m_model;
	std::shared_ptr<Mesh> m_activeMesh;
	Vector3List m_positions;
	Vector3List m_normals;
	Vector2List m_uvs;
	VertexIndicesMap m_vertexIndicesMap;
public:
	OBJReader(const std::string &path);

	std::shared_ptr<Model> read() override;
private:
	void createNewModelWithOneMesh();

	bool tryReadVector(const char *line);
	bool tryReadPosition(const char *line);
	bool tryReadNormal(const char *line);
	bool tryReadUV(const char *line);

	bool tryReadFace(const char *line);
	bool tryReadPositionFace(const char *line);
	bool tryReadPositionUVFace(const char *line);
	bool tryReadPositionNormalFace(const char *line);
	bool tryReadPositionUVNormalFace(const char *line);

	void addVertex(std::shared_ptr<VertexIndices> vertex);
	std::shared_ptr<Vertex> createVertex(const VertexIndices &vertexIndices);
};



} // namespace meow

#endif // OBJ_READER_H