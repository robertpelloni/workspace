--[[
--
--Read pixel information from an image and do something with it ;)
--
--]]
--
local t = {}
function spawn(x,y)
	table.insert(t,{x=x,y=y})
end

local dr = nil
function love.load()
	--love.graphics.scale(2.4)

	--read each pixel color and something based on that
	local im = love.image.newImageData("map.png")

	for y = 1, im:getHeight() do
		for x = 1, im:getWidth() do
			-- pixel coordinates range from 0 to image width - 1 / height - 1
			local r, g, b, a, pixel= im:getPixel( x, y)
			if r == 55 and g == 50 and b == 227 then
				--print(x .. " " .. y)
				spawn(x,y)
			end
		end
	end

	-- set pixels to a custom color
	local data = love.image.newImageData(132,132)
	for i=1,data:getHeight() do
		for k=1,data:getWidth() do
			data:setPixel(i,k,155,255,355,255)
		end
	end

	data:setPixel(60,60,255,0,0,255)
	data:setPixel(61,60,255,0,0,255)
	data:setPixel(60,61,255,0,0,255)
	data:setPixel(61,61,255,0,0,255)

	data:encode("tga","testga.tga")
	data:encode("png","testpng.png")
	data:encode("bmp","testbmp.bmp")
	data:encode("hdr","testhdr.hdr")
	--load the newly made texture with custom colors and size and draw to it
	--love.draw
	dr = love.graphics.newImage(data)
	dr:setFilter("nearest","nearest")
end

function love.update(dt)
	local mx = love.mouse.getX()
	local my = love.mouse.getY()

	if love.keyboard.isDown("esc") then
		love.event.quit()
	end
end

function love.draw()
	for i,v in ipairs(t) do
		love.graphics.rectangle("fill",v.x*16,v.y*16,16,16)
	end
	love.graphics.draw(dr,200,100)
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
