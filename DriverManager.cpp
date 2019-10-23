

#include "DriverManager.hpp"

DriverManager::DriverManager( string aDriverClass )
{
    JDBCNativeInterface* sJDBC;
    jstring sDriverClassStr;
    jboolean sInitFlag = JNI_TRUE;
    jobject sORet;

    mDriverClass = aDriverClass;

    sJDBC = JDBCNativeInterface::getInstance();
    mEnv = sJDBC->mEnv;

    
    /**
     * ClassLoader
     */
    mCClassLoader   = mEnv->FindClass( "java/lang/ClassLoader" );
    if( mCClassLoader == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    mMGetSystemClassLoader = mEnv->GetStaticMethodID( 
            mCClassLoader, 
            "getSystemClassLoader", 
            "()Ljava/lang/ClassLoader;");
    if( mMGetSystemClassLoader == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    mOClassLoader = mEnv->CallStaticObjectMethod( mCClassLoader, mMGetSystemClassLoader );
    if( mOClassLoader == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    /**
     * Class.forName(...)
     */
    mCClass   = mEnv->FindClass( "Ljava/lang/Class;" );
    if( mCClass == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    mMForName = mEnv->GetStaticMethodID( 
            mCClass, 
            "forName", 
            "(Ljava/lang/String;ZLjava/lang/ClassLoader;)Ljava/lang/Class;");
    if( mMForName == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    sDriverClassStr = mEnv->NewStringUTF( const_cast<char*>( mDriverClass.c_str() ) );
    if( sDriverClassStr == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    sORet = mEnv->CallStaticObjectMethod( 
            mCClass, 
            mMForName, 
            sDriverClassStr,
            sInitFlag,
            mOClassLoader);
    if( sORet == NULL )
    {
        printf("driver : %s\n", mDriverClass.c_str() );
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mCDriverManager = mEnv->FindClass( "java/sql/DriverManager" );
    if( mCDriverManager == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    mMGetConnection = mEnv->GetStaticMethodID( 
            mCDriverManager, 
            "getConnection", 
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/sql/Connection;");
    if( mMGetConnection == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
    }
}

DriverManager::~DriverManager()
{
}

Connection* DriverManager::getConnection( string aUrl, string aUser, string aPasswd )
{
    jobject sConnection;

    jstring sUrl;
    jstring sUser;
    jstring sPasswd;

    mUrl    = aUrl;
    mUser   = aUser;
    mPasswd = aPasswd;

    sUrl    = mEnv->NewStringUTF( const_cast<char*>( mUrl.c_str()    ) );
    sUser   = mEnv->NewStringUTF( const_cast<char*>( mUser.c_str()   ) );
    sPasswd = mEnv->NewStringUTF( const_cast<char*>( mPasswd.c_str() ) );

    sConnection = mEnv->CallStaticObjectMethod( mCDriverManager, mMGetConnection, sUrl, sUser, sPasswd );
    if( sConnection == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
    }

    return new Connection( sConnection );
}
