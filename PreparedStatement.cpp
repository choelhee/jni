

#include "PreparedStatement.hpp"

PreparedStatement::PreparedStatement( jobject aOStmt ) : Statement( aOStmt )
{
    mJDBC = JDBCNativeInterface::getInstance();
    mEnv  = mJDBC->mEnv;

    mOStmt = aOStmt;

    mCStmt = mEnv->FindClass( "java/sql/PreparedStatement" );
    if( mCStmt == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mMSetInt = mEnv->GetMethodID( mCStmt, "setInt", "(II)V" );
    if( mMSetInt == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }
    mMSetLong = mEnv->GetMethodID( mCStmt, "setLong", "(IJ)V" );
    if( mMSetLong == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

    mMSetString = mEnv->GetMethodID( mCStmt, "setString", "(ILjava/lang/String;)V" );
    if( mMSetString == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

    mMExecute = mEnv->GetMethodID( mCStmt, "execute", "()Z" );
    if( mMExecute == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

}

PreparedStatement::~PreparedStatement()
{
}

void PreparedStatement::setInt( int aParameterIndex, int aValue )
{
    mEnv->CallVoidMethod( mOStmt, mMSetInt, aParameterIndex, aValue );
}

void PreparedStatement::setLong( int aParameterIndex, long long aValue )
{
    mEnv->CallVoidMethod( mOStmt, mMSetLong, aParameterIndex, aValue );
}

void PreparedStatement::setString( int aParameterIndex, string aStr )
{
}

bool PreparedStatement::execute()
{
    jboolean sRet;

    sRet = mEnv->CallBooleanMethod( mOStmt, mMExecute );
    if( sRet == JNI_TRUE )
    {   
        return true;
    }   

    mJDBC->PrintStackTrace( mEnv );
    return false;
}




