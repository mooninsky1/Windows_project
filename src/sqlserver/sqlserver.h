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
	void ExecuteSP2();
	//lihf 2018/09/30 测试返回数据集
	void ExecuteSP3();
	void ExecuteRecordsetSQL();
	void ExecuteCommandSQL();
private:
	//清除存储过程绑定的参数
	bool DestroyParams();
	bool BindParams(LPCSTR pszName, DataTypeEnum enumDataType,  ParameterDirectionEnum enumDirType,int nSize, char * pszData);
	//lihf 2018/09/30 取得存储过程返回值跟output参数
	void GetReturnValueSP();
		/** 解析数据库返回值
	@param   
	@param   
	@return  
	*/
	bool					FetchDBRetValue(_variant_t& varSource, LPSTR pszValue, int nLen);

private:
	////////////////////////数据库对像有关//////////////////////////////
	// COM _Command 命令对象
	_CommandPtr				m_compCommand;

	// COM _Recordset 结果集对象
	_RecordsetPtr			m_compRecordset;	

	// COM _Connection 连接对象
	_ConnectionPtr			m_compConnection;

	// 返回代码
	int						m_nDBRetCode;

	// 返回描述
	char					m_szDBRetDesc[30];

};