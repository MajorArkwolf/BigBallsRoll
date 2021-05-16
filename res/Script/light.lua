local Light = {}

function Light:Init(localLight)
    if (localLight == true) then
        self.id = LightRegister()
        self.localLight = true
    else
        self.id = 0
        self.localLight = false
    end
end

function Light:SetAmbient(x, y, z)
    self.ambient = {}
    self.ambient.x = x
    self.ambient.y = y
    self.ambient.z = z
    --LightAmbient(self.id, x, y, z)
end

function Light:SetDiffuse(x, y, z)
    if (self.localLight) then
        self.diffuse = {}
        self.diffuse.x = x
        self.diffuse.y = y
        self.diffuse.z = z
        --LightDiffuse(self.id, x, y, z)
    end
end

function Light:SetSpecular(x, y, z)
    if (self.localLight) then
        self.specular = {}
        self.specular.x = x
        self.specular.y = y
        self.specular.z = z
        --LightSpecular(self.id, x, y, z)
    end
end

function Light:SetPosition(x, y, z)
    if (self.localLight) then
        self.position = {}
        self.position.x = x
        self.position.y = y
        self.position.z = z
        --LightPosition(self.id, x, y, z)
    end
end

function Light:Disable()
    if (self.id > 0) then
        LightDisable(self.id)
    end
end

function Light:Enable()
    if (self.id == nil) then
        return
    end
    if (self.ambient ~= nil) then
        LightAmbient(self.id, self.ambient.x, self.ambient.y, self.ambient.z)
    end
    if (self.diffuse ~= nil) then
        LightDiffuse(self.id, self.diffuse.x, self.diffuse.y, self.diffuse.z)
    end
    if (self.specular ~= nil) then
        LightSpecular(self.id, self.specular.x, self.specular.y, self.specular.z)
    end
    if (self.position ~= nil) then
        LightPosition(self.id, self.position.x, self.position.y, self.position.z)
    end
end

return Light
