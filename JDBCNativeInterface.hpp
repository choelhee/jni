

#ifndef _JDBCNATIVEINTERFACE_HPP
#define _JDBCNATIVEINTERFACE_HPP

using namespace std;

#include <jni.h>

#include <string>


class JDBCNativeInterface
{
	public:
		static JDBCNativeInterface* getInstance();
		static void                 setClassPath( char* aClassPath );
		JNIEnv*        mEnv;
		JavaVM*        mJvm;
		jobjectArray   mArgs;
		JavaVMInitArgs mVMargs;
		JavaVMOption   mOptions[1];
		void   PrintStackTrace( JNIEnv* aEnv );
	private:
		JDBCNativeInterface();
		~JDBCNativeInterface();
		static JDBCNativeInterface* mInstance;
		static string               mClassPath;

};


#endif

