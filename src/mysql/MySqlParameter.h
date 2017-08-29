#ifndef __MYSQL_PARAMETER_H__
#define __MYSQL_PARAMETER_H__

#include "ISqlDataBase.h"
#include "MySqlConnection.h"
#include "MySqlBindData.h"

class MySqlParameter
{
private:

	/** @name  ˽�г�Ա���� */////////////////////////////////////////////////////
    /// @{

	// �󶨲����б�
	MySqlBindData *m_pMySqlBindData;

	/// @}

public:
	MySqlParameter(void);
	~MySqlParameter(void);
public:
	// ��ʼ��
	int Init();
public:
	
	/** @name �������������� *///////////////////////////////////////////////////
    /// @{
	
	// ��Ӵ洢���̲��������������ͣ�
	void AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nBinaryLen);
	// ִ�а󶨲���
	void RunExecuteBindParameter(MYSQL *pMySql, MYSQL_STMT *pMySqlStmt, const char * strSQL);

	/// @}

public:

	/** @name �������������� *///////////////////////////////////////////////////
    /// @{

	// �������洢���̲������������ͣ�
	void AddIntOutputParameter(const char *lpszName);

	/// @}

public:

	/** @name ��ȡ���ز������� *///////////////////////////////////////////////////
    /// @{

	// ��ȡ�洢���̷��صĲ������������ͣ�
	int GetIntParameterValue(const char *lpszName);

	/// @}

};

#endif	// __MYSQL_PARAMETER_H__
