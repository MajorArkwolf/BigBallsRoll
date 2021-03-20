
function Init()
    worldUp = {}
    worldUp.x = 0.0
    worldUp.y = 1.0
    worldUp.z = 0.0
    gen = dofile("res/Script/levelGenerator.lua")
    timer = 0
    -- 0 = not running, 1 = running, 2 = done
    generation_running = 0
    level = 1
    gen:Init(seed)
    gen:Setup(50, 1, 50, 10)
    gen:RegisterGameObjects()
    local position = {}
    position.x = gen.startPoint[1] + 0.5
    position.y = gen.startPoint[2] + 1.5
    position.z = gen.startPoint[3] + 0.5
    player = dofile("res/Script/Player.lua")
    player:Init(position)
    player.playerMoveOn = true
    endNode = dofile("res/Script/EndNode.lua")
    endNode:Init(gen.endPoint[1], gen.endPoint[2], gen.endPoint[3], gen.boardID)
    startNode = dofile("res/Script/StartNode.lua")
    startNode:Init(gen.startPoint[1], gen.startPoint[2], gen.startPoint[3], gen.boardID)
    startNode.playerStarted = true
    startNode.boardIsReady = true
end

function NextLevel()
    while generation_running ~= 2 do
        GenerateNextLevel()
    end
    generation_running = 0
    -- This next function is a C API call
    GameNextLevel()
    gen:RegisterGameObjects()
    startNode:Init(gen.startPoint[1], gen.startPoint[2], gen.startPoint[3], gen.boardID)
    startNode:FreshBoard(5, player, endNode)
    endNode:Init(gen.endPoint[1], gen.endPoint[2], gen.endPoint[3], gen.boardID)
    player:ReInit()
    level = level + 1
end

function GenerateNextLevel()
    if generation_running == 0 then
        generation_running = 1
        co = coroutine.create(function ()
            gen:Setup(50, 1, 50, 10) end
        )
        coroutine.resume(co)
        return
    end
    if generation_running == 1 and coroutine.status(co) == "dead" then
        generation_running = 2
        return
    end
end

function Update()
    GenerateNextLevel()
    player:Update(deltaTime)
    if endNode:CheckEndTrigger(player) then
        if endNode:DestroyRandomBlock() then
            NextLevel()
        end
    else
        if startNode:CheckStartTrigger(player, deltaTime) then
            -- If game has started then let the timer continue
            timer = timer + deltaTime
        end
    end
end


function Draw()

end

function InputKeyboardDown(input)
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

function InputKeyboardUp(input)
    if input == 22 then
        player.forward = false
    elseif input == 18 then
        player.backward = false
    elseif input == 0 then
        player.left = false
    elseif input == 3 then
        player.right = false
    end
end

function InputMouseButton(button, buttonState)
    -- Left Mouse Button
    if button == 66 then

    end
    --Right Mouse Button
    if button == 67 then
        if buttonState == 1 then
            player.rotatePlayerOn = true
        else
            player.rotatePlayerOn = false
        end
    end
end
