//********************************************************************
//	文件名称:	
//	创建日期:	2014/11/14
//	版权信息:	豆趣软件
//	创 建 人:	李涵锋
//  功能说明: 属性打包更新   
//	修改记录:	 
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
	int								m_uid;						// 实体ID			
	int								m_byMultiUpdateCount;		// 多属性更新引用次数*/
	vecSMultiPropRecord				m_vecPropUpdateData;		// 多属性更新列表
};

class CPropPackUpdateDo
{
public:
	CPropPackUpdateDo(int uid);
	~CPropPackUpdateDo();
	void SwapOut();
	void SwapIn();
private:
	int								m_uidTemp;						// 实体ID			
	int								m_byMultiUpdateCountTemp;		// 多属性更新引用次数*/
	vecSMultiPropRecord				m_vecPropUpdateDataTemp;		// 多属性更新列表
};

class CPropUpdateTest
{
public:
	void Test();
	
};