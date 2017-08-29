#include <jni.h>
#include <string.h>
#include <stdio.h>

// ��������PATH��windows�º�linux�µķָ������
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif


int main(void)
{
	JavaVMOption options[1];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;
	
	long status;
	jclass cls;
	jmethodID mid;
	jfieldID fid;
	jobject obj;
	
	options[0].optionString = "-Djava.class.path=.";
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_4;
	vm_args.nOptions = 1;
	vm_args.options = options;
	
	// ���������
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	
	if (status != JNI_ERR)
	{
		// �Ȼ��class����
		cls = env->FindClass("Sample2");
		if (cls != 0)
		{
			// ��ȡ����ID, ͨ����������ǩ��, ���þ�̬����
			mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;)Ljava/lang/String;");
			if (mid != 0)
			{
				const char* name = "World";
				jstring arg = env->NewStringUTF(name);
				jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, arg);
				const char* str = env->GetStringUTFChars(result, 0);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
			}
			
			/*** �½�һ������ ***/
			// ����Ĭ�Ϲ��캯��
			//obj = env->AllocObjdect(cls); 
			
			// ����ָ���Ĺ��캯��, ���캯�������ֽ���<init>
			mid = env->GetMethodID(cls, "<init>", "()V");
			obj = env->NewObject(cls, mid);
			if (obj == 0)
			{
				printf("Create object failed!\n");
			}
			/*** �½�һ������ ***/
			
			// ��ȡ����ID, ͨ����������ǩ��
			fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
			if (fid != 0)
			{
				const char* name = "icejoywoo";
				jstring arg = env->NewStringUTF(name);
				env->SetObjectField(obj, fid, arg); // �޸�����
			}
			
			// ���ó�Ա����
			mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
			if (mid != 0)
			{
				jstring result = (jstring)env->CallObjectMethod(obj, mid);
				const char* str = env->GetStringUTFChars(result, 0);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
			}
		}
		
		jvm->DestroyJavaVM();
		return 0;
	}
	else
	{
		printf("JVM Created failed!\n");
		return -1;
	}
}