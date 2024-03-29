local ArcBallCamera = {}

function CalculateHorizontalDistance(radius, pitch)
    return (radius * math.cos(math.rad(pitch)))
end

function CalculateVerticalDistance(radius, pitch)
    return (radius * math.sin(math.rad(pitch)))
end

function ArcBallCamera:Init(newRadius)
    self.radius = newRadius
    self.rotationAround = 0.0
    self.pitch = -20
end

function ArcBallCamera:Update(deltaTime, trackingID, mouseSensitivity, rotation)
    -- There is a chance that MouseDeltaY will not be set on first load
    -- however we need the camera to update to calculate its position, this stops a nil from occuring.
    if MouseDeltaY ~= nil then
        self.radius = self.radius + (MouseDeltaY * deltaTime * -1 * mouseSensitivity)
    end
    if self.radius < 5 then
        self.radius = 5
    end
    local trackingPosition = GameObjectGetPosition(trackingID)
    local trackingRotation = rotation
    local theta = trackingRotation.y + self.rotationAround
    local horizontalDistance = CalculateHorizontalDistance(self.radius, self.pitch)
    local offsetX = horizontalDistance * math.sin(math.rad(theta))
    local offsetZ = horizontalDistance * math.cos(math.rad(theta))
    local xFinalPosition = trackingPosition.x - offsetX
    local yFinalPosition = trackingPosition.y + CalculateVerticalDistance(self.radius, 20)
    local zFinalPosition = trackingPosition.z - offsetZ
    CameraSetPosition(xFinalPosition, yFinalPosition, zFinalPosition)
    CameraSetPitch(self.pitch)
    CameraSetYaw(90  - theta)
    CameraUpdateView()
end

return ArcBallCamera
