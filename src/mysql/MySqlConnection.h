#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#if defined __WINDOWS__
	#include <winsock.h>
#endif

#include "mysql.h"
#include "ISqlDataBase.h"

class MySqlConnection : public ISqlConnection
{
private:

	/** @name  ˽�г�Ա���� */////////////////////////////////////////////////////
    /// @{

	// MySQL����
	MYSQL *m_pMySQL;

	/// @}

public:
	MySqlConnection(void);
	~MySqlConnection(void);
public:

	/** @name ������Ա���� *///////////////////////////////////////////////////
    /// @{

	// ��ȡ���ݿ����
	MYSQL* GetMySql(void);

	/// @}

public:

	/** @name ���Ա���� *///////////////////////////////////////////////////
    /// @{

	// �����ݿ�
	virtual int Open(const char *szHost, int nPort, const char *szUser, const char *szPassword, const char *szDBName);
	// �ر����ݿ�
	virtual void Close(void);
	// ɾ������
	virtual void DeleteThis(void);

	/// @}
};

#endif	// __MYSQL_CONNECTION_H__
