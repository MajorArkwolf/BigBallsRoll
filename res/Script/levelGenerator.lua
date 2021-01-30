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

 function Generator:Setup(seed, xlength, ylength, zlength, tolerance)
    math.randomseed(seed)
     self.maxX = xlength
     self.maxY = ylength
     self.maxZ = zlength
    --Setup our primary data structure for a level.
    self.field = InitialiseField(xlength, ylength, zlength)

    --Generate our two main points that will be used to check to ensure we have our start and win condition
    self.startPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
    self.endPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
    local pointsAreNotApart = true

    while pointsAreNotApart do
        if math.abs(self.startPoint[1] - self.endPoint[1]) < tolerance or math.abs(self.startPoint[3] - self.endPoint[3]) < tolerance then
            self.endPoint = {math.random(1, xlength), math.random(1, ylength), math.random(1, zlength)}
        else
            pointsAreNotApart = false
        end
    end
     self.field = RandomPath(self.startPoint, self.endPoint, xlength, ylength, zlength, self.field)
end

function GetRandomDirection()
    local direction = {}
    direction.x = {}
    direction.z = {}
    local dir = math.random(1, 4)
    if (dir == 1) then
        --north
        direction.x = 1
        direction.z = 0
    elseif (dir == 2) then
        --east
        direction.x = 0
        direction.z = 1
    elseif (dir == 3) then
        --south
        direction.x = -1
        direction.z = 0
    else
        --west
        direction.x = 0
        direction.z = -1
    end
    return direction
end

function RotateDirection(direction)
    direction.x = direction.x + 1
    if (direction.x > 1) then
        direction.x = -1
    end

    direction.z = direction.z + 1
    if (direction.z > 1) then
        direction.z = -1
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
        count = 0
        dir = GetRandomDirection()
        while (count <= 4) do
            x = dir.x + currentNode[1]
            y = currentNode[2]
            z = dir.z + currentNode[3]
            if (x > 0 and y > 0 and  z > 0 and x <= gridMaxX and y <= gridMaxY and z <= gridMaxZ) then
                local nextNode = {x, y, z}
                if (not HasBeenVisited(nextNode) and NextNode(nextNode, endNode, gridMaxX, gridMaxY, gridMaxZ)) then
                    pathLength = pathLength + 1
                    path[pathLength] = nextNode
                    return true
                end
            end
            dir = RotateDirection(dir)
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
    return field
end

function Generator:RegisterGameObjects()
    for keyx, valuex in ipairs(self.field) do
        for keyy, valuey in ipairs(valuex) do
            for keyz, valuez in ipairs(valuey) do
                if (valuez == true) then
                    object = GameObjectRegister()
                    GameObjectSetPosition(object, keyx, keyy, keyz)
                    local total = keyx + keyy + keyz
                    if (keyx == self.startPoint[1] and keyy == self.startPoint[2] and keyz == self.startPoint[3]) then
                        GameObjectSetModel(object, "Off/redcube.off")
                    elseif (keyx == self.endPoint[1] and keyy == self.endPoint[2] and keyz == self.endPoint[3]) then
                        GameObjectSetModel(object, "Off/greencube.off")
                    elseif (math.fmod(total, 2) == 0) then
                        GameObjectSetModel(object, "Off/bluecube.off")
                    else
                        GameObjectSetModel(object, "Off/darkbluecube.off")
                    end
                end
            end
        end
    end
end

return Generator