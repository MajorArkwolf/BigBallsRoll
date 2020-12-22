# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    #This thing goes brrrrrooooooooommmmmmmm
    main.c

    # helper
    Helper/token.c
    Helper/stringHelper.c
    Helper/stringPath.c

    # math

    # objloader
    ObjLoader/objLoader.c
    ObjLoader/model.c
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
