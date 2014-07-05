#include "obj_reader.h"

#include <cstdio>
#include <vector>
#include <memory>

namespace meow {

Model *OBJReader::read(const char *path) {
	std::unique_ptr<StatefullOBJReader> reader(new StatefullOBJReader());
	return reader->read(path);
}

Model *StatefullOBJReader::read(const char *path) {
	auto buffer = m_bufferAllocator->allocate(512);
	auto file = m_fileSystemService->open(path, "r");

	size_t readCount;
	do {
		readCount = m_fileSystemService->readLine(file, buffer);
		auto line = buffer->buffer;

		Vector3 v;
		if (tryReadPosition(line, &v))
			m_logService->info("position: %f %f %f\n", v.x, v.y, v.z);
		else if (tryReadNormal(line, &v))
			m_logService->info("normal: %f %f %f\n", v.x, v.y, v.z);
		else if (tryReadUV(line, &v))
			m_logService->info("uv: %f %f %f\n", v.x, v.y, v.z);
		else
			m_logService->info("no read\n");
	} while (readCount != 0);

	m_fileSystemService->close(file);
	m_bufferAllocator->destroy(buffer);
	return NULL;
}

bool StatefullOBJReader::tryReadPosition(const char *line, Vector3 *v) {
	return sscanf(line, "v %20f %20f %20f", &v->x, &v->y, &v->z) == 3;
}

bool StatefullOBJReader::tryReadNormal(const char *line, Vector3 *v) {
	return sscanf(line, "vn %20f %20f %20f", &v->x, &v->y, &v->z) == 3;
}

bool StatefullOBJReader::tryReadUV(const char *line, Vector3 *v) {
	return sscanf(line, "vt %20f %20f %20f", &v->x, &v->y, &v->z) == 3;
} 



} //namespace meow