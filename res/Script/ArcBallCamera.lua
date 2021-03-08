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

function ArcBallCamera:Update(deltaTime, trackingID)
    self.radius = self.radius + (MouseDeltaY * deltaTime * -1)
    if self.radius < 5 then
        self.radius = 5
    end
    local trackingPosition = GameObjectGetPosition(trackingID)
    local trackingRotation = GameObjectGetRotation(trackingID)
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
