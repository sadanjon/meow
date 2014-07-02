#ifndef MEOW_DI_H 
#define MEOW_DI_H

#include "buffer_allocator.h"
#include "reader.h"
#include "logged_shader_service.h"
#include "file_system_service.h"
#include "log_service.h"

#include "di.h"

DI_USE(meow::IBufferAllocator, meow::BufferAllocator);
DI_USE(meow::IReader, meow::Reader);

#ifdef DISABLE_LOGGING
DI_USE(meow::IShaderService, meow::ShaderService);
#else
DI_USE(meow::IShaderService, meow::LoggedShaderService);
#endif

DI_USE(meow::IFileSystemService, meow::FileSystemService);
DI_USE(meow::ILogService, meow::LogService);

#endif // MEOW_DI_H