function Init()
    gen = dofile("res/Script/levelGenerator.lua")
    gen:Setup(1, 30, 1, 30, 5)
    gen:RegisterGameObjects()
    object = GameObjectRegister()
    GameObjectSetPosition(object, gen.startPoint[1] + 0.5, gen.startPoint[2] + 1.5, gen.startPoint[3] + 0.5)
    GameObjectSetModel(object, "Ball.obj")
end

function Update()

end

function Draw()

end
