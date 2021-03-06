include(cmake/gmock.cmake)

add_executable(unit_tests test/all_unit_tests.cpp test/math_test.cpp src/my_math.cpp src/my_math.h)

add_executable(obj_reader_test 
	test/integration/obj_reader_test.cpp 
	src/infra/di.h
	src/infra/di.cpp
	src/model_service.h
	src/model_service.cpp
	src/file_system/file_system_service.h
	src/file_system/file_system_service.cpp
	src/file_system/file.h
	src/file_system/file.cpp
	src/file_system/line_reader.h
	src/file_system/line_reader.cpp
	src/file_system/text_reader.h
	src/file_system/text_reader.cpp
	src/readers/obj_reader/obj_reader.h
	src/readers/obj_reader/obj_reader.cpp
	src/model.h
	src/model_service.h
	src/model_service.cpp
	src/ilog_service.h
	src/log_service.h
	src/log_service.cpp
	)

add_executable(shader_service_test 
	test/integration/shader_service_test.cpp 
	src/gl_extensions.h
	src/gl_extensions.cpp
	src/idriver_runner.h
	src/driver_runner.h
	src/driver_runner.cpp
	src/infra/di.h
	src/infra/di.cpp
	src/file_system/ifile_system_service.h
	src/file_system/file_system_service.h
	src/file_system/file_system_service.cpp
	src/file_system/ifile.h
	src/file_system/file.h
	src/file_system/file.cpp
	src/file_system/iline_reader.h
	src/file_system/line_reader.h
	src/file_system/line_reader.cpp
	src/file_system/itext_reader.h
	src/file_system/text_reader.h
	src/file_system/text_reader.cpp
	src/gl/ishader_service.h
	src/gl/shader_service.h
	src/gl/shader_service.cpp
	src/gl/logged_shader_service.h
	src/gl/logged_shader_service.cpp
	src/ilog_service.h
	src/log_service.h
	src/log_service.cpp
	)


include_directories(${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(unit_tests ${GMOCK_LIBRARIES})
target_link_libraries(obj_reader_test ${GMOCK_LIBRARIES} ${SDL2_LIBRARIES})
target_link_libraries(shader_service_test ${GMOCK_LIBRARIES} ${SDL2_LIBRARIES})

add_test(NAME unit 
         COMMAND unit_tests)

add_test(NAME obj_reader 
         COMMAND obj_reader_test)


add_test(NAME shader_service 
         COMMAND shader_service_test)
