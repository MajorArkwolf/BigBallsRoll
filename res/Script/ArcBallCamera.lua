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
    self.rotationAround = self.rotationAround + (MouseDeltaX * deltaTime)
    self.radius = self.radius + (MouseDeltaY * deltaTime * -1)
    local trackingPosition = GameObjectGetPosition(trackingID)
    local trackingRotation = GameObjectGetRotation(trackingID)
    local theta = trackingRotation[2] + self.rotationAround
    local horizontalDistance = CalculateHorizontalDistance(self.radius, self.pitch)
    local offsetX = horizontalDistance * math.sin(math.rad(theta))
    local offsetZ = horizontalDistance * math.cos(math.rad(theta))
    local xFinalPosition = trackingPosition[1] - offsetX
    local yFinalPosition = trackingPosition[2] + CalculateVerticalDistance(self.radius, 20)
    local zFinalPosition = trackingPosition[3] - offsetZ
    CameraSetPosition(xFinalPosition, yFinalPosition, zFinalPosition)
    CameraSetPitch(self.pitch)
    CameraSetYaw(90  - theta)
    CameraUpdateView()
end

return ArcBallCamera