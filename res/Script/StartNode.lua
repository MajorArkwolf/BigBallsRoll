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

function StartNode:FreshBoard(player)
    DisableBoard(self.board)
    self.oldEndBlock = GameObjectRegister()
    GameObjectSetModel(self.oldEndBlock, "Off/greencube.off")
    local position = {}
    position.x = self.position.x
    position.y = self.position.y + 20
    position.z = self.position.z
    GameObjectSetPosition(self.oldEndBlock, position.x, position.y, position.z)
    local offsetFromFinish = {}
    offsetFromFinish.x = player.position.x - round(player.position.x)
    offsetFromFinish.y = 0
    offsetFromFinish.z = player.position.z - round(player.position.z)
    player.position.x = position.x + offsetFromFinish.x
    player.position.y = position.y + 1.5
    player.position.z = position.z + offsetFromFinish.z
end

function DisableBoard(board)
    for key, id in ipairs(board) do
        GameObjectToggleRender(board[id], true)
    end
end

function StartNode:EnableBlock()
    if (#self.board + 1 ~= self.countBoardId) then
        GameObjectToggleRender(self.board[self.countBoardId], false)
        self.countBoardId = self.countBoardId + 1
        return false
    end
    GameObjectToggleRender(self.oldEndBlock, true)
    return true
end

function StartNode:CheckStartTrigger(player, deltaTime)
    if (not self.boardIsReady) then
        self.boardIsReady = self:EnableBlock()
    elseif (not self.playerStarted and player.position.y < self.position.y + 1.6) then
        player.position.y = 1.5
        player.playerMoveOn = true;
        self.playerStarted = true
    elseif (not self.playerStarted) then
        player:Fall(deltaTime)
    end
end

return StartNode
