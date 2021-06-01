local BallSpawner = {}

function BallSpawner:Init(position, modelName)
    self.position = position
    self.modelName = modelName
    self.timer = 0
    self.activated = false

end

function BallSpawner:Configure(amountOfBalls, force, coneSpread, timeBetweenSpawn, sizeOfBall)
    self.amountOfBalls = amountOfBalls
    self.force = force
    self.coneSpread = coneSpread
    self.timeBetweenSpawn = timeBetweenSpawn
    self.sizeOfBall = sizeOfBall
    self.ballArray = {}
end

function BallSpawner:Activate(isActivate)
    self.activated = isActivate
end

function BallSpawner:Update(deltaTime)
    if (self.activated and #self.ballArray < self.amountOfBalls) then
        self.timer = self.timer + deltaTime
        if (self.timer > self.timeBetweenSpawn) then
            self:SpawnBall(self.position, self.sizeOfBall, 1, self.force, self.coneSpread)
            self.timer = 0
        end
    end
end

function BallSpawner:SpawnBall(position, size, mass, force, coneSpread)
    local object = GameObjectRegister()
    self.ballArray[#self.ballArray + 1] = object
    GameObjectSetPosition(object, position.x, position.y, position.z)
    GameObjectSetScale(object, size, size, size)
    GameObjectSetModel(object, self.modelName)
    self:AddPhysicsBody(object, position, size / 2, mass, force, coneSpread)
end

function BallSpawner:AddPhysicsBody(id, position, scale, mass, force, coneSpread)
    --Register Physics
    PhysicsRegisterCollisionBody(id)
    PhysicsSetPosition(id, position.x, position.y, position.z)
    local localPosition = {}
    localPosition.x = 0
    localPosition.y = 0
    localPosition.z = 0
    PhysicsAddSphereCollider(id, localPosition, scale)
    local randomForce = {}
    randomForce.y = 0
    randomForce.x = math.random(0, force) * math.random(-1 * coneSpread, coneSpread)
    randomForce.z = math.random(0, force) * math.random(-1 * coneSpread, coneSpread)
    PhysicsAddForce(id, randomForce)
    PhysicsSetMass(id, mass)
end

return BallSpawner
