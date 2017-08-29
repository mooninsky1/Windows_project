#ifndef __MYSQL_COMMAND_H__
#define __MYSQL_COMMAND_H__

#include "ISqlDataBase.h"
#include "MySqlConnection.h"
#include "MySqlParameter.h"

class MySqlCommand : public ISqlCommand
{
private:

	/** @name  ˽�г�Ա���� */////////////////////////////////////////////////////
    /// @{

	// MySql���Ӷ���
	MySqlConnection *m_pMySqlConnection;
	// ������ʱ
	int m_nBusyTimeout;
	// �󶨲���
	int m_nBandParamPostion;
	// Ԥ�����������
	int m_nBindParamTotal;
	//
	MySqlParameter *m_pMySqlParameter;
	// �󶨲����б�
	MYSQL_BIND *m_pMySqlBindParamArray;
	MYSQL_STMT *m_pMySqlStmt;
	/// @}

public:
	MySqlCommand(void);
	~MySqlCommand(void);
public:
	MySqlCommand(MySqlConnection *pMySqlConnection);
public:
	
	/** @name �������������� *///////////////////////////////////////////////////
    /// @{
	
	// ��Ӵ洢���̲������������ͣ�
	virtual void AddIntInputParameter(const char *lpszName, int nValue);
	// ��Ӵ洢���̲��������������ͣ�
	virtual void AddShortInputParameter(const char *lpszName, short nValue);
	// ��Ӵ洢���̲������ֽ����ͣ�
	virtual void AddByteInputParameter(const char *lpszName, char byValue);
	// ��Ӵ洢���̲������ַ����ͣ�
	virtual void AddStringInputParameter(const char *lpszName, const char *lpszValue);
	// ��Ӵ洢���̲��������������ͣ�
	virtual void AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nLen);

	/// @}

public:

	/** @name �������������� *///////////////////////////////////////////////////
    /// @{

	// �������洢���̲������������ͣ�
	virtual void AddIntOutputParameter(const char *lpszName);

	/// @}

public:

	/** @name ��ȡ���ز������� *///////////////////////////////////////////////////
    /// @{

	// ��ȡ�洢���̷��صĲ������������ͣ�
	virtual int GetIntParameterValue(const char *lpszName);

	/// @}

public:

	/** @name ��ն���������� *///////////////////////////////////////////////////
    /// @{

	// ��ն������
	virtual void ClearParameter();

	/// @}
public:


	/** @name ���Ա���� *///////////////////////////////////////////////////
    /// @{

	// ����CMySqlConnectionָ��
	virtual void SetSqlConnection(ISqlConnection *pSqlConnection);
	// ִ���޷���ֵ
	virtual void ExecuteNonQuery(const char * strSQL, int bUseStoredProc = 0);
	// ִ���޷���ֵ
	virtual int ExecuteQuery(const char * strSQL, int bUseStoredProc = 0);
	// ִ�в�ѯ���
	virtual ISqlDataReader* ExecuteReader(const char * strSQL, int bUseStoredProc = 0);
	// ִ�в�ѯ���
	virtual int ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc = 0);
	// ִ�в�ѯ���
	virtual int ExecuteScalar(const char * strSQL, int bUseStoredProc = 0);
	// 
	virtual void ExecuteBegin(void);
	//
	virtual void ExecuteEnd(void);
	// ɾ������
	virtual void DeleteThis(void);

	/// @}
};

#endif	// __MYSQL_COMMAND_H__
