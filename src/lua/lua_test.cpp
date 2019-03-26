#include "lua_test.h"
#include <iostream>
using namespace std;

//sky ��̬��Ա��ʼ���������ܷ���
lua_State* CLuaTest::L=NULL;

void CLuaTest::LuaInit()
{
	L = luaL_newstate();
	luaopen_base(L); //
	luaopen_table(L); //
	luaopen_package(L); //
	luaopen_io(L); //
	luaopen_string(L); //

	luaL_openlibs(L); //���������е�lib
}
void CLuaTest::CloseLua()
{
	lua_close(L);
}


void CLuaTest::Test()
{
	LuaInit();
	//
	OpenLuaFile();
	//
	//C_Push_value();
	//C_Push_Fun();
	C_Call_Lua();
	//
	CloseLua();
}
//open lua source
void CLuaTest::OpenLuaFile()
{
	char* szLuaFile="sky.lua";
	if( luaL_loadfile(L,szLuaFile) ||
		lua_pcall(L,0,0,0) )
	{
		const char * error = lua_tostring(L, -1) ;
		std::cout << string(error).c_str() << endl;
	}
}
//c push value to lua
void CLuaTest::C_Push_value()
{
	int nValue=10;
	lua_pushnumber(L,nValue);
	lua_setglobal(L,"nValue");
}
void CLuaTest::C_Push_Fun()
{
	lua_pushcfunction(L,AddSum);
	lua_setglobal(L,"AddSum");
}

int CLuaTest::AddSum(lua_State* L)
{
	cout<<"lua call this fun\n";
	int sum =100;
	//�õ�lua���ݵĲ�������
	int n = lua_gettop(L);
	if(2 != n)
	{
		lua_pushstring(L,"��������!");
		lua_error(L);
		return 0;
	}
	int nfirstvalue = luaL_checkint(L,-2);
	cout<<"first value is:"<<nfirstvalue<<endl;
	int nsecondvalue = luaL_checkint(L,-1);
	cout<<"second value is:"<<nsecondvalue<<endl;
	sum = nfirstvalue+nsecondvalue;
	lua_pushnumber(L,sum);
	//����ֵֻ��һ��
	return 1;
}

//c call lua's fun
void CLuaTest::C_Call_Lua()
{
	//����lua�к���
	lua_getglobal(L,"C_Call_Lua");
	//���ݲ���
	lua_pushinteger(L,10);
	lua_pushinteger(L,20);
	//
	lua_pcall(L,2,1,0);
	if(!lua_isnumber(L,-1))
	{
		return;
	}
	int iRet = lua_tonumber(L,-1);
	lua_pop(L,-1);
	cout<<"in c++ the sum is:"<<iRet<<endl;
}


