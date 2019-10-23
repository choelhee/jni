

using namespace std;


#include <iostream>
#include <string>
#include <stdlib.h>
#include "JDBCNativeInterface.hpp"
#include "DriverManager.hpp"



int main()
{
    Connection*         conn = NULL;
    PreparedStatement*  stmt = NULL;
    int         ret  = 0;
    int         i = 0;
    int         end = 100000;

    long long   sBalance;
    long long   sBalanceID;
    long long   sAccID;
    long long   sServID;
    int         sAge;
    int         sPriority;


    JDBCNativeInterface::setClassPath( const_cast<char*>( "./mysql-connector-java-8.0.15.jar:." ) );

    DriverManager* dr = new DriverManager( "com.mysql.cj.jdbc.Driver" ); 
    
    conn = dr->getConnection( "jdbc:mysql://127.0.0.1:3306/test?serverTimezone=UTC",
                       "test",
                       "test" );

    stmt = conn->prepareStatement( "insert into acct_balance values(?, 1, ?, now(), now(), ?, 0, 0, 10, 1, '10A', '10A', '10A', now(), ?, ?, 1, 4, 1, 10, ?)" );
    if( stmt == NULL )
    {
        printf( "failed(), prepareStatement()\n" );
        return 0;
    }

    for( i = 1; i<= end; i++ )
    {
        sBalanceID = i;
        sBalance   = random() % 10000000000000000000UL;
        sAge       = (random() % (80 - 20 + 1)) + 20;
        sAccID     = sBalance;
        sServID    = sBalance;
        sPriority  = sBalance % 10;

        stmt->setInt( 1, sBalanceID );
        stmt->setInt( 2, sAge );
        stmt->setInt( 3, sBalance );
        stmt->setInt( 4, sAccID );
        stmt->setInt( 5, sServID );
        stmt->setInt( 6, sPriority );

        stmt->execute();
    }

    stmt->close();

    conn->close();
    return 0;
}
