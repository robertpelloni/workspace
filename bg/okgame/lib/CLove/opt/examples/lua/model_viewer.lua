--[[
-- Takes a sprite sheet and transforms it into a model. 
--]]

model_viewer = {}
model_viewer.__index = model_viewer 

function model_viewer.create(image, nearest, qW, qH, scale)
    local self = {}
    setmetatable(self, model_viewer)

    self.image = image
    if (nearest) then
        self.image:setFilter("nearest","nearest")
    end
    self.quadWidth = qW or self.image:getHeight()
    self.quadHeight = qH or self.quadWidth
    self.quads = {}

    local steps = self.image:getWidth()/self.quadWidth
    for i=1,steps do
        self.quads[i] = love.graphics.newQuad((i-1)*self.quadWidth, 0, self.quadWidth, self.quadHeight, self.image:getWidth(), self.image:getHeight())
    end
    
    self.flip = false
    self.rotation = 0
    self.layer_spacing = math.floor(math.max(((self.quadWidth+self.quadHeight)/3)/#self.quads, 1)+.5)
    self.scale = scale or 100/math.max(self.quadWidth, #self.quads)

    return self
end

function model_viewer:draw(x, y, flip)
    self.flip = flip or false
    local sy = #self.quads/2 * self.layer_spacing * self.scale

    for i=1,#self.quads do
        local index = self.flip and #self.quads-i+1 or i
        for j=1,math.max(1,self.layer_spacing) * self.scale do
            love.graphics.draw(self.image, self.quads[index], 
            x, y+sy - i * self.scale * self.layer_spacing - j, 
            math.rad(self.rotation), self.scale, self.scale,
            self.quadWidth/2, self.quadHeight/2)
            if j>1 then break end
        end
    end
end

-- Getters and setters
-- 
function model_viewer:setRotation(v)
    self.rotation = v
end

function model_viewer:getRotation()
    return self.rotation
end


