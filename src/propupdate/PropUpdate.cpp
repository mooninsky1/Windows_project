#include "PropUpdate.h"

static char g_szPlayerTempBuf[4096];

void CPropPackUpdate::IncMultiUpdateCount()
{
	m_byMultiUpdateCount++;
}
void CPropPackUpdate::DecMultiUpdateCount()
{
	m_byMultiUpdateCount--;
}
void CPropPackUpdate::Reset()
{
	m_uid = 0;
	m_byMultiUpdateCount = 0;
	m_vecPropUpdateData.clear();
}
CPropPackUpdateDo::CPropPackUpdateDo(int uid)
{
	//同一对象引用计数+1
	if (CPropPackUpdate::Instance().GetUid() == uid )
	{
		CPropPackUpdate::Instance().IncMultiUpdateCount();
	}
	//不是同一对象交换出来
	else
	{
		//copy
		SwapOut();

		//reset
		CPropPackUpdate::Instance().Reset();
		CPropPackUpdate::Instance().SetUid(uid);
		CPropPackUpdate::Instance().IncMultiUpdateCount();
	}
	
}
void CPropPackUpdateDo::SwapOut()
{
	m_uidTemp = CPropPackUpdate::Instance().GetUid();
	m_byMultiUpdateCountTemp = CPropPackUpdate::Instance().GetMultiUpdateCount();
	m_vecPropUpdateDataTemp  = CPropPackUpdate::Instance().GetSMultiPropRecord();
}
void CPropPackUpdateDo::SwapIn()
{
	CPropPackUpdate::Instance().Reset();

	CPropPackUpdate::Instance().SetUid(m_uidTemp);
	CPropPackUpdate::Instance().SetMultiUpdateCount(m_byMultiUpdateCountTemp);
	CPropPackUpdate::Instance().SetSMultiPropRecord(m_vecPropUpdateDataTemp);
}
CPropPackUpdateDo::~CPropPackUpdateDo()
{
	//引用计数－1
	CPropPackUpdate::Instance().DecMultiUpdateCount();

	if (0 == CPropPackUpdate::Instance().GetMultiUpdateCount())
	{
		vecSMultiPropRecord SMultiPropRecord = CPropPackUpdate::Instance().GetSMultiPropRecord();
		
		vecSMultiPropRecord::iterator it = SMultiPropRecord.begin();
		std::cout<<"uid:"<<CPropPackUpdate::Instance().GetUid()<<",";
		for (; it != SMultiPropRecord.end() ; ++it)
		{
			std::cout<<*it<<'\t';
		}
		std::cout<<std::endl;
		SwapIn();
	}
}
void CPropUpdateTest::Test()
{
	CPropPackUpdateDo do1(1);
	CPropPackUpdate::Instance().PushSMultiPropRecord(10);
	{
		CPropPackUpdateDo do2(2);
		CPropPackUpdate::Instance().PushSMultiPropRecord(20);
		CPropPackUpdate::Instance().PushSMultiPropRecord(21);
		{
			CPropPackUpdateDo do2(2);
			CPropPackUpdate::Instance().PushSMultiPropRecord(22);
			CPropPackUpdate::Instance().PushSMultiPropRecord(23);
			{
				CPropPackUpdateDo do2(2);
				CPropPackUpdate::Instance().PushSMultiPropRecord(24);
				CPropPackUpdate::Instance().PushSMultiPropRecord(25);
				{
					CPropPackUpdateDo do1(1);
					CPropPackUpdate::Instance().PushSMultiPropRecord(11);
					CPropPackUpdate::Instance().PushSMultiPropRecord(12);
				}
			}
		}
	}

}