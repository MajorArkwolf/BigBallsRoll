function Init()
    mm_lights = {}
    mm_lights[1] = dofile("res/Script/light.lua")
    mm_lights[1]:Init(false)
    mm_lights[1]:SetAmbient(0.6, 0.6, 0.6)
    mm_lights[2] = dofile("res/Script/light.lua")
    mm_lights[2]:Init(true)
    mm_lights[2]:SetAmbient(0.8, 0.8, 0.8)
    mm_lights[2]:SetDiffuse(1.0, 1.0, 1.0)
    mm_lights[2]:SetSpecular(1.0, 1.0, 1.0)
    mm_lights[2]:SetPosition(0, 1, 0)
    local boardDimensions = {}
    boardDimensions.x = 20
    boardDimensions.y = -5
    boardDimensions.z = 20
    GenerateBoard(boardDimensions.x, boardDimensions.y, boardDimensions.z)
    local player = GameObjectRegister()
    GameObjectSetPosition(player, 0 + 0.5, boardDimensions.y + 1.5, 0 + 0.5)
    GameObjectSetModel(player, "Ball.obj")
    CameraSetPosition(0 + 0.5 - 2, 15, 0 + 0.5)
    CameraSetPitch(-85)
    CameraUpdateView()
    titleLogo = dofile("res/Script/logo.lua")
    titleLogo:Init(boardDimensions)
end

function MainMenuUpdate()
    titleLogo:Update(deltaTime)
end

function MainMenuDraw()

end

-- Generates a chess board with
function GenerateBoard(xLength, yHeight, zLength)
    local object = {}
    local board = {}
    local count = 1
    for x=1, xLength, 1 do
        for z=1, zLength, 1 do
            object = GameObjectRegister()
            GameObjectSetPosition(object, x - (xLength / 2), yHeight , z - (zLength / 2))
            local number = x + yHeight + z
            if (math.fmod(number, 2) == 0) then
                GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
            else
                GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
            end
            board[count] = object
            count = count + 1
        end
    end
    -- Left wall
    for x=1, xLength, 1 do
        local z = 1
        object = GameObjectRegister()
        GameObjectSetPosition(object, x - (xLength / 2), yHeight + 1, z - (zLength / 2))
        local number = x + z + yHeight + 1
        if (math.fmod(number, 2) == 0) then
            GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
        else
            GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
        end
        board[count] = object
        count = count + 1
    end
    -- Right wall
    for x=1, xLength, 1 do
        object = GameObjectRegister()
        GameObjectSetPosition(object, x - (xLength / 2), yHeight + 1, zLength - (zLength / 2))
        local number = x + zLength + yHeight + 1
        if (math.fmod(number, 2) == 0) then
            GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
        else
            GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
        end
        board[count] = object
        count = count + 1
    end
    -- Front wall
    for z=2, zLength - 1, 1 do
        local x = 1
        object = GameObjectRegister()
        GameObjectSetPosition(object, x - (xLength / 2), yHeight + 1, z - (zLength / 2))
        local number = x + z + yHeight + 1
        if (math.fmod(number, 2) == 0) then
            GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
        else
            GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
        end
        board[count] = object
        count = count + 1
    end
    --Back wall
    for z=2, zLength - 1, 1 do
        object = GameObjectRegister()
        GameObjectSetPosition(object, xLength - (xLength / 2), yHeight + 1, z - (zLength / 2))
        local number = xLength + z + yHeight + 1
        if (math.fmod(number, 2) == 0) then
            GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
        else
            GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
        end
        board[count] = object
        count = count + 1
    end
end

function MainMenuPause()
    for key, value in ipairs(mm_lights) do
        value:Disable()
    end
end

function MainMenuUnpause()
    for key, value in ipairs(mm_lights) do
        value:Enable()
    end
end
