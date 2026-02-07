
-- NOTE: CLove has 'different' API than Love. Be careful! 

box = {}
box.x = 100
box.y = 100
box.s = 32

function love.load()

end

function love.update(dt) 
    if love.joystick.isDown(0, "b", "dpright") then
        box.x = box.x + 100 * dt
    end
    if love.joystick.isDown(0, "x", "dpleft") then
        box.x = box.x - 100 * dt
    end
    if love.joystick.isDown(0, "y", "dpup") then
        box.y = box.y + 100 * dt
    end
    if love.joystick.isDown(0, "a", "dpdown") then
        box.y = box.y - 100 * dt
    end
    
    -- NOTE!
    -- RT & LT are being shown in this piece of code and can not be accesed
    -- differently at least using an XBox One controller.
    for i=1, love.joystick.getAxisCount(0) do
        local value = love.joystick.getAxis(0, i)
        if value ~= 0 then 
            print("detected movement: " .. value .. " on axis: " .. i)
        end
    end

end

function love.joystickpressed(id, button)
    if id == 0 then 
        -- add your logic
        print(button .. " has been just pressed!")
    end
end

function love.joystickreleased(id, button)
    if id == 0 then
        -- add your logic here
    end
end


function love.draw()

    love.graphics.rectangle("fill", box.x, box.y, box.s, box.s)

    local count = love.joystick.getCount(0)
    local name = love.joystick.getName(0)
    local isGamepad = tostring(love.joystick.isGamepad(0))
    local isConnected = tostring(love.joystick.isConnected(0))
  --  local getHatCount = love.joystick.getHatCount(0)
  --  local getHat = tostring(love.joystick.getHat(0, "d")) -- TYPE can be: u, d, l , r, ld (left down), lu, rd, du
  --  local getGamepadAxis = tostring(love.joystick.getGamepadAxis(0, "rightx"))
   
    
    love.graphics.print("You got: " .. count .. " connected device with status of connected: " .. isConnected .. " joystick/gamepad connected which \n are/are not gamepads: " .. isGamepad .. " by the name of: " .. name, 10, 300);

end
