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
	ExecuteSP();
	ExecuteSP1();
	ExecuteSP2();
	ExecuteSP3();
	//ExecuteRecordsetSQL();
	//ExecuteCommandSQL();
}


bool CSqlServerTest::Connect()
{
	// 连接数据库
	std::string hostName = "192.168.0.109";
	std::string dbName = "nodetest";
	std::string account = "sa";
	std::string password = "123456";
	char szConnect[1024];
	sprintf_s(szConnect, "Provider=SQLOLEDB.1;Data Source=%s;Initial Catalog=%s", hostName.c_str(), dbName.c_str());
	std::string connectstr = szConnect;
// 	HRESULT hr = m_compConnection->Open(_T( connectstr.c_str() ), _T( account.c_str() ), _T( password.c_str() ), adConnectUnspecified);
// 	
 	HRESULT hr = m_compConnection->Open(_T("Provider=SQLOLEDB.1;Data Source=192.168.0.109,1433;Initial Catalog=nodetest"), 
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

		if(!BindParams("@ret",adInteger,adParamReturnValue,4,NULL))
		{
			return ;
		}
		if(!BindParams("@returndesc",adVarChar,adParamOutput,30,NULL))
		{
			return ;
		}
		if(!BindParams("@name",adVarChar,adParamInput,30,"yhf"))
		{
			return ;
		}
		_variant_t vNull;
		vNull.vt=VT_ERROR;
		vNull.scode=DISP_E_PARAMNOTFOUND;
		m_compCommand->Execute(&vNull, &vNull, adCmdStoredProc);
		GetReturnValueSP();
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
	DestroyParams();
	try
	{
		m_compCommand->CommandText = "loaduser";
		m_compCommand->CommandType = adCmdStoredProc;

		if(!BindParams("@ret",adInteger,adParamReturnValue,4,NULL))
		{
			return ;
		}
		
		if(!BindParams("@returndesc",adVarChar,adParamOutput,30,NULL))
		{
			return ;
		}
		if(!BindParams("@name",adVarChar,adParamInput,30,"lhf"))
		{
			return ;
		}
	
		HRESULT hr = m_compRecordset->Open(_variant_t((IDispatch *)m_compCommand), vtMissing, adOpenForwardOnly, adLockReadOnly, adOptionUnspecified);		                       
		if(FAILED(hr))
		{
			return ;
		}
		GetReturnValueSP();
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
void CSqlServerTest::ExecuteSP2()
{
	DestroyParams();
	try
	{
		m_compCommand->CommandText = "loaduser";
		m_compCommand->CommandType = adCmdStoredProc;

		if(!BindParams("@ret",adInteger,adParamReturnValue,4,NULL))
		{
			return ;
		}
		if(!BindParams("@returndesc",adVarChar,adParamOutput,30,NULL))
		{
			return ;
		}
		if(!BindParams("@name1",adVarChar,adParamInput,30,"yhf"))
		{
			return ;
		}
		_variant_t vNull;
		vNull.vt=VT_ERROR;
		vNull.scode=DISP_E_PARAMNOTFOUND;
		m_compRecordset =  m_compCommand->Execute(NULL, NULL, adCmdStoredProc);
		
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
		//lihf 2018/09/29 execute()函数应该看成是直到m_precordset关掉以后才会正确返回 这样才能取得到output参数
		m_compRecordset->Close();
		GetReturnValueSP();
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
void CSqlServerTest::ExecuteSP3()
{
	DestroyParams();
	try
	{
		m_compCommand->CommandText = "loadalluser";
		m_compCommand->CommandType = adCmdStoredProc;

		if(!BindParams("@ret",adInteger,adParamReturnValue,4,NULL))
		{
			return ;
		}

		if(!BindParams("@returndesc",adVarChar,adParamOutput,30,NULL))
		{
			return ;
		}
		
		HRESULT hr = m_compRecordset->Open(_variant_t((IDispatch *)m_compCommand), vtMissing, adOpenForwardOnly, adLockReadOnly, adOptionUnspecified);		                       
		if(FAILED(hr))
		{
			return ;
		}
		GetReturnValueSP();
		int nRecordCount = m_compRecordset->GetRecordCount();
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
void CSqlServerTest::ExecuteRecordsetSQL()
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

void CSqlServerTest::ExecuteCommandSQL()
{
	char* strSQL = "SELECT * FROM users";
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

bool CSqlServerTest::BindParams( LPCSTR pszName, DataTypeEnum enumDataType, ParameterDirectionEnum enumDirType,int nSize, char * pszData )
{
	if(pszName == NULL || m_compCommand == NULL || m_compCommand->GetParameters() == NULL)
	{
		return false;
	}
	// 如果是输入或者输入输出参数，则转化成_variant_t格式
	_variant_t	vtParamValue;
	if(enumDirType == adParamInput || enumDirType == adParamInputOutput)
	{
		// 不能没有数据
		if(pszData == NULL)
		{
			return false;
		}

		switch(enumDataType)
		{
		case adTinyInt:
			{
				vtParamValue = _variant_t(*((BYTE*)pszData));
			}
			break;
		case adSmallInt:
			{
				vtParamValue = _variant_t((*((short*)pszData)));
			}
			break;
		case adUnsignedInt:
			{
				vtParamValue = _variant_t((*((DWORD*)pszData)));
			}
			break;
		case adInteger:
			{
				vtParamValue = _variant_t((*((int*)pszData)));
			}
			break;
		case adBigInt:
			{
				vtParamValue = _variant_t((*((__int64*)pszData)));				
			}
			break;
		case adSingle:
			{
				vtParamValue = _variant_t((*((float*)pszData)));	
			}
			break;
		case adDouble:
			{
				vtParamValue = _variant_t((*((double*)pszData)));
			}
			break;
		case adVarChar:
			{
				vtParamValue = _variant_t(pszData);
			}
			break;
		case adVarWChar:
			{
				vtParamValue = _variant_t((*((WCHAR*)pszData)));
			}
			break;
		case adBinary:
		case adVarBinary:
			{
#pragma warning (push)
#pragma warning (disable : 6387)	//warning C6387: “参数 1”可能是“0”: 
#pragma warning (disable : 6309)	//warning 6309: “参数 1”可能是“0”:
				int nRealSize = nSize;
				if (adParamInput == enumDirType) //保存数据库里,参数的大小按实际大小来保存
				{
					if (nRealSize <1) //配置长度小于1,即0长,返回错误
					{
						return false;
					}
					const char *pos = pszData + nRealSize-1; //指向变量尾部
					for (; pos > pszData; pos--) //至少要保存一位,所以处于第一位的时候,不再判断
					{
						if (*pos != 0)
						{
							break;
						}
					}

					nRealSize =  pos - pszData+1; //pos的位置可能因为循环的最后减1而处于前一位,所以这里要加1
				}
				SAFEARRAY * pSafeArray = SafeArrayCreateVectorEx(VT_UI1, 0, nRealSize, NULL);
#pragma warning (default : 6387)
#pragma warning (default : 6309)
#pragma warning (pop)
				if(pSafeArray == NULL)
				{
					return false;
				}

				HRESULT hr;
				for(int i = 0; i < nRealSize; i++)
				{
					hr = SafeArrayPutElement(pSafeArray, (long *)&i, (void*)(pszData + i));
					if(FAILED(hr))
					{
						return false;
					}
				}
				vtParamValue.vt = VT_ARRAY | VT_UI1;
				vtParamValue.parray = pSafeArray;
			}
			break;
		default:return false;
		}
	}

	_ParameterPtr __spparam = m_compCommand->CreateParameter(pszName, enumDataType, enumDirType , nSize, vtParamValue);
	HRESULT hr = m_compCommand->GetParameters()->Append(__spparam);
	if(FAILED(hr))
	{
		return false;
	}
	return true;
}

void CSqlServerTest::GetReturnValueSP()
{
	m_nDBRetCode = 0;
	*m_szDBRetDesc='\0';
	_variant_t vResultdesc;
	vResultdesc = m_compCommand->GetParameters()->GetItem("@returndesc")->GetValue();
	FetchDBRetValue(vResultdesc,m_szDBRetDesc,sizeof(m_szDBRetDesc));
	
	ParametersPtr pp = m_compCommand->GetParameters();
	if(pp != NULL)
	{
		// 取得返回值
		int count = pp->GetCount();

		for(long i = 0; i < count; i++)
		{
			_ParameterPtr pParameter = pp->GetItem(_variant_t(i));
			vResultdesc = pParameter->GetValue();
			if(pParameter != NULL && pParameter->Direction == adParamReturnValue)
			{
				// 取得参数值
				_variant_t varOutput = pParameter->GetValue();

				m_nDBRetCode = (int)varOutput;
				break;
			}
		}
	}
}

bool CSqlServerTest::FetchDBRetValue( _variant_t& varSource, LPSTR pszValue, int nLen )
{
	switch(varSource.vt)
	{
	case VT_I1:
	case VT_UI1:
		{
			if(nLen < sizeof(BYTE))
			{
				return false;
			}

			BYTE byValue = (BYTE)varSource;
			memcpy(pszValue, &byValue, sizeof(BYTE));
		}
		break;
	case VT_I2:
	case VT_UI2:
	case VT_BOOL:
		{
			if(nLen < sizeof(short))
			{
				return false;
			}

			short wValue = (short)varSource;
			memcpy(pszValue, &wValue, sizeof(short));
		}
		break;
	case VT_I4:
	case VT_INT:
		{
			if(nLen < sizeof(int))
			{
				return false;
			}

			int nValue = (int)varSource;
			memcpy(pszValue, &nValue, sizeof(int));
		}
		break;
	case VT_UI4:
	case VT_UINT:
		{
			if(nLen < sizeof(DWORD))
			{
				return false;
			}

			DWORD dwValue = (DWORD)varSource;
			memcpy(pszValue, &dwValue, sizeof(DWORD));
		}
		break;
	case VT_I8:
	case VT_UI8:
	case VT_DECIMAL:
		{
			if(nLen < sizeof(__int64))
			{
				return false;
			}

			__int64 i8Value = (__int64)varSource;
			memcpy(pszValue, &i8Value, sizeof(__int64));
		}
		break;
	case VT_R4:
		{
			if(nLen < sizeof(float))
			{
				return false;
			}

			float fValue = (float)varSource;
			memcpy(pszValue, &fValue, sizeof(float));
		}
		break;
	case VT_R8:
		{
			if(nLen < sizeof(double))
			{
				return false;
			}

			double dblValue = (double)varSource;
			memcpy(pszValue, &dblValue, sizeof(double));
		}
		break;
	case VT_BSTR:
	case VT_LPSTR:
	case VT_LPWSTR:
		{
			_bstr_t bstrValue = (_bstr_t)varSource;
			if(nLen < (int)bstrValue.length())
			{
				return false;
			}

			strncpy((char*)pszValue, (char *)bstrValue, strlen((char *)bstrValue) + 1);
		}
		break;
	case VT_ARRAY | VT_UI1:
		{			
			SAFEARRAY * pSafeArray = varSource.parray;

			char * pBuf = NULL;
			//一般只有一维数组,所以以一维数组的真实长度为准 qinjc add 2015.7.28
			unsigned long reallen =pSafeArray->rgsabound[0].cElements;
			SafeArrayAccessData(pSafeArray,(void **)&pBuf);	

			memcpy(pszValue, pBuf, reallen);
			//这里认为数据库里取出的长度不会超过配置的长度 qinjc add 2015.7.28
			memset(pszValue+reallen, 0, nLen-reallen);

			SafeArrayUnaccessData(pSafeArray); // 这句不能少			
		}
		break;
	case VT_NULL:
		{
			memset(pszValue, 0x00, nLen);
		}
		break;
	case VT_DATE:
		{
			_bstr_t bstrValue = (_bstr_t)varSource;
			if (nLen < (int)bstrValue.length())
				return false;
			strncpy((char*)pszValue, (char *)bstrValue, strlen((char *)bstrValue) + 1);
		}
		break;
	default:return false;
	}

	return true;
}



