local StartNode = {}

function round(x)
    return x>=0 and math.floor(x+0.5) or math.ceil(x-0.5)
end

function StartNode:Init(x, y, z, board)
    self.position = {}
    self.position.x = x
    self.position.y = y
    self.position.z = z
    self.playerStarted = false
    self.boardIsReady = false
    self.board = board
    self.countBoardId = 1
end

function StartNode:FreshBoard(height, player, endNode)
    -- Hide the board
    DisableBoard(self.board)
    -- Create a fake end block to make it seem like the player never moved.
    self.oldEndBlock = GameObjectRegister()
    GameObjectSetModel(self.oldEndBlock, "Obj/Terrain/greencube.obj")
    -- Set the end position above the start position
    local position = {}
    position.x = self.position.x
    position.y = self.position.y + height
    position.z = self.position.z
    GameObjectSetPosition(self.oldEndBlock, position.x, position.y, position.z)
    -- Calculate how far the player was roughly hanging of the square and place them back.
    local offsetFromFinish = {}
    offsetFromFinish.x = player.position.x - endNode.position.x
    offsetFromFinish.y = 0
    offsetFromFinish.z = player.position.z - endNode.position.z
    local newPlayerPositions = {}
    newPlayerPositions.position = {}
    newPlayerPositions.respawnPosition = {}
    newPlayerPositions.position.x = position.x + offsetFromFinish.x
    newPlayerPositions.position.y = position.y + 1.325
    newPlayerPositions.position.z = position.z + offsetFromFinish.z
    newPlayerPositions.respawnPosition.x = newPlayerPositions.position.x
    newPlayerPositions.respawnPosition.y = self.position.y + 1.325
    newPlayerPositions.respawnPosition.z = newPlayerPositions.position.z
    return newPlayerPositions
end

function DisableBoard(board)
    for key, id in ipairs(board) do
        GameObjectToggleRender(id, true)
    end
end

function StartNode:EnableBlock()
    if (#self.board + 1 ~= self.countBoardId) then
        GameObjectToggleRender(self.board[self.countBoardId], false)
        self.countBoardId = self.countBoardId + 1
        return false
    end
    -- TODO: Add a delete call on this object so that the physics is disabled.
    GameObjectToggleRender(self.oldEndBlock, true)
    return true
end

function StartNode:CheckStartTrigger(player, deltaTime)
    -- Check to see if the player has landed, if not the player is still falling
    if (not self.boardIsReady) then
        self.boardIsReady = self:EnableBlock()
        PhysicsSleepWorld(true)
    elseif (not self.playerStarted) then
        PhysicsSleepWorld(false)
        if(player.position.y < self.position.y + 1.6) then
            player.playerMoveOn = true;
            self.playerStarted = true
        end
    end
    return self.playerStarted
end

return StartNode
