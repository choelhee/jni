

#include "Connection.hpp"

Connection::Connection( jobject aOConnection )
{
    mJDBC        = JDBCNativeInterface::getInstance();
    mEnv         = mJDBC->mEnv;
    mOConnection = aOConnection;

    /**
     * get Connection class & method
     **/
    mCConnection   = mEnv->FindClass( "java/sql/Connection" );
    if( mCConnection == 0 ) 
    {   
        mJDBC->PrintStackTrace( mEnv );
        return;
    } 

    mMClose = mEnv->GetMethodID( mCConnection, "close", "()V" );
    if( mMClose == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mMCommit = mEnv->GetMethodID( mCConnection, "commit", "()V" );
    if( mMCommit == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }


    mMRollback = mEnv->GetMethodID( mCConnection, "rollback", "()V" );
    if( mMRollback == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mMCreateStatement = mEnv->GetMethodID( mCConnection, "createStatement", "()Ljava/sql/Statement;" );
    if( mMCreateStatement == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }

    mMPrepareStatement = mEnv->GetMethodID( mCConnection, "prepareStatement", "(Ljava/lang/String;)Ljava/sql/PreparedStatement;" );
    if( mMPrepareStatement == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return;
    }


}

Connection::~Connection()
{
}

void Connection::close()
{
    mEnv->CallVoidMethod( mOConnection, mMClose );
}

void Connection::commit()
{
    mEnv->CallVoidMethod( mOConnection, mMCommit );
}

void Connection::rollback()
{
    mEnv->CallVoidMethod( mOConnection, mMRollback );
}

Statement* Connection::createStatement()
{
    jobject sStmt;
    sStmt = mEnv->CallObjectMethod( mOConnection, mMCreateStatement );
    if( sStmt == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return NULL;
    }

    return new Statement( sStmt );
}

PreparedStatement* Connection::prepareStatement( string aSql )
{
    jobject sStmt;
    jstring sSql;

    sSql = mEnv->NewStringUTF( const_cast<char*>( aSql.c_str() ) );

    sStmt = mEnv->CallObjectMethod( mOConnection, mMPrepareStatement, sSql );
    if( sStmt == NULL )
    {
        mJDBC->PrintStackTrace( mEnv );
        return NULL;
    }

    return new PreparedStatement( sStmt );
}




