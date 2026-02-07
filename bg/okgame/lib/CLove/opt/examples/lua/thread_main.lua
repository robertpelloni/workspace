
--[[
--
-- Note: Threads in CLove are totally different then in Love
--
--]]

thread, love.thread.newThread("test.lua", "nameit") 
function love.load()
  require("test")     
end

function love.update(dt)
    if love.keyboard.isDown("esc") then
        love.event.quit()
    end
end
