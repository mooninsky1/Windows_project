#ifndef __MYSQL_DATA_READER_H__
#define __MYSQL_DATA_READER_H__


#include "mysql.h"
#include "ISqlDataBase.h"

class MySqlDataReader : public ISqlDataReader
{
private:

	/** @name  ˽�г�Ա���� */////////////////////////////////////////////////////
    /// @{

	// MySQL����
	MYSQL *m_pMySQL;
	// MySQL���ص����ݼ�
	MYSQL_RES *m_pMySQL_Res;
	// ������
	int	m_nRowCount;
	// ������
	int m_nColumnCount;
	// ������ݳ���
	unsigned long *m_pColumnLength;
	// ������
	MYSQL_ROW m_pMySqlRow;

	/// @}

public:
	MySqlDataReader(void);
	~MySqlDataReader(void);

public:
	MySqlDataReader(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res);
public:

	/** @name ������Ա���� *///////////////////////////////////////////////////
    /// @{

	void SetMySQLRes(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res);
	
	/// @}

public:

	/** @name ���Ա���� *///////////////////////////////////////////////////
    /// @{

	// �Ƿ��Ѿ���ȡ����
	virtual int Read();
	// �ƶ���¼����һ��
	virtual int MoveNext();
	// ��ȡ�����ַ���
	virtual const char* GetFieldValue(int nField);
	// ��ȡ�����ַ���
	virtual const char* GetFieldValue(const char *strFieldName);
	// ��ȡ��������
	virtual int GetIntField(int nField, int nNullValue = 0);
	// ��ȡ��������
	virtual int GetIntField(const char *strFieldName, int nNullValue = 0);
	// ��ȡ����������
	virtual float GetFloatField(int nField, float fNullValue = 0.0);
	// ��ȡ����������
	virtual float GetFloatField(const char *strFieldName, float fNullValue = 0.0);
	// ��ȡ����������
	virtual double GetDoubleField(int nField, double dNullValue = 0.0);
	// ��ȡ����������
	virtual double GetDoubleField(const char *strFieldName, double dNullValue = 0.0);
	// ��ȡ�����ַ���
	virtual string GetStringField(int nField, const char *strNullValue = "");
	// ��ȡ�����ַ���
	virtual string GetStringField(const char *strFieldName, const char *strNullValue = "");
	// ��ȡ����������
	virtual int GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0);
	// ��ȡ����������
	virtual int GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0);
	// �ж��ֶ��Ƿ�Ϊ��
	virtual int IsFieldNull(int nField);
	// �ж��ֶ��Ƿ�Ϊ��
	virtual int IsFieldNull(const char *strFieldName);
	// ��ȡ�����ֶ�����
	virtual const char* GetFieldName(int nColumn);
	// ��ȡ����λ��
	virtual int GetFieldIndex(const char *strFieldName);
	// ��ȡ�ֶ�������
	virtual int GetFieldCount();
	// ��ȡ��¼����
	virtual int GetRowCount();
	// �ս����
	virtual void Close();
	// ɾ������
	virtual void DeleteThis(void);

	/// @}

private:

	/** @name ˽��Ա���� *///////////////////////////////////////////////////
    /// @{

	// ��ȡ�ֶγ���
	long GetFieldLength(int nField);
	// ��ȡ�ֶγ���
	long GetFieldLength(const char *strFieldName);

	/// @}
};


#endif	// __MYSQL_DATA_READER_H__
