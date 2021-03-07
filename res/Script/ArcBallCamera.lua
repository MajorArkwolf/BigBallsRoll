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
    --self.pitch = self.pitch + (MouseDeltaY * deltaTime * -1)
    trackingPosition = GameObjectGetPosition(trackingID)
    trackingRotation = GameObjectGetRotation(trackingID)
    theta = trackingRotation[2] + self.rotationAround
    horizontalDistance = CalculateHorizontalDistance(self.radius, self.pitch)
    offsetX = horizontalDistance * math.sin(math.rad(theta))
    offsetZ = horizontalDistance * math.cos(math.rad(theta))
    xFinalPosition = trackingPosition[1] - offsetX
    zFinalPosition = trackingPosition[3] - offsetZ
    CameraSetPosition(xFinalPosition, CalculateVerticalDistance(self.radius, 20), zFinalPosition)
    CameraSetPitch(self.pitch)
    CameraSetYaw(90  - theta)
    CameraUpdateView()
end

return ArcBallCamera