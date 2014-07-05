#include "di.h"

#include "file_system_service.h"
#include "shader_service.h"
#include "readers/reader.h"
#include "readers/obj_reader.h"
#include "buffer_allocator.h"
#include "exception_formatter.h"
#include "log_service.h"

namespace di {

Registry::Registry() {
	registerType<meow::IFileSystemService, meow::FileSystemService>();
	registerType<meow::IShaderService, meow::ShaderService>();
	registerType<meow::IReader, meow::Reader>();
	registerType<meow::IBufferAllocator, meow::BufferAllocator>();
	registerType<meow::IOBJReader, meow::OBJReader>();
	registerType<meow::IExceptionFormatter, meow::ExceptionFormatter>();
	registerType<meow::ILogService, meow::LogService>();
}


}
