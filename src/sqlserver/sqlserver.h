#pragma once

#ifdef WIN32
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF", "adoEOF")
#endif

class CSqlServerTest
{
public:
	CSqlServerTest();
	~CSqlServerTest();
	void Test();
protected:
	bool Init();
	bool Connect();
	void ExecuteSP();
	void ExecuteSP1();
	void ExecuteRecordsetCMD();
	void ExecuteCommandCMD();
private:
	//清除存储过程绑定的参数
	bool DestroyParams();
private:
	////////////////////////数据库对像有关//////////////////////////////
	// COM _Command 命令对象
	_CommandPtr				m_compCommand;

	// COM _Recordset 结果集对象
	_RecordsetPtr			m_compRecordset;	

	// COM _Connection 连接对象
	_ConnectionPtr			m_compConnection;

};