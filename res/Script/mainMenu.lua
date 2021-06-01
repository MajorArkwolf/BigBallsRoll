function Init()
    mm_lights = {}
    mm_lights[1] = dofile("res/Script/light.lua")
    mm_lights[1]:Init(false)
    mm_lights[1]:SetAmbient(0.6, 0.6, 0.6)
    mm_lights[1]:Enable()
    mm_lights[2] = dofile("res/Script/light.lua")
    mm_lights[2]:Init(true)
    mm_lights[2]:SetAmbient(0.8, 0.8, 0.8)
    mm_lights[2]:SetDiffuse(1.0, 1.0, 1.0)
    mm_lights[2]:SetSpecular(1.0, 1.0, 1.0)
    mm_lights[2]:SetPosition(0, 1, 0)
    mm_lights[2]:Enable()
    local boardDimensions = {}
    boardDimensions.x = 20
    boardDimensions.y = -5
    boardDimensions.z = 20
    GenerateBoard(boardDimensions.x, boardDimensions.y, boardDimensions.z)
    CameraSetPosition(0 + 0.5 - 2, 15, 0 + 0.5)
    CameraSetPitch(-85)
    CameraUpdateView()
    titleLogo = dofile("res/Script/logo.lua")
    titleLogo:Init(boardDimensions)
    ballSpawner = dofile("res/Script/BallSpawner.lua")
    local ballSpawnerPos = {}
    ballSpawnerPos.x = 0
    ballSpawnerPos.y = 20
    ballSpawnerPos.z = 0
    ballSpawner:Init(ballSpawnerPos, "Ball.obj")
    ballSpawner:Configure(30, 100, 10, 0.5, 1)
    ballSpawner:Activate(true);
end

function MainMenuUpdate()
    titleLogo:Update(deltaTime)
    ballSpawner:Update(deltaTime)
end

function MainMenuDraw()

end

function MainMenuInputKeyboardDown(input)
    if input == 22 then
        player.forward = true
    elseif input == 18 then
        player.backward = true
    elseif input == 0 then
        player.left = true
    elseif input == 3 then
        player.right = true
    end
end

function MainMenuInputKeyboardUp(input)

end

function MainMenuInputMouseButton(button, buttonState)
    -- Left Mouse Button
    if button == 66 then

    end
    --Right Mouse Button
    if button == 67 then
        if buttonState == 1 then
            local ball_position = ballSpawner.position
            ballSpawner:SpawnBall(ball_position, 1, 300, 5)
        end
    end
end


function RegisterCollisionShape(id, position, scale)
    PhysicsRegisterCollisionBody(id)
    PhysicsCollisionBodySetStatic(id, true)
    PhysicsSetMass(id, 0)
    PhysicsSetPosition(id, position.x, position.y, position.z)
    local relativePosition = {}
    relativePosition.x = 0
    relativePosition.y = 0
    relativePosition.z = 0
    PhysicsAddAABBCollider(id, relativePosition, scale)
end

-- Generates a chess board with
function GenerateBoard(xLength, yHeight, zLength)
    local object = {}
    local position = {}
    local scale = {}
    scale.x = 1
    scale.y = 1
    scale.z = 1
    local board = {}
    local count = 1
    for x=1, xLength, 1 do
        for z=1, zLength, 1 do
            object = GameObjectRegister()
            position.x = x - (xLength / 2)
            position.y = yHeight
            position.z = z - (zLength / 2)
            GameObjectSetPosition(object, position.x, position.y, position.z)
            RegisterCollisionShape(object, position, scale)
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
        object = GameObjectRegister()
        position.x = x - (xLength / 2)
        position.y = yHeight + 1
        position.z = z - (zLength / 2)
        GameObjectSetPosition(object, position.x, position.y, position.z)
        RegisterCollisionShape(object, position, scale)
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
        position.x = x - (xLength / 2)
        position.y = yHeight + 1
        position.z = zLength - (zLength / 2)
        GameObjectSetPosition(object, position.x, position.y, position.z)
        RegisterCollisionShape(object, position, scale)
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
        position.x = x - (xLength / 2)
        position.y = yHeight + 1
        position.z = z - (zLength / 2)
        GameObjectSetPosition(object, position.x, position.y, position.z)
        RegisterCollisionShape(object, position, scale)
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
        position.x = xLength - (xLength / 2)
        position.y = yHeight + 1
        position.z = z - (zLength / 2)
        GameObjectSetPosition(object, position.x, position.y, position.z)
        RegisterCollisionShape(object, position, scale)
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
