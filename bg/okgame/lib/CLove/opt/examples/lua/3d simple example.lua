function love.load()
	love.window.setMode(800,600)
	-- camera type: 2d or 3d only 
	-- left is always 0
	-- right is the width of your window/ camera
	-- bottom is the height 
	-- top is 0
	-- zNear should be 0.1 if you do not know what that is
	-- zFar should be a greater value than 10 but leave it at 100
	-- love.graphics.setCamera("2d",0,800,600,0,0.1,100)

	-- camera type: 2d or 3d only
	-- FOV aka field of view 
	-- ratio: width / height, always 
	-- zNear
	-- zFar

	-- 2d camera is set by default in CLove
	love.graphics.setCamera("3d",65,800/600,1.0,300)

	-- lookAt is like gluLookAt. I only use it in 3D
	-- position X,Y,Z of camera 
	-- target's position 
	-- where to look up from, usually is 0,-1,0, at least that's how I know to use it
	love.graphics.lookAt(1.2,1.2,-140.2, 0,-20,20, 0, -1, 0);

	img = love.graphics.newImage("hey.png")
end

local rot = 0
local z = -300
local y = 0
local x = 0
function love.update(dt)
	if love.keyboard.isDown("esc") then love.event.quit() end 

	rot = rot + dt / 8

	if love.keyboard.isDown("w") then 
		z = z + 100 * dt 
	end

	if love.keyboard.isDown("s") then 
		z = z - 100 * dt 
	end

	if love.keyboard.isDown("d") then 
		x = x + 100 * dt 
	end

	if love.keyboard.isDown("a") then 
		x = x - 100 * dt 
	end
end

function love.wheelmoved(w)
	if w < 0 then 
		y = y - 10
	elseif w > 0 then 
		y = y + 10
	end
end

function love.draw()
	love.graphics.push()

	--translation now accepts Z but it's not necessary
	love.graphics.translate(x,y,z)
	
	-- same goes for scale
	--love.graphics.scale(6, 6, 6)
	
	--same goes for rotation but now you need to specify the angle and the axe: XYZ. The values can be only {-1,0,1} otherwhise you'll broke t
	--love.graphics.rotate(rot, 0, 1, 0)
	
	love.graphics.draw(img,30,30,rot)
	love.graphics.rectangle("fill",-5,-5,32,32)
	love.graphics.circle("fill",120,20,32,32)
	
	love.graphics.pop()
end