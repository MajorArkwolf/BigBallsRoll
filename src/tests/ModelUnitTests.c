#include "ModelUnitTests.h"
#include <unity.h>
#include "ObjLoader/model.h"
#include "ObjLoader/modelLoader.h"

void test_ModelLoader() {
    Model model = ModelLoader_loadModel("", "Obj/Terrain/cube.obj");
    TEST_ASSERT_TRUE(8 == model.Mesh[0].NumOfVert);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, model.Mesh[0].Vertices[0].X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, model.Mesh[0].Vertices[1].Y);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, model.Mesh[0].Vertices[2].Z);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].Z);
    TEST_ASSERT_EQUAL(12, model.Mesh[0].NumOfFaces);
    TEST_ASSERT_EQUAL(3, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].NumFaces);
    TEST_ASSERT_EQUAL(4, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[0].VertexID);
    TEST_ASSERT_EQUAL(0, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[1].VertexID);
    TEST_ASSERT_EQUAL(2, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[2].VertexID);
    TEST_ASSERT_TRUE(24 == model.Mesh[0].NumOfNormals);
}