#include "sqlserver.h"
#include <string>
#include <iostream>
#include "tchar.h"

using namespace std;

CSqlServerTest::CSqlServerTest()
{
	Init();
}
CSqlServerTest::~CSqlServerTest()
{
	//State属性指明当前Connection对象的状态，0表示关闭，1表示已经打开
	if (m_compConnection->State)
	{
		m_compConnection->Close();
	}

	// COM _Connection 连接对象
	if(m_compConnection != NULL)
	{
		m_compConnection.Release();
		m_compConnection = NULL;
	}

	// COM _Recordset 结果集对象
	if(m_compRecordset != NULL)
	{
		m_compRecordset.Release();
		m_compRecordset = NULL;
	}

	// COM _Command 命令对象
	if(m_compCommand != NULL)
	{
		m_compCommand.Release();
		m_compCommand = NULL;
	}

	CoUninitialize();
}
bool CSqlServerTest::Init()
{
	CoInitialize(NULL);
	// COM _Command 命令对象		
	HRESULT hr = m_compCommand.CreateInstance(__uuidof(Command));
	if(FAILED(hr))
	{
		return false;
	}

	// COM _Recordset 结果集对象
	hr = m_compRecordset.CreateInstance(__uuidof(Recordset));
	if(FAILED(hr))
	{
		return false;
	}

	// COM _Connection 连接对象
	hr = m_compConnection.CreateInstance(__uuidof(Connection));
	if(FAILED(hr))
	{
		return false;
	}

	m_compRecordset->PutRefSource(m_compCommand);		
	m_compRecordset->CursorLocation = adUseClient;	
	m_compCommand->CommandType = adCmdStoredProc;	

	return true;
}

bool CSqlServerTest::DestroyParams(void)
{
	if(m_compCommand == NULL)
	{
		return false;
	}

	ParametersPtr pp = m_compCommand->GetParameters();

	if (pp == NULL)
	{
		return false;
	}

	// 清除_Command 命令对象参数
	try
	{		
		if(pp != NULL)
		{
			for(long i = pp->GetCount() - 1; i >= 0; i--)
			{
				pp->Delete(_variant_t(i));
			}
		}
	}
	catch(_com_error &adoerror)
	{
		// 通知上层
		char szWarnDesc[256] = { 0 };
	}
	return true;
}
void CSqlServerTest::Test()
{
	Connect();
	ExecuteSP1();
	ExecuteSP();
	ExecuteRecordsetCMD();
	ExecuteCommandCMD();
}


bool CSqlServerTest::Connect()
{
	// 连接数据库
	std::string hostName = "192.168.31.118,1029";
	std::string dbName = "nodetest";
	std::string account = "sa";
	std::string password = "123456";
	char szConnect[1024];
	sprintf_s(szConnect, "Provider=SQLOLEDB.1;Data Source=%s;Initial Catalog=%s", hostName.c_str(), dbName.c_str());
	std::string connectstr = szConnect;
// 	HRESULT hr = m_compConnection->Open(_T( connectstr.c_str() ), _T( account.c_str() ), _T( password.c_str() ), adConnectUnspecified);
// 	
 	HRESULT hr = m_compConnection->Open(_T("Provider=SQLOLEDB.1;Data Source=192.168.31.118,1029;Initial Catalog=nodetest"), 
 		_T("sa"), 
 		_T("123456"),
 		adConnectUnspecified);

	if(FAILED(hr))
	{
		return false;
	}
	//非常关键的一句，将建立的连接赋值给它 
	m_compCommand->ActiveConnection = m_compConnection;

	return true;
}

