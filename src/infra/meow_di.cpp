#include "di.h"

#include "entities/camera_service.h"
#include "entities/normal_generator/normals_generator.h"
#include "entities/position_mesh/position_mesh_generator_factory.h"
#include "file_system/file_system_service.h"
#include "gl/shader_service.h"
#include "gl/logged_shader_service.h"
#include "gl/logged_shader_program_service.h"
#include "gl/vbo_service.h"
#include "readers/obj_reader/obj_reader.h"
#include "exception_formatter.h"
#include "log_service.h"
#include "model_service.h"
#include "window_service.h"
#include "main_loop_service.h"
#include "renderable_service.h"

namespace meow {

void initializeDI() {
	di::Container::registerType<meow::ICameraService, meow::CameraService>();
	di::Container::registerType<meow::INormalsGenerator, meow::NormalsGenerator>();
	di::Container::registerType<meow::IFileSystemService, meow::FileSystemService>();
	di::Container::registerType<meow::IShaderService, meow::LoggedShaderService>();
	di::Container::registerType<meow::IShaderProgramService, meow::LoggedShaderProgramService>();
	di::Container::registerType<meow::IModelService, meow::ModelService>();
	di::Container::registerType<meow::IVBOService, meow::VBOService>();
	di::Container::registerType<meow::IExceptionFormatter, meow::ExceptionFormatter>();
	di::Container::registerType<meow::ILogService, meow::LogService>();
	di::Container::registerType<meow::IWindowService, meow::WindowService>();
	di::Container::registerType<meow::IMainLoopService, meow::MainLoopService>();
	di::Container::registerType<meow::IRenderableService, meow::RenderableService>();
	di::Container::registerType<meow::IPositionMeshGeneratorFactory, meow::PositionMeshGeneratorFactory>();
	
}

} // namespace meow
