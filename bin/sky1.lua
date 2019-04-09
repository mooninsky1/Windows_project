
--[[
this functions call by c/c++
--]]
function C_Call_Lua( a,b )
	-- body
	local sum = a+b
	print("in skyl.lua sum is:"..sum)
	return sum
end

