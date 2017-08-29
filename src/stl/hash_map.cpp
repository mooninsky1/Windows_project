#include "hash_map.h"
#include <iostream>

void CHashMapTest::Test()
{
	for (int i=0; i < 10; i++)
	{
		SSkillID skill;
		skill.nid = i;
		skill.nlevel =i;
		m_hashInt[skill] = i;
	}
	for (int i=0; i < 10; i++)
	{
		SSkillID skill;
		skill.nid = i;
		skill.nlevel =i;
		ItHash it = m_hashInt.find(skill);
		if (it != m_hashInt.end())
		{
			std::cout<<"find skill id:"<<skill.nid <<"result:"<<it->second<<std::endl;
		}
	}
}