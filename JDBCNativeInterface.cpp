


#include "JDBCNativeInterface.hpp"

JDBCNativeInterface* JDBCNativeInterface::mInstance = NULL;
string               JDBCNativeInterface::mClassPath = ".";

JDBCNativeInterface* JDBCNativeInterface::getInstance()
{
    if( mInstance == NULL )
    {
        mInstance = new JDBCNativeInterface();

        return mInstance;
    }

    return mInstance;
}

void JDBCNativeInterface::setClassPath( char* aClassPath )
{
    mClassPath = aClassPath;
}




JDBCNativeInterface::JDBCNativeInterface()
{
    jint sRet;
    string sClassPath( "-Djava.class.path=" );
    
    
    sClassPath += mClassPath;


    mVMargs.version = 0x00010002;
    JNI_GetDefaultJavaVMInitArgs( &mVMargs );
    mOptions[0].optionString= const_cast<char*>(sClassPath.c_str());
    mVMargs.options = mOptions; 
    mVMargs.nOptions = 1;  
    mVMargs.ignoreUnrecognized = JNI_TRUE;

    sRet = JNI_CreateJavaVM(&mJvm, (void**)&mEnv, &mVMargs );
    if( sRet != 0 )
    {
        PrintStackTrace( mEnv );
        return;
    }

}

JDBCNativeInterface::~JDBCNativeInterface()
{
    mJvm->DestroyJavaVM();
}


void JDBCNativeInterface::PrintStackTrace( JNIEnv* aEnv)
{
    jthrowable sThrow;
    sThrow = aEnv->ExceptionOccurred();
    if( sThrow != NULL )
    {
        aEnv->ExceptionDescribe();
        aEnv->ExceptionClear();
    }
}


