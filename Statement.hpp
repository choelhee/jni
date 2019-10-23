

#ifndef _STATEMENT_HPP_
#define _STATEMENT_HPP_

#include <jni.h>
#include "JDBCNativeInterface.hpp"
#include "Statement.hpp"
#include "ResultSet.hpp"

class Statement
{
	protected:
		JDBCNativeInterface* mJDBC;
		JNIEnv*              mEnv;

		jclass  mCStmt;
		jobject mOStmt;

		jmethodID mMExecute;
		jmethodID mMExecuteUpdate;
		jmethodID mMExecuteQuery;

	public:
		Statement( jobject aOStmt );
		~Statement();
		bool       execute( string aSql );
		ResultSet* executeQuery( string aSql );
		int        executeUpdate( string aSql );
};


#endif
