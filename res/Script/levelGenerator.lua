local Generator = {}

function InitialiseField(xlength, ylength, zlength)
    local field = {}
    for x=1, xlength, 1
    do
        field[x] = {}
        for y = 1, ylength, 1
        do
            field[x][y] = {}
            for z = 1, zlength, 1
            do
                field[x][y][z] = false
            end
        end
    end
    return field
end

function Generator:Init(seed)
    math.randomseed(seed)
end

function Generator:Setup(xlength, ylength, zlength, tolerance)
   diagnialEnabled = false
   if xlength <= tolerance then
       xlength = tolerance * 2
   end
   if zlength <= tolerance then
       zlength = tolerance * 2
   end

   self.maxX = xlength
   self.maxY = ylength
   self.maxZ = zlength
   --Setup our primary data structure for a level.
   self.field = InitialiseField(xlength, ylength, zlength)

   --Generate our two main points that will be used to check to ensure we have our start and win condition
   self.startPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
   self.endPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
   local pointsAreNotApart = true
   count = 0
   while pointsAreNotApart do
       if math.abs(self.startPoint[1] - self.endPoint[1]) < tolerance or math.abs(self.startPoint[3] - self.endPoint[3]) < tolerance then
           self.endPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
       else
           pointsAreNotApart = false
       end
       count = count + 1
       if count > 10 then
           self.startPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
           count = 0
       end
   end
   self.field = RandomPath(self.startPoint, self.endPoint, xlength, ylength, zlength, self.field)
end

function GetRandomDirection()
    local direction = {}
    direction.x = 0
    direction.y = 0
    direction.z = 0
    local dir = math.random(1, 6)
    if (dir == 1) then
        --north
        direction.x = 1
    elseif (dir == 2) then
        --east
        direction.z = 1
    elseif (dir == 3) then
        --south
        direction.x = -1
    elseif (dir == 4) then
        --west
        direction.z = -1
    elseif (dir == 5) then
        --up
        direction.y = 1
    else
        --down
        direction.y = -1
    end
    return direction
end

function RotateDirection(direction)
    if (diagnialEnabled) then
        direction.x = direction.x + 1
        if (direction.x > 1) then
            direction.x = -1
        end

        direction.z = direction.z + 1
        if (direction.z > 1) then
            direction.z = -1
        end
    else
        local nextDir = math.random(1, 2)
        if (nextDir == 1) then
            direction.x = direction.x + 1
            if (direction.x > 1) then
                direction.x = -1
            end
        else
            direction.z = direction.z + 1
            if (direction.z > 1) then
                direction.z = -1
            end
        end
    end
    return direction
end

function AlterHeight(direction)
    direction.y = direction.y + 1
    if (direction.y > 1) then
        direction.y = -1
    end
    return direction
end

function HasBeenVisited(currentNode)
    for x = 1, visitedLength, 1 do
        if (currentNode[1] == visited[x][1] and currentNode[2] == visited[x][2] and currentNode[3] == visited[x][3]) then
            return true
        end
    end
    return false
end

function ClearBlocks(currentNode, field, gridMaxY)
    for x = currentNode[2] + 1, gridMaxY, 1 do
        field[currentNode[1]][x][currentNode[3]] = false
    end
    for x = currentNode[2] - 1, 1, -1 do
        field[currentNode[1]][x][currentNode[3]] = false
    end
    return field
end

function NextNode(currentNode, endNode, gridMaxX, gridMaxY, gridMaxZ)
    --If we have found the end node
    if (currentNode[1] == endNode[1] and currentNode[2] == endNode[2] and currentNode[3] == endNode[3]) then
        pathLength = pathLength + 1
        path[pathLength] = currentNode
        return true
    end
    -- add the node onto our visited list
    visitedLength = visitedLength + 1
    visited[visitedLength] = currentNode

    while(true) do
        local count = 0
        local dir = GetRandomDirection()
        while (count <= 6) do
            local x = dir.x + currentNode[1]
            local y = dir.y + currentNode[2]
            local z = dir.z + currentNode[3]
            if (x > 0 and y > 0 and  z > 0 and x <= gridMaxX and y <= gridMaxY and z <= gridMaxZ) then
                local nextNode = {x, y, z}
                if (not HasBeenVisited(nextNode) and NextNode(nextNode, endNode, gridMaxX, gridMaxY, gridMaxZ)) then
                    pathLength = pathLength + 1
                    path[pathLength] = nextNode
                    return true
                end
            end
            dir = RotateDirection(dir)
            if (y < 1 or y > gridMaxY) then
                dir = AlterHeight(dir)
            end
            count = count + 1
        end
        count = 0
        return false
    end
    return false
end

function RandomPath(startPoint, endPoint, gridMaxX, gridMaxY, gridMaxZ, field)
    path = {}
    pathLength = 0
    visited = {}
    visitedLength = 0
    -- add the node onto our visited list
    pathLength = pathLength + 1
    path[pathLength] = startPoint
    result = NextNode(startPoint, endPoint, gridMaxX, gridMaxY, gridMaxZ)
    for key, value in ipairs(path) do
        field[value[1]][value[2]][value[3]] = true
    end
    field = ClearBlocks(startPoint, field, gridMaxY)
    field = ClearBlocks(endPoint, field, gridMaxY)
    return field
end

function Generator:RegisterGameObjects()
    self.boardID = {}
    self.boardID[1] = 0
    local id = 2
    for keyx, valuex in ipairs(self.field) do
        for keyy, valuey in ipairs(valuex) do
            for keyz, valuez in ipairs(valuey) do
                if (valuez == true) then
                    local object = GameObjectRegister()
                    GameObjectSetPosition(object, keyx, keyy, keyz)
                    --Register Physics for gameobjects
                    PhysicsRegisterCollisionBody(object)
                    PhysicsCollisionBodySetStatic(object, true)
                    PhysicsSetMass(object, 0)
                    PhysicsSetPosition(object, keyx, keyy, keyz)
                    local position = {}
                    position.x = 0
                    position.y = 0
                    position.z = 0
                    local rotation = {}
                    rotation.x = 0
                    rotation.y = 0
                    rotation.z = 0
                    local length = {}
                    length.x = 1
                    length.y = 1
                    length.z = 1
                    PhysicsAddAABBCollider(object, position, length)
                    local total = keyx + keyy + keyz
                    if (keyx == self.startPoint[1] and keyy == self.startPoint[2] and keyz == self.startPoint[3]) then
                        GameObjectSetModel(object, "Obj/Terrain/redcube.obj")
                        self.boardID[id] = object
                        id = id + 1
                    elseif (keyx == self.endPoint[1] and keyy == self.endPoint[2] and keyz == self.endPoint[3]) then
                        GameObjectSetModel(object, "Obj/Terrain/greencube.obj")
                        self.boardID[1] = object
                    elseif (math.fmod(total, 2) == 0) then
                        GameObjectSetModel(object, "Obj/Terrain/lightbluecube.obj")
                        self.boardID[id] = object
                        id = id + 1
                    else
                        GameObjectSetModel(object, "Obj/Terrain/darkbluecube.obj")
                        self.boardID[id] = object
                        id = id + 1
                    end
                end
            end
        end
    end
end

return Generator
