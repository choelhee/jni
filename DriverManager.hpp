



#ifndef _DRIVERMANGER_HPP_
#define _DRIVERMANGER_HPP_

#include "JDBCNativeInterface.hpp"
#include "Connection.hpp"

class DriverManager
{
	private:
		JDBCNativeInterface* mJDBC;
		JNIEnv*   mEnv;
		string    mDriverClass;
		string    mUrl;
		string    mUser;
		string    mPasswd;

		jclass    mCClass;
		jmethodID mMForName;

		jclass    mCClassLoader;
		jobject   mOClassLoader;
		jmethodID mMGetSystemClassLoader;

		jclass    mCDriverManager;
		jmethodID mMGetConnection;

	public:
		DriverManager( string aDriverClass );
		~DriverManager();
		Connection* getConnection( string aUrl, string aUser, string aPasswd );
};


#endif

