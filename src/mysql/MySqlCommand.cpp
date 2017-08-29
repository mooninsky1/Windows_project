
#include "MySqlCommand.h"
#include "MySqlDataReader.h"
#include <iostream>
#include <string.h>


MySqlCommand::MySqlCommand(void)
{
	m_pMySqlConnection = NULL;
	m_pMySqlParameter = NULL;
	m_pMySqlStmt = NULL;
}

MySqlCommand::~MySqlCommand(void)
{
	if (m_pMySqlParameter != NULL)
	{
		delete m_pMySqlParameter;
		m_pMySqlParameter = NULL;
	}
}

MySqlCommand::MySqlCommand(MySqlConnection *pMySqlConnection)
{
	m_pMySqlConnection = pMySqlConnection;
	if (m_pMySqlParameter == NULL)
	{
		m_pMySqlParameter = new MySqlParameter();
		m_pMySqlParameter->Init();
	}
}


void MySqlCommand::SetSqlConnection(ISqlConnection *pSqlConnection)
{
	m_pMySqlConnection = (MySqlConnection*)pSqlConnection;
	if (m_pMySqlParameter == NULL)
	{
		m_pMySqlParameter = new MySqlParameter();
		m_pMySqlParameter->Init();
	}
}

// ��Ӵ洢���̲������������ͣ�
void MySqlCommand::AddIntInputParameter(const char *lpszName, int nValue)
{

}

// ��Ӵ洢���̲��������������ͣ�
void MySqlCommand::AddShortInputParameter(const char *lpszName, short nValue)
{

}
	

// ��Ӵ洢���̲������ֽ����ͣ�
void MySqlCommand::AddByteInputParameter(const char *lpszName, char byValue)
{

}
	
// ��Ӵ洢���̲������ַ����ͣ�
void MySqlCommand::AddStringInputParameter(const char *lpszName, const char *lpszValue)
{

}

// ��Ӵ洢���̲��������������ͣ�
void MySqlCommand::AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nLen)
{
	m_pMySqlParameter->AddBinaryInputParameter(lpszName, lpBinaryValue, nLen);
}

// ��ȡ�洢���̷��صĲ������������ͣ�
int MySqlCommand::GetIntParameterValue(const char *lpszName)
{
	return 0;
}
	
// �������洢���̲������������ͣ�
void MySqlCommand::AddIntOutputParameter(const char *lpszName)
{

}

// ��ն������
void MySqlCommand::ClearParameter()
{

}

// ִ���޷���ֵ
void MySqlCommand::ExecuteNonQuery(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteNonQuery m_pMySqlConnection is NULL" << std::endl;
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteNonQuery pMySQL is NULL" << std::endl;
		return;
	}
	if (!bUseStoredProc)
	{
		int nTextLen = (int)strlen(strSQL);
		if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
		{
			const char *lpszError = mysql_error(pMySQL);
			std::cout << "MySqlCommand::ExecuteNonQuery error:" << lpszError << std::endl;
			return;
		}
		//
		do
		{
			MYSQL_RES* pMySQL_Res = mysql_store_result(pMySQL);
			mysql_free_result(pMySQL_Res);
		}
		while ((0 == mysql_next_result(pMySQL)));
		return;
	}
	if (m_pMySqlStmt == NULL)
	{
		m_pMySqlStmt = mysql_stmt_init(pMySQL);
	}
	m_pMySqlParameter->RunExecuteBindParameter(pMySQL, m_pMySqlStmt, strSQL);
}

// ִ���޷���ֵ
int MySqlCommand::ExecuteQuery(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteQuery m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteQuery pMySQL is NULL" << std::endl;
		return 0;
	}
	
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "MySqlCommand::ExecuteQuery error:" << lpszError << std::endl;
		return 0;
	}
	// ���ز���Ӱ�������
	int nReturn = (int)mysql_affected_rows(pMySQL);
	//
	do
	{
		MYSQL_RES* pMySQL_Res = mysql_store_result(pMySQL);
		mysql_free_result(pMySQL_Res);
	}
	while ((0 == mysql_next_result(pMySQL)));

	return nReturn;
}

// ִ�в�ѯ���
int MySqlCommand::ExecuteScalar(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteScalar m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteScalar pMySQL is NULL" << std::endl;
		return 0;
	}
	//
	MySqlDataReader myMySqlDataReader;
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "MySqlCommand::ExecuteScalar error:" << lpszError << std::endl;
		return 0;
	}
	MYSQL_RES *m_pMySQL_Res = mysql_store_result(pMySQL);
	myMySqlDataReader.SetMySQLRes(pMySQL, m_pMySQL_Res);
	int nReturn = 0;
	if (myMySqlDataReader.Read())
	{
		nReturn = myMySqlDataReader.GetIntField(0);
	}
	myMySqlDataReader.Close();
	return nReturn;
}

// ִ�в�ѯ���
ISqlDataReader* MySqlCommand::ExecuteReader(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::m_pMySqlConnection is NULL" << std::endl;
		return NULL;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::pMySQL is NULL" << std::endl;
		return NULL;
	}
	//
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::error:" << lpszError << std::endl;
		return NULL;
	}
	MYSQL_RES *m_pMySQL_Res = mysql_store_result(pMySQL);
	MySqlDataReader *pMySqlDataReader = new MySqlDataReader(pMySQL, m_pMySQL_Res);
	return pMySqlDataReader;
}

// ִ�в�ѯ���
int MySqlCommand::ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "int MySqlCommand::ExecuteReader::m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "int MySqlCommand::ExecuteReader::pMySQL is NULL" << std::endl;
		return 0;
	}
	//
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "int MySqlCommand::ExecuteReader::error:" << lpszError << std::endl;
		return 0;
	}
	MYSQL_RES *pMySQL_Res = mysql_store_result(pMySQL);
	MySqlDataReader *pMySqlDataReader = (MySqlDataReader*)pSqlDataReader;
	pMySqlDataReader->SetMySQLRes(pMySQL, pMySQL_Res);
	return 1;
}

// 
void MySqlCommand::ExecuteBegin(void)
{
	if (m_pMySqlConnection == NULL)
	{
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		return;
	}
	//
	if (mysql_real_query(pMySQL, "START TRANSACTION", (unsigned long)strlen("START TRANSACTION")) != 0)
	{
		return;
	}
}

//
void MySqlCommand::ExecuteEnd(void)
{
	if (m_pMySqlConnection == NULL)
	{
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		return;
	}
	//
	if (mysql_real_query( pMySQL, "COMMIT", (unsigned long)strlen("COMMIT")) != 0)
	{
		return;
	}
}

// ɾ������
void MySqlCommand::DeleteThis(void)
{
	delete this;
}

#ifdef __MY_SQL__

// ��ȡMYSQL�������
ISqlCommand* GetStaticMySqlCommand()
{
	static MySqlCommand *pMySqlCommand = NULL;
	if (pMySqlCommand == NULL)
	{
		pMySqlCommand = new MySqlCommand();
	}
	return pMySqlCommand;
}

// ʵ����MYSQL�������
ISqlCommand* GetNewMySqlCommand()
{
	MySqlCommand *pMySqlCommand = new MySqlCommand();
	return pMySqlCommand;
}


#endif	// __MY_SQL__
