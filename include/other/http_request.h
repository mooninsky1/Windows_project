//******************************************

//��C++��socket����Http��װ�࣬Neeao�޸�

//http://neeao.com

//2009-08-25

//******************************************



#if !defined(AFX_REQUEST_H__9F2C9BB6_CBA7_40AF_80A4_09A1CE1CE220__INCLUDED_)

#define AFX_REQUEST_H__9F2C9BB6_CBA7_40AF_80A4_09A1CE1CE220__INCLUDED_




#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000




#include <stdio.h>

#include <stdlib.h>

#include <string>

#include <winsock2.h>

#pragma comment(lib, "WS2_32")


using namespace std;

#define MEM_BUFFER_SIZE 10



/*

����25     HTTPRequest: Structure that returns the HTTP headers and message

  ����26                     from the request

	����27 */

typedef struct

{

	const char* headerSend;                               // Pointer to HTTP header Send

	const char* headerReceive;                            // Pointer to HTTP headers Receive

	const char* message;                                  // Pointer to the HTTP message

	long messageLength;                             // Length of the message

} HTTPRequest;



/*

����37     MemBuffer:  Structure used to implement a memory buffer, which is a

  ����38                 buffer of memory that will grow to hold variable sized

	����39                 parts of the HTTP message.

	  ����40 */

typedef struct

{

	unsigned    char *buffer;

	unsigned    char *position;

	size_t      size;

} MemBuffer;





class Request

{

public:

	Request();

	virtual ~Request();



private:

	void        MemBufferCreate(MemBuffer *b);

	void        MemBufferGrow(MemBuffer *b);

	void        MemBufferAddByte(MemBuffer *b, unsigned char byt);

	void        MemBufferAddBuffer(MemBuffer *b, unsigned char *buffer, size_t size);

	DWORD       GetHostAddress(LPCSTR host);

	void        SendString(SOCKET sock,LPCSTR str);

	BOOL        ValidHostChar(char ch);

	void        ParseURL(string url,const char* protocol,int lprotocol, const char* host,int lhost,const char* request,int lrequest,int *port);



	int         SendHTTP(string url,LPCSTR headerReceive,BYTE *post, DWORD postLength,HTTPRequest *req);



public:

	int     SendRequest(bool IsPost, string url, string& psHeaderSend, string& pszHeaderReceive,string& pszMessage);

};



#endif // !defined(AFX_REQUEST_H__9F2C9BB6_CBA7_40AF_80A4_09A1CE1CE220__INCLUDED_)
