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
    if (self.position.x < player.position.x + self.width and self.position.x + 1 > player.position.x) then
        if (self.position.z < player.position.z + self.width and self.position.z + 1 > player.position.z) then
            self.finishedLevel = true
            player.playerMoveOn = false
            return true
        end
    end
    return false
end

return EndNode
