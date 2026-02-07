local debug, print = debug, print

local cloveErrorResult = false
local cloveErrorMessage = nil

require "main"

local function error_printer(msg, layer)
	cloveErrorMessage = (debug.traceback("Error: " .. tostring(msg), 1+(layer or 1)):gsub("\n[^\n]+$", ""))
	print((debug.traceback("Error: " .. tostring(msg), 1+(layer or 1)):gsub("\n[^\n]+$", "")))
end

local function deferErrhand(...)
	local handler = error_printer
	return handler(...)
end

function cloveHandleErrors()
	if cloveErrorMessage ~= nil then 
		love.graphics.setBackgroundColor(89, 157, 220)
		love.graphics.setColor(255,255,255,255)
		local err = {}
		local trace = debug.traceback()

		table.insert(err, "\n")
		table.insert(err, cloveErrorMessage.."\n\n")

		for l in string.gmatch(trace, "(.-)\n") do
			if not string.match(l, "boot.lua") then
				l = string.gsub(l, "stack traceback:", "\n")
				table.insert(err, l)
			end
		end

		local p = table.concat(err, "\n")

		p = string.gsub(p, "\t", "")
		p 	= string.gsub(p, "%[string \"(.-)\"%]", "%1")
		love.graphics.print(p,10,100)
		love.graphics.setColor(255,255,255,255)			
	end
end

function cloveHasError()
	return cloveErrorResult
end

cloveErrorResult = xpcall( love.load, error_printer )
cloveErrorResult = xpcall( love.update, deferErrhand )
cloveErrorResult = xpcall( love.draw, deferErrhand )

if cloveErrorResult then 
	cloveHandleErrors()
end
