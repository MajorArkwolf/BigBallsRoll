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
    self.pitch = -30
end

function ArcBallCamera:Update(deltaTime, trackingID)
    trackingPosition = GameObjectGetPosition(trackingID)
    trackingRotation = GameObjectGetRotation(trackingID)
    theta = trackingRotation[2] + self.rotationAround
    horizontalDistance = CalculateHorizontalDistance(self.radius, self.pitch)
    offsetX = horizontalDistance * math.sin(math.rad(theta))
    offsetZ = horizontalDistance * math.cos(math.rad(theta))
    xFinalPosition = trackingPosition[1] - offsetX
    zFinalPosition = trackingPosition[3] - offsetZ
    CameraSetPosition(xFinalPosition, CalculateVerticalDistance(self.radius, 20), zFinalPosition)
    CameraSetYaw(90  - theta)
    CameraSetPitch(self.pitch)
    CameraUpdateView()

end

return ArcBallCamera