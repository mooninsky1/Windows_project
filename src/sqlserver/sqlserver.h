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
	//lihf 2018/09/30 ���Է������ݼ�
	void ExecuteSP3();
	void ExecuteRecordsetSQL();
	void ExecuteCommandSQL();
private:
	//����洢���̰󶨵Ĳ���
	bool DestroyParams();
	bool BindParams(LPCSTR pszName, DataTypeEnum enumDataType,  ParameterDirectionEnum enumDirType,int nSize, char * pszData);
	//lihf 2018/09/30 ȡ�ô洢���̷���ֵ��output����
	void GetReturnValueSP();
		/** �������ݿⷵ��ֵ
	@param   
	@param   
	@return  
	*/
	bool					FetchDBRetValue(_variant_t& varSource, LPSTR pszValue, int nLen);

private:
	////////////////////////���ݿ�����й�//////////////////////////////
	// COM _Command �������
	_CommandPtr				m_compCommand;

	// COM _Recordset ���������
	_RecordsetPtr			m_compRecordset;	

	// COM _Connection ���Ӷ���
	_ConnectionPtr			m_compConnection;

	// ���ش���
	int						m_nDBRetCode;

	// ��������
	char					m_szDBRetDesc[30];

};