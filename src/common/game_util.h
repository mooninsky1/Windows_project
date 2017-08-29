#pragma once
#include <string>
#include <stdio.h>
#include <sys/time.h>
#include <map>


std::string GetTimeSecond();
class cTimeEscape;

class cTimeEscape
{
public:
    cTimeEscape(const char* tag,bool bPrint=false):m_bPrint(bPrint)
    {
        m_strTag = tag;
        gettimeofday(&m_timestart, NULL);
        m_strTimeStart = GetTimeSecond();
		m_pTimeFather = NULL;
    }
    ~cTimeEscape();
    
public:
	//�۲�����ģ�������
	void Register(cTimeEscape* Father);
	//�ռ�����
	void GetDate(std::string strTag,double timecost);
private:
	bool m_bPrint;//���Ǵ�ӡ������ʱ������
    timeval m_timestart;
    std::string m_strTag;
    std::string m_strTimeStart;
	cTimeEscape* m_pTimeFather;
	std::multimap<std::string,double> m_mapTagTime;
};


