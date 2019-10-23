



#ifndef _CONNECTION_HPP_
#define _CONNECTION_HPP_

#include <jni.h>
#include "JDBCNativeInterface.hpp"
#include "Statement.hpp"
#include "PreparedStatement.hpp"

class Connection
{
	private:
		JDBCNativeInterface* mJDBC;
		JNIEnv*              mEnv;

		jclass  mCConnection;
		jobject mOConnection;
		jmethodID mMClose;
		jmethodID mMCommit;
		jmethodID mMRollback;
		jmethodID mMCreateStatement;
		jmethodID mMPrepareStatement;


	public:
		Connection( jobject aOConnection );
		~Connection();
		void close();
		void commit();
		void rollback();
		Statement*         createStatement();
		PreparedStatement* prepareStatement( string aSql );
};


#endif

