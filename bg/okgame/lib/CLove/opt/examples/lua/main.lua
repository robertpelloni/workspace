local image = nil
local batch = nil

local how_much = 2000 -- CHANGE THIS AS YOU LIKE TO TEST THE FPS

local use_batch = true -- SWITCH THIS TO SEE THE DIFFERENCE

function love.load()
    image = love.graphics.newImage("hey.png")

    if use_batch then
        batch = love.graphics.newSpriteBatch(image, how_much)
        setupSpriteBatch()
    end
end

function love.update(dt)
    if love.keyboard.isDown("esc") then
        print("Closing!")
        love.event.quit()
    end

    if use_batch then
        setupSpriteBatch()
    end
end

function setupSpriteBatch()
    batch:clear()
    for i=1,how_much do
        batch:add( math.random(0,love.window.getWidth()), math.random(0,love.window.getHeight()) )

    end
end

function love.draw()
    -- love.graphics.rectangle("fill", 100, 100, 100, 100)
    if not use_batch then
        for i=1,how_much do
            love.graphics.draw(image, math.random(0,love.window.getWidth()), math.random(0,love.window.getHeight()) )
        end
    else
        love.graphics.draw(batch)
    end

    love.graphics.print(""..love.timer.getFPS(),10,10)
end

function love.keypressed(k)
end

function love.quit()
end

function love.mousepressed(x,y,b)
end

function love.wheelmoved(y)
end
