

#include "ResultSet.hpp"


ResultSet::ResultSet( jobject aOResultSet )
{
    mJDBC = JDBCNativeInterface::getInstance();
    mEnv  = mJDBC->mEnv;

    mOResultSet = aOResultSet;

    mCResultSet = mEnv->FindClass( "java/sql/ResultSet" );
    if( mCResultSet == NULL )
    {
         mJDBC->PrintStackTrace( mEnv );
         return;
    }

    mMNext = mEnv->GetMethodID( mCResultSet, "next" , "()Z" );
    if( mMNext == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

    mMGetInt = mEnv->GetMethodID( mCResultSet, "getInt" , "(I)I" );
    if( mMNext == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

}

ResultSet::~ResultSet()
{
}

bool ResultSet::next()
{
    jboolean sHasRecord;

    sHasRecord = mEnv->CallBooleanMethod( mOResultSet, mMNext );
    if( sHasRecord == JNI_TRUE )
    {
        return true;
    }

    mJDBC->PrintStackTrace( mEnv );
    return false;
}

int ResultSet::getInt( int aColumnIndex )
{
    jint sRet;
    jint sColumnIndex = aColumnIndex;

    sRet = mEnv->CallIntMethod( mOResultSet, mMGetInt, sColumnIndex );
    return sRet;
}
