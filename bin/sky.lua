--[[
测试c++向lua传递数值
print("c++ nValue="..nValue)
--]]

---[[
--调用c++函数
local sum = AddSum(5,7)
print("sum is:"..sum)
---]]

--[[
lua define function
--]]

local test  = function ( ... )
	-- body
	print("this is one kind of lua's fun")
end

function fun( ... )
	-- body
	print("this is nother lua's fun")
end

test()

fun()

--[[
this functions call by c/c++
--]]
function C_Call_Lua( a,b )
	-- body
	local sum = a+b
	print("in lua sum is:"..sum)
	return sum
end

--[[
this functions call by c/c++
--]]
function C_Call_Lua1( a,b )
	-- body
	local sum = a+b
	print("in sky.lua sum is:"..sum)
	return sum
end

---[[__index元方法测试

Window={} --创建一个名字空间
Window.mt={} --定义元表
--声明构造函数
function Window.new(o,k)
	setmetatable(o,Window.mt)
	return o
end
--定义元原型
Window.prototype={x=10,y=20,z=30,w=40,h=50}
--定义__index  用于talbe查询
Window.mt.__index=function (table,key)
	print("access __index")
	return Window.prototype[key]
end
-- __newindex 用于table更新
Window.mt.__newindex=function (table,key,value)
	print("access __newindex")
	Window.prototype[key]=value
	
end
--w=Window.new({x=1,y=2})
w=Window.new{x=1,y=2}
print(w.x)    --  1
print(w.y)
print(w.z)	  --30
print(w.k)	  --nil
w.k = 100
print(w.k)
print("rawget")
print(rawget(w,x))
print(rawget(w,z))
--]]