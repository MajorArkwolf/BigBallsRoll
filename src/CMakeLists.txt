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
    Math/extraMath.c

    # Objloader
    ObjLoader/modelLoader.c
    ObjLoader/objLoader.c
    ObjLoader/model.c

    # Engine
    Engine/engine.c
    Engine/camera.c
    Engine/stateManager.c
    Engine/gameObject.c
    Engine/modelManager.c
    Engine/InputManager.c
    Engine/textureManager.c
    ## Audio
    Engine/Audio/sound.c
    Engine/Audio/audioEngine.c
    Engine/Audio/audioManager.c

    #Scenes
    Scene/MainMenu/MainMenu.c
    Scene/LevelOne/LevelOne.c
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
