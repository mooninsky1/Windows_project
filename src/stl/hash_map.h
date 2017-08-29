//********************************************************************
//	�ļ�����:	
//	��������:	2014/11/04
//	��Ȩ��Ϣ:	��Ȥ���
//	�� �� ��:	���
//  ����˵��:   ����hash_map�Զ�������windows�¸�linux��find linux��find���Ķ�����key��Ӧ��value
//	�޸ļ�¼:	 
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