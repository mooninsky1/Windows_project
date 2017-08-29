
#include "MySqlDataReader.h"
#include <stdlib.h>
#include <string.h>



MySqlDataReader::MySqlDataReader(void)
{
	// MySQL����
	m_pMySQL = NULL;
	// MySQL���ص����ݼ�
	m_pMySQL_Res = NULL;
	// ������
	m_pMySqlRow = NULL;
	// ������
	m_nRowCount = 0;
	// ������
	m_nColumnCount = 0;
	// ���ֶγ���
	m_pColumnLength = NULL;
}

MySqlDataReader::MySqlDataReader(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res)
{
	// MySQL����
	m_pMySQL = pMySQL;
	// MySQL���ص����ݼ�
	m_pMySQL_Res = pMySQL_Res;
	//��λ�α�λ�õ���һ��λ��
	mysql_data_seek(m_pMySQL_Res, 0);
	// �õ�������
	m_nRowCount = (int)mysql_num_rows(m_pMySQL_Res); 
	// �õ�������
	m_nColumnCount = mysql_num_fields(m_pMySQL_Res);
	// ��ȡ�ֶγ���
	m_pColumnLength = mysql_fetch_lengths(m_pMySQL_Res);
}

MySqlDataReader::~MySqlDataReader(void)
{
	Close();
}

/** @name ������Ա���� *///////////////////////////////////////////////////
/// @{

void MySqlDataReader::SetMySQLRes(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res)
{
	// MySQL����
	m_pMySQL = pMySQL;
	// MySQL���ص����ݼ�
	m_pMySQL_Res = pMySQL_Res;
	//��λ�α�λ�õ���һ��λ��
	mysql_data_seek(m_pMySQL_Res, 0);
	// �õ�������
	m_nRowCount = (int)mysql_num_rows(m_pMySQL_Res); 
	// �õ�������
	m_nColumnCount = mysql_num_fields(m_pMySQL_Res);
}

/// @}

int MySqlDataReader::Read()
{
	m_pMySqlRow =  mysql_fetch_row(m_pMySQL_Res);
	if (m_pMySqlRow == NULL)
	{
		return 0;
	}
	// ��ȡ�ֶγ���
	m_pColumnLength = mysql_fetch_lengths(m_pMySQL_Res);
	return 1;
}
int MySqlDataReader::MoveNext()
{
	return 1;
}


// ��ȡ�����ַ���
const char* MySqlDataReader::GetFieldValue(const char *strFieldName)
{
	int nFiledIndex = GetFieldIndex(strFieldName);
	if (nFiledIndex == -1)
	{
		return NULL;
	}
	return GetFieldValue(nFiledIndex);

}

// ��ȡ�����ַ���
const char* MySqlDataReader::GetFieldValue(int nField)
{
	if (nField >= m_nColumnCount)
	{
		return NULL;
	}
	if (m_pMySqlRow == NULL)
	{
		return NULL;
	}
	return m_pMySqlRow[nField];

}

	

// ��ȡ��������
int MySqlDataReader::GetIntField(int nField, int nNullValue/*=0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return nNullValue;
	}
	return atoi(pszFieldValue);

}

// ��ȡ��������
int MySqlDataReader::GetIntField(const char *strFieldName, int nNullValue/*=0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetIntField(nFieldIndex, nNullValue);
}

// ��ȡ����������
float MySqlDataReader::GetFloatField(int nField, float fNullValue/*=0.0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return fNullValue;
	}
	return (float)atof(pszFieldValue);
}

// ��ȡ����������
float MySqlDataReader::GetFloatField(const char *strFieldName, float fNullValue/*=0.0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetFloatField(nFieldIndex, fNullValue);
}

// ��ȡ����������
double MySqlDataReader::GetDoubleField(int nField, double dNullValue/*=0.0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return dNullValue;
	}
	return atof(pszFieldValue);
}

// ��ȡ����������
double MySqlDataReader::GetDoubleField(const char *strFieldName, double dNullValue/*=0.0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetDoubleField(nFieldIndex, dNullValue);
}

// ��ȡ�����ַ���
string MySqlDataReader::GetStringField(int nField, const char *strNullValue/*=""*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return strNullValue;
	}
	return pszFieldValue;
}

// ��ȡ�����ַ���
string MySqlDataReader::GetStringField(const char *strFieldName, const char *strNullValue/*=""*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetStringField(nFieldIndex, strNullValue);
}

// ��ȡ����������
int MySqlDataReader::GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue/* = 0*/)
{
	int nFieldLength = GetFieldLength(nField);
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return nNullValue;
	}
	if (uMaxLen < (unsigned int)nFieldLength)
	{
		return nNullValue;
	}
	memcpy(lpszContent, pszFieldValue, nFieldLength);
	return nFieldLength;
}

