local EndNode = {}

--GameObjectToggleRender

function EndNode:Init(x, y, z, board)
    self.position = {}
    self.position.x = x
    self.position.y = y
    self.position.z = z
    self.width = 0
    self.board = board
    self.finishedLevel = false
    self.endLevelSound = "levelcomplete.ogg"
    self.flag = GameObjectRegister()
    GameObjectSetPosition(self.flag, x - 0.35, y + 2.345, z + 0.25)     -- centered
    GameObjectSetModel(self.flag, "Obj/Flag.obj")
end

function EndNode:DestroyRandomBlock()
    if (#self.board > 1) then
        local idToDelete = math.random(#self.board)
        if idToDelete == 1 then
            return false
        end
        GameObjectToggleRender(self.board[idToDelete], true)
        table.remove(self.board, idToDelete)
        return false
    end
    --GameObjectToggleRender(self.board[1], true)
    --table.remove(self.board, 1)
    return true
end

function EndNode:CheckEndTrigger(player)
    if (self.position.y <= player.position.y) then  -- Check player isn't under node
        if (self.position.x < player.position.x + self.width and self.position.x + 1 > player.position.x) then
            if (self.position.z < player.position.z + self.width and self.position.z + 1 > player.position.z) then
                return true
            end
        end
    end
    return false
end

function EndNode:BeginEndStep(player)
    if (self.finishedLevel == false) then
        AudioPlaySound(self.gameObjectID, self.endLevelSound, false)
        AudioSetSourceVolume(self.gameObjectID, 100)
        self.finishedLevel = true
        player.playerMoveOn = false
        PhysicsStopCB(player.gameObjectID)
        self:CentrePlayer(player)
        PhysicsSleepWorld(true)
    end
end

function EndNode:CentrePlayer(player)
    GameObjectToggleRender(self.flag, true)
    player.position = GameObjectGetPosition(player.gameObjectID)
    player.position.x = self.position.x + 0.5
    player.position.y = self.position.y + 1.5
    player.position.z = self.position.z + 0.5
    GameObjectSetPosition(player.gameObjectID, player.position.x, player.position.y, player.position.z)
end

return EndNode
