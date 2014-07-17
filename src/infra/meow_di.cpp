#include "di.h"

#include "file_system/file_system_service.h"
#include "gl/shader_service.h"
#include "readers/obj_reader/obj_reader.h"
#include "exception_formatter.h"
#include "log_service.h"
#include "model_service.h"
#include "math/vector3_service.h"

namespace meow {

void initializeDI() {
	di::Container::registerType<meow::IFileSystemService, meow::FileSystemService>();
	di::Container::registerType<meow::IShaderService, meow::ShaderService>();
	di::Container::registerType<meow::IModelService, meow::ModelService>();
	di::Container::registerType<meow::IVector3Service, meow::Vector3Service>();
	di::Container::registerType<meow::IExceptionFormatter, meow::ExceptionFormatter>();
	di::Container::registerType<meow::ILogService, meow::LogService>();
}

} // namespace meow
