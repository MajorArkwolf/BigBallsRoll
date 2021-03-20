#pragma once
#include <exotic/cester.h>
#include "ObjLoader/model.h"
#include "ObjLoader/modelLoader.h"

/*
 * This will load a known model with known information to test if the model loading is working correct.
 */

CESTER_TEST(obj_vert_test, inst,
            Model model = ModelLoader_loadModel("", "Obj/cube.obj");
            cester_assert_true(8 == model.Mesh[0].NumOfVert);
            cester_assert_float_eq(0.0f, model.Mesh[0].Vertices[0].X);
            cester_assert_float_eq(0.0f, model.Mesh[0].Vertices[1].Y);
            cester_assert_float_eq(1.0f, model.Mesh[0].Vertices[2].Z);
            cester_assert_float_eq(1.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].X);
            cester_assert_float_eq(0.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].Y);
            cester_assert_float_eq(0.0f, model.Mesh[0].Vertices[model.Mesh[0].NumOfVert - 1].Z);
)

CESTER_TEST(obj_face_test, inst,
            Model model = ModelLoader_loadModel("", "Obj/cube.obj");
            cester_assert_int_eq(12, model.Mesh[0].NumOfFaces);
            cester_assert_int_eq(3, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].NumFaces);
            cester_assert_int_eq(4, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[0].VertexID);
            cester_assert_int_eq(0, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[1].VertexID);
            cester_assert_int_eq(2, model.Mesh[0].Faces[model.Mesh[0].NumOfFaces -1].Point[2].VertexID);
)

CESTER_TEST(obj_normal_test, inst,
            Model model = ModelLoader_loadModel("", "Obj/cube.obj");
            cester_assert_true(24 == model.Mesh[0].NumOfNormals);
)