void CSqlServerTest::ExecuteSP()
{
	DestroyParams();
	try
	{
		m_compCommand->CommandText = "loaduser";
		m_compCommand->CommandType = adCmdStoredProc;

		_variant_t	vtParamValue;
		vtParamValue = _variant_t("lhf");
		_ParameterPtr __spparam = m_compCommand->CreateParameter("@returndesc", adVarChar, adParamOutput , 30, vtParamValue);
		HRESULT hr = m_compCommand->GetParameters()->Append(__spparam);
		if(FAILED(hr))
		{
			return ;
		}
		_variant_t	vtParamValue2;
		vtParamValue2 = _variant_t("lhf");
		_ParameterPtr __spparam2 = m_compCommand->CreateParameter(" @name", adVarChar,adParamInput , 30, vtParamValue2);
		hr = m_compCommand->GetParameters()->Append(__spparam2);
		if(FAILED(hr))
		{
			return ;
		}
		_variant_t vNull;
		vNull.vt=VT_ERROR;
		vNull.scode=DISP_E_PARAMNOTFOUND;
		//m_compCommand->Execute(&vNull, &vNull, adCmdStoredProc);
		m_compCommand->Execute(NULL, NULL, adCmdStoredProc);
	}
	catch (_com_error* e)
	{
		std::cout<<"exception\n";
	}
	catch (exception e)
	{
		std::cout<<"exception\n";
	}
	

}
void CSqlServerTest::ExecuteSP1()
{
	try
	{
		m_compCommand->CommandText = "loaduser";
		m_compCommand->CommandType = adCmdStoredProc;
		_variant_t	vtParamValue;
		_ParameterPtr __spparam = m_compCommand->CreateParameter("@returndesc", adVarChar, adParamOutput , 30, vtParamValue);
		HRESULT hr = m_compCommand->GetParameters()->Append(__spparam);
		if(FAILED(hr))
		{
			return ;
		}
		_variant_t	vtParamValue2;
		vtParamValue2 = _variant_t("lhf");
		_ParameterPtr __spparam2 = m_compCommand->CreateParameter(" @name", adVarChar,adParamInput , 30, vtParamValue2);
		hr = m_compCommand->GetParameters()->Append(__spparam2);
		if(FAILED(hr))
		{
			return ;
		}
	
		hr = m_compRecordset->Open(_variant_t((IDispatch *)m_compCommand), vtMissing, adOpenForwardOnly, adLockReadOnly, adOptionUnspecified);		                       
		if(FAILED(hr))
		{
			return ;
		}
		while(!m_compRecordset->adoEOF)
		{
			_variant_t varSource;
			//lihf 2018/09/27 取得字段user内容
			varSource = m_compRecordset->GetCollect("user");
			//varSource = m_compRecordset->GetCollect((_variant_t)((long)1));
			char szText[20];
			switch(varSource.vt)
			{
			case VT_BSTR:
			case VT_LPSTR:
			case VT_LPWSTR:
				{
					_bstr_t bstrValue = (_bstr_t)varSource;
					if(sizeof(szText) < (int)bstrValue.length())
					{
						break;;
					}

					memcpy(szText, (char *)bstrValue, strlen((char *)bstrValue) + 1);
					std::cout<<szText;
					break;
				}
			}
			m_compRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
	}
}
void CSqlServerTest::ExecuteRecordsetCMD()
{
	if(m_compRecordset->State != adStateClosed)
	{
		m_compRecordset->Close();
	}

	char* szSQL="SELECT * FROM users;";
	HRESULT hr = m_compRecordset->Open(_T("SELECT * FROM users;"),(IDispatch *)m_compConnection,adOpenDynamic,adLockOptimistic,adCmdText);
 	
	while(!m_compRecordset->adoEOF)
 	{
 		_variant_t varSource;
		//lihf 2018/09/27 取得字段user内容
 		varSource = m_compRecordset->GetCollect("user");
		//varSource = m_compRecordset->GetCollect((_variant_t)((long)1));
		char szText[20];
 		switch(varSource.vt)
 		{
		case VT_BSTR:
		case VT_LPSTR:
		case VT_LPWSTR:
			{
				_bstr_t bstrValue = (_bstr_t)varSource;
				if(sizeof(szText) < (int)bstrValue.length())
				{
					break;;
				}

				memcpy(szText, (char *)bstrValue, strlen((char *)bstrValue) + 1);
				std::cout<<szText;
				break;
			}
 		}
 		m_compRecordset->MoveNext();
 	}
}

void CSqlServerTest::ExecuteCommandCMD()
{
	char* strSQL = "SELECT * FROM users";
// 	_CommandPtr pCommamd;
// 	_RecordsetPtr pRecord;
// 	pCommamd.CreateInstance("ADODB.Command");
// 	pRecord.CreateInstance("ADODB.Recordset");
	try
	{
		m_compCommand->CommandText = _bstr_t(strSQL);
		m_compCommand->CommandType = adCmdText;

		m_compRecordset = m_compCommand->Execute(NULL,NULL,adCmdText);
		int icount = 0;
		icount = m_compRecordset->RecordCount;
		VARIANT vtValue;
		while(!m_compRecordset->adoEOF)
		{
			vtValue = m_compRecordset->GetCollect("user") ;
			char szText[20];
			switch(vtValue.vt)
			{
			case VT_BSTR:
			case VT_LPSTR:
			case VT_LPWSTR:
				{
					_bstr_t bstrValue = (_bstr_t)vtValue;
					if(sizeof(szText) < (int)bstrValue.length())
					{
						break;;
					}

					memcpy(szText, (char *)bstrValue, strlen((char *)bstrValue) + 1);
					std::cout<<szText;
					break;
				}
			}
			m_compRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{


	}
}