// ��ȡ����������
int MySqlDataReader::GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue/* = 0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetBinaryField(nFieldIndex, lpszContent, uMaxLen, nNullValue);
}

// �ж��ֶ��Ƿ�Ϊ��
int MySqlDataReader::IsFieldNull(int nField)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return 1;
	}
	return 0;
}

// �ж��ֶ��Ƿ�Ϊ��
int MySqlDataReader::IsFieldNull(const char *strFieldName)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return IsFieldNull(nFieldIndex);
}

// ��ȡ�����ֶ�����
const char* MySqlDataReader::GetFieldName(int nColumn)
{
	mysql_field_seek(m_pMySQL_Res, nColumn);
	MYSQL_FIELD *pMySQL_Field = mysql_fetch_field(m_pMySQL_Res);
	if (pMySQL_Field != NULL)
	{
		return pMySQL_Field->name;
	}
	return  NULL;
}

// ��ȡ����λ��
int MySqlDataReader::GetFieldIndex(const char *strFieldName)
{
	if (strFieldName == NULL)
	{
		return -1;
	}
	// ��λ����0��
	for (int i = 0; i < m_nColumnCount; i++)
	{
		if (strcmp(GetFieldName(i), strFieldName) == 0)
		{
			return i;
		}
	}
	return -1;
}

// ��ȡ�ֶγ���
long MySqlDataReader::GetFieldLength(int nField)
{
	if (nField >= m_nColumnCount)
	{
		return NULL;
	}
	if (m_pMySqlRow == NULL)
	{
		return NULL;
	}
	return m_pColumnLength[nField];
}

// ��ȡ�ֶγ���
long MySqlDataReader::GetFieldLength(const char *strFieldName)
{
	int nFiledIndex = GetFieldIndex(strFieldName);
	if (nFiledIndex == -1)
	{
		return NULL;
	}
	return GetFieldLength(nFiledIndex);
}

// ��ȡ�ֶ�������
int MySqlDataReader::GetFieldCount()
{
	return m_nColumnCount;
}

// ��ȡ��¼����
int MySqlDataReader::GetRowCount()
{
	return m_nRowCount;
}

// �ս����
void MySqlDataReader::Close()
{
	if (m_pMySQL != NULL)
	{
		do
		{
			MYSQL_RES* pMySQL_Res = mysql_store_result(m_pMySQL);
			mysql_free_result(pMySQL_Res);
		}
		while ((0 == mysql_next_result(m_pMySQL)));
	}
	m_pMySqlRow = NULL;
	m_pMySQL_Res = NULL;
	m_nColumnCount = 0;
	m_nRowCount = 0;
}

// ɾ������
void MySqlDataReader::DeleteThis(void)
{
	delete this;
}

#ifdef __MY_SQL__

// ��ȡMYSQL��ȡ����
ISqlDataReader* GetStaticMySqlDataReader()
{
	static MySqlDataReader *pMySqlDataReader = NULL;
	if (pMySqlDataReader == NULL)
	{
		pMySqlDataReader = new MySqlDataReader();
	}
	return pMySqlDataReader;
}

// ʵ����MYSQL��ȡ����
ISqlDataReader* GetNewMySqlDataReader()
{
	MySqlDataReader *pMySqlDataReader = new MySqlDataReader();
	return pMySqlDataReader;
}

#endif	// __MY_SQL__

