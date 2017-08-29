#ifndef __I_SQL_DATABASE_H__
#define __I_SQL_DATABASE_H__
#include <string>
using namespace std;
class ISqlConnection
{
public:
	// �����ݿ�
	virtual int Open(const char *szHost, int nPort, const char *szUser, const char *szPassword, const char *szDBName) = 0;
	// �ر����ݿ�
	virtual void Close(void) = 0;
	// ɾ������
	virtual void DeleteThis(void) = 0;
};

//#if defined (__MS_SQL__)
// ��ȡMSSQL���Ӷ���
//ISqlConnection* GetStaticMsSqlConnection();
// ʵ����MSSQL���Ӷ���
//ISqlConnection* GetNewMsSqlConnection();
//#elif defined (__MY_SQL__)
// ��ȡMYSQL���Ӷ���
ISqlConnection* GetStaticMySqlConnection();
// ʵ����MYSQL���Ӷ���
ISqlConnection* GetNewMySqlConnection();
//#endif

class ISqlDataReader
{
public:
	// �Ƿ��Ѿ�����
	virtual int Read() = 0;
	// �ƶ���һ����¼
	virtual int MoveNext() = 0;
	// ��ȡ�����ַ���
	virtual const char* GetFieldValue(int nField) = 0;
	// ��ȡ�����ַ���
	virtual const char* GetFieldValue(const char *strFieldName) = 0;
	// ��ȡ��������
	virtual int GetIntField(int nField, int nNullValue = 0) = 0;
	// ��ȡ��������
	virtual int GetIntField(const char *strFieldName, int nNullValue = 0) = 0;
	// ��ȡ����������
	virtual float GetFloatField(int nField, float fNullValue = 0.0) = 0;
	// ��ȡ����������
	virtual float GetFloatField(const char *strFieldName, float fNullValue = 0.0) = 0;
	// ��ȡ����������
	virtual double GetDoubleField(int nField, double dNullValue = 0.0) = 0;
	// ��ȡ����������
	virtual double GetDoubleField(const char *strFieldName, double dNullValue = 0.0) = 0;
	// ��ȡ�����ַ���
	virtual string GetStringField(int nField, const char *strNullValue = "") = 0;
	// ��ȡ�����ַ���
	virtual string GetStringField(const char *strFieldName, const char *strNullValue = "") = 0;
	// ��ȡ����������
	virtual int GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0) = 0;
	// ��ȡ����������
	virtual int GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0) = 0;
	// �ж��ֶ��Ƿ�Ϊ��
	virtual int IsFieldNull(int nField) = 0;
	// �ж��ֶ��Ƿ�Ϊ��
	virtual int IsFieldNull(const char *strFieldName) = 0;
	// ��ȡ�����ֶ�����
	virtual const char* GetFieldName(int nColumn) = 0;
	// ��ȡ����λ��
	virtual int GetFieldIndex(const char *strFieldName) = 0;
	// ��ȡ�ֶ�������
	virtual int GetFieldCount() = 0;
	// ��ȡ��¼����
	virtual int GetRowCount() = 0;
	// �ս����
	virtual void Close() = 0;
	// ɾ������
	virtual void DeleteThis(void) = 0;
};

//#if defined (__MS_SQL__)
// ��ȡMSSQL��ȡ����
//ISqlDataReader* GetStaticMsSqlDataReader();
// ʵ����MSSQL��ȡ����
//ISqlDataReader* GetNewMsSqlDataReader();
//#elif defined (__MY_SQL__)
// ��ȡMYSQL��ȡ����
ISqlDataReader* GetStaticMySqlDataReader();
// ʵ����MYSQL��ȡ����
ISqlDataReader* GetNewMySqlDataReader();
//#endif

class ISqlCommand
{
public:
	
	/** @name �������������� *///////////////////////////////////////////////////
    /// @{
	
	// ��Ӵ洢���̲������������ͣ�
	virtual void AddIntInputParameter(const char *lpszName, int nValue) = 0;
	// ��Ӵ洢���̲��������������ͣ�
	virtual void AddShortInputParameter(const char *lpszName, short nValue) = 0;
	// ��Ӵ洢���̲������ֽ����ͣ�
	virtual void AddByteInputParameter(const char *lpszName, char byValue) = 0;
	// ��Ӵ洢���̲������ַ����ͣ�
	virtual void AddStringInputParameter(const char *lpszName, const char *lpszValue) = 0;
	// ��Ӵ洢���̲��������������ͣ�
	virtual void AddBinaryInputParameter(const char *lpszName, char *lpszValue, int nLen) = 0;

	/// @}

public:

	/** @name �������������� *///////////////////////////////////////////////////
    /// @{

	// �������洢���̲������������ͣ�
	virtual void AddIntOutputParameter(const char *lpszName) = 0;

	/// @}

public:

	/** @name ��ȡ���ز������� *///////////////////////////////////////////////////
    /// @{

	// ��ȡ�洢���̷��صĲ������������ͣ�
	virtual int GetIntParameterValue(const char *lpszName) = 0;

	/// @}

public:

	/** @name ��ն���������� *///////////////////////////////////////////////////
    /// @{

	// ��ն������
	virtual void ClearParameter() = 0;

	/// @}

public:

	/** @name ִ��SQL��亯�� *///////////////////////////////////////////////////
    /// @{


	// ִ���޷���ֵ
	virtual void ExecuteNonQuery(const char * strSQL, int bUseStoredProc = 0) = 0;
	// ִ���޷���ֵ
	virtual int ExecuteQuery(const char * strSQL, int bUseStoredProc = 0) = 0;
	// ִ�в�ѯ���
	virtual ISqlDataReader* ExecuteReader(const char * strSQL, int bUseStoredProc = 0) = 0;
	// ִ�в�ѯ���
	virtual int ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc = 0) = 0;
	// ִ�в�ѯ���
	virtual int ExecuteScalar(const char * strSQL, int bUseStoredProc = 0) = 0;

	/// @}

public:

	/** @name ���Ա���� *///////////////////////////////////////////////////
    /// @{

	// ����SqlConnectionָ��
	virtual void SetSqlConnection(ISqlConnection *pSqlConnection) = 0;
	// ��ʼִ��
	virtual void ExecuteBegin(void) = 0;
	// ����ִ��
	virtual void ExecuteEnd(void) = 0;
	// ɾ������
	virtual void DeleteThis(void) = 0;

	/// @}
};

//#if defined (__MS_SQL__)
// ��ȡMSSQL�������
//ISqlCommand* GetStaticMsSqlCommand();
// ʵ����MSSQL�������
//ISqlCommand* GetNewMsSqlCommand();
//#elif defined (__MY_SQL__)
// ��ȡMYSQL�������
ISqlCommand* GetStaticMySqlCommand();
// ʵ����MYSQL�������
ISqlCommand* GetNewMySqlCommand();
//#endif

#endif	// __I_SQL_DATABASE_H__