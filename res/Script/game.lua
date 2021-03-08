
function Init()
    player = dofile("res/Script/Player.lua")
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

    player:Init(position)
end

function NextLevel()
    while generation_running ~= 2 do
        GenerateNextLevel()
    end
    generation_running = 0
    GameNextLevel()
    gen:RegisterGameObjects()
    local position = {}
    position.x = gen.startPoint[1] + 0.5
    position.y = gen.startPoint[2] + 1.5
    position.z = gen.startPoint[3] + 0.5
    player:Init(position)
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
    if timer > 5 then
        --NextLevel()
        timer = 0
    end
    timer = timer + deltaTime
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