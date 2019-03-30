#include <iostream>
using namespace std;

#define LUA_COMPAT_APIINTCASTS
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};

class CLuaTest
{
public:
	static void Test();
	//��ʼ��LUA
	static void LuaInit();
	static void CloseLua();
	//open lua source
	static void OpenLuaFile();
	//c push value to lua
	static void C_Push_value();
	//c push function
	static void C_Push_Fun();
	//c call lua's fun
	static void C_Call_Lua();
private:
	//�������ͣ�lua����
	static int AddSum(lua_State* L);
private:
	static lua_State* L;
};
