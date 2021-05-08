local Logo = {}

function Logo:Init(boardPosition)
    self.gameObjectID = GameObjectRegister()
    self.position = {}
    self.position.x = 0
    self.position.y = (boardPosition.y + 10)
    self.startingYPos = (boardPosition.y + 10)
    self.maxHeight = 3
    self.position.z = 1
    self.rotation = {}
    self.rotation.x = 3
    self.rotation.y = -90
    self.rotation.z = 0
    self.movingIn = true
    self.rotatingLeft = true
    GameObjectSetModel(self.gameObjectID, "Obj/Title.obj")
    AudioRegisterSource(self.gameObjectID)
    AudioPlaySound(self.gameObjectID, "trance.ogg", true)
    AudioSetSourceVolume(self.gameObjectID, 10)
    --PhysicsRegisterCollisionBody(self.gameObjectID)
    --PhysicsCollisionBodySetStatic(self.gameObjectID, true)
    --PhysicsSetMass(self.gameObjectID, 0)
    --PhysicsSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    --local length = {}
    --length.x = 2
    --length.y = 0.5
    --length.z = 3.2
    --local localPos = {}
    --localPos.x = -1
    --localPos.y = 0
    --localPos.z = -1.5
    --PhysicsAddAABBCollider(self.gameObjectID, localPos, length)
    self:ExitLogo(boardPosition)
end

function Logo:ExitLogo(boardDimensions)
    self.exitLogo = {}
    self.exitLogo.id = GameObjectRegister()
    self.exitLogo.position = {}
    self.exitLogo.position.x = -5
    self.exitLogo.position.y = boardDimensions.y + 10
    self.exitLogo.position.z = 1
    GameObjectSetPosition(self.exitLogo.id, self.exitLogo.position.x, self.exitLogo.position.y, self.exitLogo.position.z)
    GameObjectSetRotation(self.exitLogo.id, 0, -90, 0)
    GameObjectSetModel(self.exitLogo.id, "Obj/EscMenu.obj")
    PhysicsRegisterCollisionBody(self.exitLogo.id)
    PhysicsCollisionBodySetStatic(self.exitLogo.id, true)
    PhysicsSetMass(self.exitLogo.id, 0)
    PhysicsSetPosition(self.exitLogo.id, self.exitLogo.position.x, self.exitLogo.position.y, self.exitLogo.position.z)
    local length = {}
    length.x = 0.8
    length.y = 0.5
    length.z = 8
    local localPos = {}
    localPos.x = 0
    localPos.y = 0
    localPos.z = -4
    PhysicsAddAABBCollider(self.exitLogo.id, localPos, length)
end

function Logo:PivotLeftAndRight(deltaTime)
    -- Make it so we are dealing with nicer numbers
    local yRotNormalised = self.rotation.y + 90
    if(self.rotatingLeft) then
        yRotNormalised = yRotNormalised - 30 * deltaTime
    else
        yRotNormalised = yRotNormalised + 30 * deltaTime
    end
    if (math.abs(yRotNormalised) > 20) then
        self.rotatingLeft = not self.rotatingLeft
    end
    -- Revert it back to an actual number
    self.rotation.y = yRotNormalised - 90
end

function Logo:MoveInAndOut(deltaTime)
    local yHeight = self.position.y - self.startingYPos
    if(self.movingIn) then
        yHeight = yHeight + 1 * deltaTime
    else
        yHeight = yHeight - 1 * deltaTime
    end
    if (yHeight > self.maxHeight or ((yHeight + self.position.y) < self.startingYPos and not self.movingIn)) then
        self.movingIn = not self.movingIn
    end
    self.position.y = self.startingYPos + yHeight
end


function Logo:Update(deltaTime)
    self:MoveInAndOut(deltaTime)
    self:PivotLeftAndRight(deltaTime)
    GameObjectSetPosition(self.gameObjectID, self.position.x, self.position.y, self.position.z)
    GameObjectSetRotation(self.gameObjectID, self.rotation.x, self.rotation.y, self.rotation.z)
end

function Logo:Draw()

end

return Logo
