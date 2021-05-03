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
