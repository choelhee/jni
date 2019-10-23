

#ifndef _PreparedStatement_HPP_
#define _PreparedStatement_HPP_

#include <jni.h>
#include "JDBCNativeInterface.hpp"
#include "Statement.hpp"
#include "ResultSet.hpp"

class PreparedStatement : public Statement
{
	private:
		jmethodID mMSetInt;
		jmethodID mMSetLong;
		jmethodID mMSetString;
		jmethodID mMExecute;

	public:
		PreparedStatement( jobject aOStmt );
		~PreparedStatement();
		void setInt( int aParameterIndex, int aValue );
		void setLong( int aParameterIndex, long long aValue );
		void setString( int aParameterIndex, string aStr );
		bool execute();
};


#endif
