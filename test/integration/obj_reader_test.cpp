#include "gmock/gmock.h"

#include <memory>

#include "file_system/file_system_service.h"
#include "infra/buffer_allocator.h"
#include "model_service.h"
#include "log_service.h"
#include "infra/di.h"

using namespace meow;
using namespace testing;

class OBJReaderTest : public Test {
public:
	std::shared_ptr<IFileSystemService> fileSystemService;
	std::shared_ptr<IModelService> modelService;

	OBJReaderTest() {
		di::Container::registerType<meow::IFileSystemService, meow::FileSystemService>();
		di::Container::registerType<meow::IBufferAllocator, meow::BufferAllocator>();
		di::Container::registerType<meow::IModelService, meow::ModelService>();
		di::Container::registerType<meow::ILogService, meow::ModelService>();

		fileSystemService = std::make_shared<FileSystemService>();
		modelService = std::make_shared<ModelService>();
	}
};

template<typename T>
void assertVectorExistsEquals(const Optional<T> &a, const T &b) {
	ASSERT_TRUE(a.exists());
	ASSERT_THAT(a.get(), Eq(b));
}

const Vertex &getVertexAt(const Model &model, int index) {
	auto &mesh = *model.meshes->at(0);
	auto &indices = *mesh.indices;
	auto &vertices = *mesh.vertices;
	return *vertices[indices[index]];
}

TEST_F(OBJReaderTest, simple) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/simple.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-3.000000f, 1.800000f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-2.976687f, 1.920243f, -0.081000f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-2.976687f, 1.920243f, -0.081000f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-2.991600f, 1.800000f, -0.081000f));
}

TEST_F(OBJReaderTest, simple_with_comments) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/simple_with_comments.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-3.000000f, 1.800000f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-2.976687f, 1.920243f, -0.081000f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-2.976687f, 1.920243f, -0.081000f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-2.991600f, 1.800000f, -0.081000f));
}

TEST_F(OBJReaderTest, out_of_order) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/out_of_order.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-2.991600f, 1.800000f, -0.081000f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-3.000000f, 1.800000f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-3.000000f, 1.800000f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-2.985000f, 1.921950f, 0.000000f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-2.976687f, 1.920243f, -0.081000f));
}

TEST_F(OBJReaderTest, simple_with_normals) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/simple_with_normals.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-3.00f, 1.80f, 0.00f));
	assertVectorExistsEquals(getVertexAt(*model, 0).normal, Vector3(5.00f, 4.50f, -5.14f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-1.23f, 3.80f, - 5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 1).normal, Vector3(3.00f, 3.50f, - 2.26f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 2).normal, Vector3(2.00f, 2.50f, 1.03f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 3).normal, Vector3(3.00f, 3.50f, - 2.26f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-1.23f, 3.80f, -5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 4).normal, Vector3(5.00f, 4.50f, -5.14f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-1.00f, 2.80f, 6.00f));
	assertVectorExistsEquals(getVertexAt(*model, 5).normal, Vector3(1.23f, 7.50f, 1.00f));
}

TEST_F(OBJReaderTest, simple_with_uvs) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/simple_with_uvs.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-3.00f, 1.80f, 0.00f));
	assertVectorExistsEquals(getVertexAt(*model, 0).uv, Vector2(5.00f, 4.50f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-1.23f, 3.80f, -5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 1).uv, Vector2(3.00f, 3.50f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 2).uv, Vector2(2.00f, 2.50f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 3).uv, Vector2(3.00f, 3.50f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-1.23f, 3.80f, -5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 4).uv, Vector2(5.00f, 4.50f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-1.00f, 2.80f, 6.00f));
	assertVectorExistsEquals(getVertexAt(*model, 5).uv, Vector2(1.23f, 7.50f));
}

TEST_F(OBJReaderTest, simple_with_uvs_and_normals) {
	auto model = modelService->createFromOBJFile("../test/assets/obj_reader_test/simple_with_uvs_and_normals.obj");

	assertVectorExistsEquals(getVertexAt(*model, 0).position, Vector3(-3.00f, 1.80f, 0.00f));
	assertVectorExistsEquals(getVertexAt(*model, 0).uv, Vector2(5.00f, 4.50f));
	assertVectorExistsEquals(getVertexAt(*model, 0).normal, Vector3(5.00f, 6.10f, 3.13f));
	assertVectorExistsEquals(getVertexAt(*model, 1).position, Vector3(-1.23f, 3.80f, -5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 1).uv, Vector2(3.00f, 3.50f));
	assertVectorExistsEquals(getVertexAt(*model, 1).normal, Vector3(3.00f, 1.30f, 0.21f));
	assertVectorExistsEquals(getVertexAt(*model, 2).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 2).uv, Vector2(2.00f, 2.50f));
	assertVectorExistsEquals(getVertexAt(*model, 2).normal, Vector3(1.00f, 3.24f, - 6.12f));
	assertVectorExistsEquals(getVertexAt(*model, 3).position, Vector3(-5.00f, 4.80f, 1.12f));
	assertVectorExistsEquals(getVertexAt(*model, 3).uv, Vector2(3.00f, 3.50f));
	assertVectorExistsEquals(getVertexAt(*model, 3).normal, Vector3(3.00f, 1.30f, 0.21f));
	assertVectorExistsEquals(getVertexAt(*model, 4).position, Vector3(-1.23f, 3.80f, -5.43f));
	assertVectorExistsEquals(getVertexAt(*model, 4).uv, Vector2(5.00f, 4.50f));
	assertVectorExistsEquals(getVertexAt(*model, 4).normal, Vector3(1.00f, 3.24f, -6.12f));
	assertVectorExistsEquals(getVertexAt(*model, 5).position, Vector3(-1.00f, 2.80f, 6.00f));
	assertVectorExistsEquals(getVertexAt(*model, 5).uv, Vector2(1.23f, 7.50f));
	assertVectorExistsEquals(getVertexAt(*model, 5).normal, Vector3(1.23f, 1.80f, 2.43f));
}


int main(int argc, char** argv) {
   testing::InitGoogleMock(&argc, argv);
   return RUN_ALL_TESTS();
}