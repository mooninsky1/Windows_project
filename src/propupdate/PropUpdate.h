//********************************************************************
//	�ļ�����:	
//	��������:	2014/11/14
//	��Ȩ��Ϣ:	��Ȥ���
//	�� �� ��:	���
//  ����˵��: ���Դ������   
//	�޸ļ�¼:	 
//*********************************************************************
#pragma once

#include <vector>
#include <iostream>

typedef std::vector<int> vecSMultiPropRecord;

class CPropPackUpdate
{
public:
	static CPropPackUpdate& Instance()
	{
		static CPropPackUpdate obj;
		return obj;
	}
	CPropPackUpdate()
	{
		Reset();
	}
public:
	void Reset();
	//
	void IncMultiUpdateCount();
	void DecMultiUpdateCount();
	int GetMultiUpdateCount(){return m_byMultiUpdateCount;}
	void SetMultiUpdateCount(int byMultiUpdateCount){m_byMultiUpdateCount = byMultiUpdateCount;}
	//
	vecSMultiPropRecord& GetSMultiPropRecord(){return m_vecPropUpdateData;}
	void SetSMultiPropRecord(const vecSMultiPropRecord&	vecPropUpdateData){ m_vecPropUpdateData = vecPropUpdateData;}
	//
	int	GetUid(){return m_uid;}
	void		SetUid(int uid ){m_uid = uid;}	
	//
	void		PushSMultiPropRecord(int record)
	{
		m_vecPropUpdateData.push_back(record);
	}
private:
	int								m_uid;						// ʵ��ID			
	int								m_byMultiUpdateCount;		// �����Ը������ô���*/
	vecSMultiPropRecord				m_vecPropUpdateData;		// �����Ը����б�
};

class CPropPackUpdateDo
{
public:
	CPropPackUpdateDo(int uid);
	~CPropPackUpdateDo();
	void SwapOut();
	void SwapIn();
private:
	int								m_uidTemp;						// ʵ��ID			
	int								m_byMultiUpdateCountTemp;		// �����Ը������ô���*/
	vecSMultiPropRecord				m_vecPropUpdateDataTemp;		// �����Ը����б�
};

class CPropUpdateTest
{
public:
	void Test();
	
};