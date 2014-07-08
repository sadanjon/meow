#ifndef OBJ_READER_H 
#define OBJ_READER_H

#include <vector>
#include <unordered_map>

#include "di.h"
#include "model.h"
#include "ifile_system_service.h"
#include "ibuffer_allocator.h"
#include "ilog_service.h"
#include "readers/vertex_map.h"

namespace meow {

class OBJReader {
	static const int BUFFER_SIZE = 512;
	di::Component<IFileSystemService> m_fileSystemService;
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<ILogService> m_logService;

	File *m_file;
	Buffer *m_buffer;
	Model *m_model;

	std::vector<float*> m_positions;
	std::vector<float*> m_normals;
	std::vector<float*> m_uvs;
	Model *m_model;
	VertexMap m_vertexMap;
public:
	OBJReader();

	Model *read(const char *path);
private:
	void createNewModel();

	bool tryReadVector(const char *line);
	bool tryReadPosition(const char *line);
	bool tryReadNormal(const char *line);
	bool tryReadUV(const char *line);

	bool tryReadFace(const char *line);
	bool tryReadPositionFace(const char *line);
	bool tryReadPositionUVFace(const char *line);
	bool tryReadPositionNormalFace(const char *line);
	bool tryReadPositionUVNormalFace(const char *line);


	Vertex *createVertex(uint16_t *position, uint16_t *normal, uint16_t *uv);
	float *findPosition(int32_t index);
	float *findNormal(int32_t index);
	float *findUV(int32_t index);
	void addVertex(Vertex *vertex);


	void openFile(const char *path);
	void allocateBuffer();
	void closeFile();
	void destroyBuffer();
	const char *readLine();
};



} // namespace meow

#endif // OBJ_READER_H