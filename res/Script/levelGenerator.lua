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
                field[x][y][z] = true
            end
        end
    end
    return field
end

 function Generator:Setup(seed, xlength, ylength, zlength, tolerance)
    math.randomseed(seed)
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
end

function Generator:RegisterGameObjects()
    counter = 0
    for keyx, valuex in ipairs(self.field) do
        for keyy, valuey in ipairs(valuex) do
            for keyz, valuez in ipairs(valuey) do
                if (valuez == true) then
                    object = GameObjectRegister()
                    GameObjectSetPosition(object, keyx, keyy, keyz)
                    if (keyx == self.startPoint[1] and keyy == self.startPoint[2] and keyz == self.startPoint[3]) then
                        GameObjectSetModel(object, "Off/redcube.off")
                    elseif (keyx == self.endPoint[1] and keyy == self.endPoint[2] and keyz == self.endPoint[3]) then
                        GameObjectSetModel(object, "Off/greencube.off")
                    elseif math.fmod(counter, 2) == 0 then
                        GameObjectSetModel(object, "Off/bluecube.off")
                    else
                        GameObjectSetModel(object, "Off/darkbluecube.off")
                    end
                    counter = counter + 1
                end
            end
        end
        counter = counter + 1
    end
end

return Generator