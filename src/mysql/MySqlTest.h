#include "ISqlDataBase.h"

class CMySqlDbMgr
{
public:
	int Init();
	static CMySqlDbMgr* GetInstance()
		{
			static CMySqlDbMgr db;
			return &db;
		}
private:
	// ���ݿ����Ӷ���
	ISqlConnection *m_pSqlConnection;
	// ���ݿ��������
	ISqlCommand *m_pSqlCommand;
	// ���ݿ��ȡ����
	ISqlDataReader *m_pSqlDataReader;

};

class CMySqlTest
{
public:
	static void Test();

};
