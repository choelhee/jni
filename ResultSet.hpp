


#ifndef _RESULTSET_HPP_
#define _RESULTSET_HPP_

#include "JDBCNativeInterface.hpp"

class ResultSet
{
	public:
		JDBCNativeInterface* mJDBC;
		JNIEnv*              mEnv;

		jclass  mCResultSet;
		jobject mOResultSet;

		jmethodID mMNext;
		jmethodID mMGetInt;

		ResultSet( jobject aOResultSet );
		~ResultSet();
		bool next();
		int  getInt( int aColumnIndex );
	
};


#endif
