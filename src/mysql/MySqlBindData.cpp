#include "MySqlBindData.h"
#include "mysql.h"
#include <string.h>

MySqlBindData::MySqlBindData(void)
{
	// ����
	m_nLength = 0;
	// ����������
	m_nBufferType = 0;
	// �����㹻��Ļ�����
	m_pBuffer = new char[8000];
}

MySqlBindData::~MySqlBindData(void)
{
	if (m_pBuffer != 0)
	{
		delete[] m_pBuffer;
		m_pBuffer = 0;
	}
}

// ������������
void MySqlBindData::SetValue(int nValue)
{
	m_nLength = 4;
	m_nBufferType = MYSQL_TYPE_LONG;
	*(int*)m_pBuffer = nValue;
}

// ���ö���������
void MySqlBindData::SetValue(short nValue)
{
	m_nLength = 2;
	m_nBufferType = MYSQL_TYPE_SHORT;
	*(short*)m_pBuffer = nValue;
}

// �����ֽ�����
void MySqlBindData::SetValue(char byValue)
{
	m_nLength = 1;
	m_nBufferType = MYSQL_TYPE_TINY;
	*(char*)m_pBuffer = byValue;
}

// �����ַ�����
void MySqlBindData::SetValue(const char *lpszValue)
{
	int nTextLen = (int)strlen(lpszValue);
	m_nLength = nTextLen + 1;
	m_nBufferType = MYSQL_TYPE_VARCHAR;
	strcpy((char*)m_pBuffer, lpszValue);
}

// ���ö���������
void MySqlBindData::SetValue(char *lpBinaryValue, int nBinaryLen)
{
	m_nLength = nBinaryLen;
	m_nBufferType = MYSQL_TYPE_BLOB;
	memcpy(m_pBuffer, lpBinaryValue, nBinaryLen);
}


// ��ȡָ�򳤶�ָ��
int MySqlBindData::GetLength()
{
	return m_nLength;
}


// ��ȡָ�򻺳���ָ��
void* MySqlBindData::GetBufferPointer()
{
	return m_pBuffer;
}

// ��ȡ����������
int MySqlBindData::GetBufferType()
{
	return m_nBufferType;
}