

#include "Statement.hpp"


Statement::Statement( jobject aOStmt )
{
    mJDBC = JDBCNativeInterface::getInstance();
    mEnv  = mJDBC->mEnv;

    mOStmt = aOStmt;

    mCStmt = mEnv->FindClass( "java/sql/Statement" );
    if( mCStmt == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mMExecute = mEnv->GetMethodID( mCStmt, "execute", "(Ljava/lang/String;)Z" );
    if( mMExecute == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }


    mMExecuteUpdate = mEnv->GetMethodID( mCStmt, "executeUpdate", "(Ljava/lang/String;)I" );
    if( mMExecuteUpdate == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

    mMExecuteQuery = mEnv->GetMethodID( mCStmt, "executeQuery", "(Ljava/lang/String;)Ljava/sql/ResultSet;" );
    if( mMExecuteQuery == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;

    }

}

Statement::~Statement()
{
}

bool Statement::execute( string aSql )
{
    jstring  sSql;
    jboolean sRet;

    sSql = mEnv->NewStringUTF( const_cast<char*>( aSql.c_str() ) );

    sRet = mEnv->CallBooleanMethod( mOStmt, mMExecute, sSql );
    if( sRet == JNI_TRUE )
    {
        return true;
    }

    mJDBC->PrintStackTrace( mEnv );
    return false;
}



ResultSet* Statement::executeQuery( string aSql )
{
    jstring sSql;
    jobject sOResultSet;

    sSql = mEnv->NewStringUTF( const_cast<char*>( aSql.c_str() ) );

    sOResultSet = mEnv->CallObjectMethod( mOStmt, mMExecuteQuery, sSql );
    if( sOResultSet == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return NULL;
    }
    return new ResultSet( sOResultSet );
}

int Statement::executeUpdate( string aSql )
{
    jstring sSql;
    jint    sRet;

    sSql = mEnv->NewStringUTF( const_cast<char*>( aSql.c_str() ) );

    sRet = mEnv->CallIntMethod( mOStmt, mMExecuteUpdate, sSql );
    if( sRet == 0 )
    {
        mJDBC->PrintStackTrace( mEnv );
        return sRet;

    }

    return sRet;
}




