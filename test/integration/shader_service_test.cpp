#include "gmock/gmock.h"

#include <memory>

#include "driver_runner.h"
#include "file_system/file_system_service.h"
#include "gl/logged_shader_service.h"
#include "log_service.h"
#include "infra/di.h"

using namespace meow;
using namespace testing;

void initializeDI() {
	di::Container::registerType<meow::IDriverRunner, meow::DriverRunner>();
	di::Container::registerType<meow::IFileSystemService, meow::FileSystemService>();
	di::Container::registerType<meow::IShaderService, meow::LoggedShaderService>();
	di::Container::registerType<meow::ILogService, meow::LogService>();
}

class ShaderServiceTest : public Test {
public:
	std::shared_ptr<IShaderService> shaderService;

	ShaderServiceTest() {
		shaderService = std::make_shared<LoggedShaderService>();
	}
};

TEST_F(ShaderServiceTest, simple) {
	auto shader = shaderService->create("../test/assets/shader_service_test/simple.vs", ShaderType::VERTEX);
	EXPECT_TRUE(true);
}

class TestDriver : public IDriver {
public:
	int run(int argc, char **argv) override {
		testing::InitGoogleMock(&argc, argv);
		return RUN_ALL_TESTS();
	}
};

int main(int argc, char **argv) {
	initializeDI();
	auto driver = std::make_shared<TestDriver>();
	auto driverRunner = std::make_shared<DriverRunner>();
	return driverRunner->run(*driver, argc, argv);
}