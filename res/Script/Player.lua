local Player = {}

function Player:Init(position)
    self.gameObjectID = GameObjectRegister()
    self.position = position
    GameObjectSetPosition(self.gameObjectID, position.x, position.y, position.z)
    GameObjectSetModel(self.gameObjectID, "Ball.obj")
    self.camera = dofile("res/Script/ArcBallCamera.lua")
    self.camera:Init(20)
    self.camera:Update(0.0, self.gameObjectID)
    self.forward = false
    self.backward = false
    self.left = false
    self.right = false
    self.playerMoveOn = false
    self.rotatePlayerOn = false
    self.velocity = 4
    self.mouseSensitivityX = 3
    self.mouseSensitivityY = 3
end

function Player:ReInit()
    self.gameObjectID = GameObjectRegister()
    GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    GameObjectSetRotation(self.gameObjectID, self.rotation.x, self.rotation.y, self.rotation.z)
    GameObjectSetModel(self.gameObjectID, "Ball.obj")
    self.camera:Update(0.0, self.gameObjectID)
end

function CalculateRightVector(front)
    local result = NormaliseVec(front)
    return CrossProductVec(result, worldUp)
end

function Player:Fall(deltaTime)
    self.position = GameObjectGetPosition(self.gameObjectID)
    self.position.y = self.position.y - (7 * deltaTime)
    GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
end

function Player:Move(deltaTime)
    local front = {}
    front.x = math.sin(math.rad(self.rotation.y))
    front.y = 0.0
    front.z = math.cos(math.rad(self.rotation.y))
    local rightNormal = CalculateRightVector(front)
    if self.forward == true then
        self.position.x = self.position.x + (front.x * self.velocity * deltaTime)
        self.position.z = self.position.z + (front.z * self.velocity * deltaTime)
    end
    if self.backward == true then
        self.position.x = self.position.x + (front.x * self.velocity * deltaTime * -1)
        self.position.z = self.position.z + (front.z * self.velocity * deltaTime * -1)
    end
    if self.right == true then
        self.position.x = self.position.x + (rightNormal.x * self.velocity * deltaTime * -1)
        self.position.z = self.position.z + (rightNormal.z * self.velocity * deltaTime * -1)
    end
    if self.left == true then
        self.position.x = self.position.x + (rightNormal.x * self.velocity * deltaTime)
        self.position.z = self.position.z + (rightNormal.z * self.velocity * deltaTime)
    end
end

function Player:Update(deltaTime)
    self.position = GameObjectGetPosition(self.gameObjectID)
    self.rotation = GameObjectGetRotation(self.gameObjectID)
    if self.rotatePlayerOn then
        self.rotation.y = self.rotation.y + (MouseDeltaX * deltaTime * self.mouseSensitivityX)
    end
    if self.playerMoveOn then
        self:Move(deltaTime)
    end
    GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    GameObjectSetRotation(self.gameObjectID, self.rotation.x, self.rotation.y, self.rotation.z)
    self.camera:Update(deltaTime, self.gameObjectID, self.mouseSensitivityY)
end

return Player
