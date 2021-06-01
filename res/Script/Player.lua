local Player = {}

function Player:Init(position)
    self.gameObjectID = GameObjectRegister()
    self.position = position
    self.startPosition = position
    self.oldPosition = position
    GameObjectSetPosition(self.gameObjectID, position.x, position.y, position.z)
    self.rotation = GameObjectGetRotation(self.gameObjectID)
    GameObjectSetModel(self.gameObjectID, "Ball.obj")
    self.camera = dofile("res/Script/ArcBallCamera.lua")
    self.camera:Init(20)
    self.forward = false
    self.backward = false
    self.left = false
    self.right = false
    self.playerMoveOn = false
    self.rotatePlayerOn = false
    self.velocity = 10
    self.playerLives = 3
    self.mouseSensitivityX = 3
    self.mouseSensitivityY = 3
    self.isJumping = false
    self.camera:Update(0.0, self.gameObjectID, self.mouseSensitivityX, self.rotation)
    self:AddPhysicsBody()
end

function Player:AddPhysicsBody()
    --Register Physics
    PhysicsRegisterCollisionBody(self.gameObjectID)
    PhysicsSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    local position = {}
    position.x = 0
    position.y = 0
    position.z = 0
    PhysicsAddSphereCollider(self.gameObjectID, position, 0.5)
end

function Player:ReInit(newPlayerPositions)
    self.position = newPlayerPositions.position
    self.startPosition = newPlayerPositions.respawnPosition
    self.gameObjectID = GameObjectRegister()
    GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    GameObjectSetRotation(self.gameObjectID, self.rotation.x, self.rotation.y, self.rotation.z)
    GameObjectSetModel(self.gameObjectID, "Ball.obj")
    self:AddPhysicsBody()
    self:Update(0.0)
end

function CalculateRightVector(front)
    local result = NormaliseVec(front)
    return CrossProductVec(result, worldUp)
end

function Player:IsPlayerDead()
    if self.position.y < -20 then
        self.playerLives = self.playerLives - 1
        self.position = self.startPosition
        GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
        PhysicsStopCB(self.gameObjectID)
    end
    if self.playerLives <= 0 then
        return true
    else
        return false
    end
end

function Player:Move(deltaTime)
    local front = {}
    front.x = math.sin(math.rad(self.rotation.y))
    front.y = 0.0
    front.z = math.cos(math.rad(self.rotation.y))
    local rightNormal = CalculateRightVector(front)
    local force = {}
    force.x = 0.0
    force.y = 0.0
    force.z = 0.0
    if self.forward == true then
        force.x = (front.x * self.velocity)
        force.z = (front.z * self.velocity)
    end
    if self.backward == true then
        force.x = (front.x * self.velocity * -1)
        force.z = (front.z * self.velocity * -1)
    end
    if self.right == true then
        force.x = (rightNormal.x * self.velocity * -1)
        force.z = (rightNormal.z * self.velocity * -1)
    end
    if self.left == true then
        force.x = (rightNormal.x * self.velocity)
        force.z = (rightNormal.z * self.velocity)
    end
    if force.x ~= 0 or force.y ~= 0 or force.z ~= 0 then
        PhysicsAddForce(self.gameObjectID, force)
    end
end

function Player:RollBall(deltaTime)
    --local newVelocity = PhysicsGetVelocity(self.gameObjectID)
    --local circumferance = 2 * math.pi * 0.5
    local xDistance = self.position.x - self.oldPosition.x
    local zDistance = self.position.z - self.oldPosition.z
    self.oldPosition = self.position
    local rotation = GameObjectGetRotation(self.gameObjectID)
    rotation.x = rotation.x + ((zDistance / (2 * math.pi * 0.5)) * -360)
    rotation.z = rotation.z + ((xDistance / (2 * math.pi * 0.5)) * -360)
    rotation.x = math.fmod(rotation.x, 360)
    rotation.z = math.fmod(rotation.z, 360)
    GameObjectSetRotation(self.gameObjectID, rotation.x, rotation.y, rotation.z)
end

function Player:Update(deltaTime)
    self.position = GameObjectGetPosition(self.gameObjectID)
    if self.rotatePlayerOn or not PlayerConfig_mouseXLock then
        self.rotation.y = self.rotation.y + (MouseDeltaX * deltaTime * PlayerConfig_mouseXSensitivity)
    end
    if self.playerMoveOn then
        self:Move(deltaTime)
    end
    self:IsPlayerDead()
    self:RollBall(deltaTime)
    self.camera:Update(deltaTime, self.gameObjectID, PlayerConfig_mouseYSensitivity, self.rotation)
end

function Player:Jump()
    local currentVelocity = PhysicsGetVelocity(self.gameObjectID)
    if currentVelocity.y < 0.05 and currentVelocity.y >= 0.0 and self.isJumping == true then
        self.isJumping = false
    end
    if self.isJumping == false then
        local force = {}
        force.x = 0.0
        force.y = 500.0
        force.z = 0.0
        PhysicsAddForce(self.gameObjectID, force)
        AudioPlaySound(self.gameObjectID, "collision.ogg", false)
        AudioSetSourceVolume(self.gameObjectID, 100)
        self.isJumping = true
    end
end

return Player
