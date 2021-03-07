local Player = {}

function Player:Init(position)
    self.gameObjectID = GameObjectRegister()
    self.position = position
    GameObjectSetPosition(self.gameObjectID, position[1], position[2], position[3])
    GameObjectSetModel(self.gameObjectID, "Ball.obj")
    self.camera = dofile("res/Script/ArcBallCamera.lua")
    self.camera:Init(20)
    self.camera:Update(deltaTime, self.gameObjectID)
end

function Player:Update(deltaTime)
    self.position = GameObjectGetPosition(self.gameObjectID)
    self.rotation = GameObjectGetRotation(self.gameObjectID)
    self.rotation[2] = self.rotation[2] + (MouseDeltaX * deltaTime)
    local front = {}
    front.x = math.sin(math.rad(self.rotation[2])) * 1 * deltaTime
    front.z = math.cos(math.rad(self.rotation[2])) * 1 * deltaTime
    self.position[1] = self.position[1] + front.x
    self.position[3] = self.position[3] + front.z
    GameObjectSetPosition(self.gameObjectID, self.position[1], self.position[2], self.position[3])
    GameObjectSetRotation(self.gameObjectID, self.rotation[1], self.rotation[2], self.rotation[3])
    self.camera:Update(deltaTime, self.gameObjectID)
end

return Player
