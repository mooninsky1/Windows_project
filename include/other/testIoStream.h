#include "../common/iStream.h"
#include <vector>
struct PlayerDog
{
	// ���ĵȼ�
	int uDogLevel;
	// ����ID
	int uDogID;
	// ��������
	int uDogIndex;
	// ���ľ���
	int uDogExperience;
	// �����Ǽ�
	int uDogStar;
	// ���ĳɳ�
	int uDogGrowup;
	// ��������
	int uDogMood;
	// ��������
	int uDogForce;
	// ��������
	int uDogCel;
	// ��������
	int uDogSurface;
	// ��������
	char szDogName[17];

	//
	PlayerDog()
	{
		Clear();
	}
	//
	void Clear()
	{
		// ���ĵȼ�
		uDogLevel = 0;
		// ����ID
		uDogID = 0;
		uDogIndex = 0;
		// ���ľ���
		uDogExperience = 0;
		uDogStar = 0;
		uDogGrowup = 0;
		uDogMood=0;
		uDogForce = 0;
		uDogCel = 0;
		uDogSurface = 0;
		// ��������
		memset(szDogName, 0, sizeof(szDogName));
	}
	bool To_Stream(nsCommon::cOStream &Ostream)
	{
		//int version = 1;
		int version = 2;

		Ostream  << version << uDogLevel<<uDogID <<uDogIndex<<uDogExperience<< uDogStar << uDogGrowup <<uDogMood << uDogSurface
			<< uDogCel << uDogSurface;
		return true;
	}
	bool From_Stream(nsCommon::cIStream &Istream)
	{
		int version;
		int uDogLevel = 0;
		int uDogID = 0;
		Istream >> version;
		if (version == 1)
		{
			int uDogLevel =2;
			Istream >> uDogLevel;
		}
// 		Istream >>uDogID >>uDogIndex>>uDogExperience>> uDogStar >> uDogGrowup >>uDogMood >> uDogSurface
// 			>> uDogCel >> uDogSurface;
		else if (version == 2)
		{
			Istream >> uDogID >>uDogIndex>>uDogExperience>> uDogStar >> uDogGrowup >>uDogMood >> uDogSurface
				>> uDogCel >> uDogSurface;
		}

		return true;
	}
};

void Test()
{
	std::vector<PlayerDog> vecDog;
	int n = 10; 
	for (int i=0; i<n; i++)
	{
		PlayerDog  tempDog;
		tempDog.uDogID = i;
		vecDog.push_back(tempDog);
	}
	nsCommon::cIStream Istream;
	nsCommon::cOStream Ostream;

	
	for (int i=0; i < n; i++)
	{
		PlayerDog tempdog = vecDog[i];
		Ostream << n;
		tempdog.To_Stream(Ostream);
	}
	std::vector<PlayerDog> vecDog1;
	nsCommon::cStreamBinaryBufferReader binareader(0,0);
	int size = Ostream.GetDataSize();
	binareader.SetData(Ostream.GetData(),Ostream.GetDataSize());
	Istream.SetReader(&binareader);
	int cout;
	Istream>>cout;
	for (int i = 0 ; i <cout; i++)
	{
		PlayerDog tempdog;
		tempdog.From_Stream(Istream);
		vecDog1.push_back(tempdog);
	}
	
	
}