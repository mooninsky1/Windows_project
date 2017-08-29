//********************************************************************
//	文件名称:	
//	创建日期:	2014/11/04
//	版权信息:	豆趣软件
//	创 建 人:	李涵锋
//  功能说明:   测试hash_map自定义类在windows下跟linux下find linux下find到的都不是key对应的value
//	修改记录:	 
//*********************************************************************

#pragma once

#include <hash_map>
struct SSkillID
{
	int nid;
	int nlevel;
// 	SSkillID(){}
// 	SSkillID& operator=(const SSkillID& ref)
// 	{
// 		nid = ref.nid;
// 		nlevel = ref.nlevel;
// 		return *this;
// 	}
// 	SSkillID(const SSkillID& ref)
// 	{
// 		nid = ref.nid;
// 		nlevel = ref.nlevel;
// 	}
	bool operator==(const SSkillID& ref)const 
	{
		return this->nid == ref.nid && this->nlevel == ref.nlevel;
	}
	bool operator < (const SSkillID& ref) const
	{
		return this->nid < ref.nid && this->nlevel<ref.nlevel;
	}
};
struct SKillId_hashfun
{
	size_t operator()(const SSkillID & ref)const
	{

		return ref.nid*100+ref.nlevel;
	}

};
struct SKillId_equalfun 
{
	bool operator()(const SSkillID& left,const SSkillID& right)const 
	{
		bool b=false;
		if(right.nid == left.nid && right.nlevel == left.nlevel)
		{
			b = true;
		}
		return b;
	}

};
#ifdef __LINUX__
#define stdext __gnu_cxx
	//namespace __gnu_cxx
	//{
	//	template <>
	//	struct hash<SSkillID>
	//	{
	//		inline size_t operator() (const SSkillID &eventkey) const
	//		{
	//			return eventkey.nid*100+eventkey.nlevel;
	//		}
	//	};
	//}
#else
namespace stdext
{
	inline size_t hash_value(const SSkillID &eventkey)
	{
		return eventkey.nid*100+eventkey.nlevel;
	}

}

#endif
#ifdef __LINUX__
typedef stdext::hash_map<SSkillID,int,SKillId_hashfun,SKillId_equalfun> CHash;
typedef stdext::hash_map<SSkillID,int,SKillId_hashfun,SKillId_equalfun>::iterator ItHash;
#else
typedef stdext::hash_map<SSkillID,int> CHash;
typedef stdext::hash_map<SSkillID,int>::iterator ItHash;
#endif
class CHashMapTest
{
public:
	CHashMapTest(){}
	~CHashMapTest(){}
	void Test();
private:
	CHash m_hashInt;
};