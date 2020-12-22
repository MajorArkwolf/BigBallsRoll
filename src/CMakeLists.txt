# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    #This thing goes brrrrrooooooooommmmmmmm
    main.c

    # Helper
    Helper/token.c
    Helper/stringHelper.c
    Helper/stringPath.c

    # Math
    Math/vectorMath.c
    Math/vec3.c
    Math/transform.c

    # Objloader
    ObjLoader/objLoader.c
    ObjLoader/model.c

    # Engine
    Engine/camera.c
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
