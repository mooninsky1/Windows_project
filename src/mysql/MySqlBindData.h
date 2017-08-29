

#ifndef __MY_SQL_BIND_DATA_H__
#define __MY_SQL_BIND_DATA_H__

class MySqlBindData
{
protected:
	// ����
	int m_nLength;
	// ����������
	int m_nBufferType;
	// ������
	void *m_pBuffer;
public:
	MySqlBindData(void);
	~MySqlBindData(void);
public:
	// ������������
	void SetValue(int nValue);
	// ���ö���������
	void SetValue(short nValue);
	// �����ֽ�����
	void SetValue(char byValue);
	// �����ַ�����
	void SetValue(const char *lpszValue);
	// ���ö���������
	void SetValue(char *lpBinaryValue, int nBinaryLen);
public:
	// ��ȡָ�򳤶�ָ��
	int GetLength();
	// ��ȡ����������
	int GetBufferType();
	// ��ȡָ�򻺳���ָ��
	void* GetBufferPointer();
};


#endif	// __MY_SQL_BIND_DATA_H__
