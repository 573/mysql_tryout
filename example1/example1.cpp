// example1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "127.0.0.1"; // = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "mysql";
    char query[] = "SHOW VARIABLES";

    /* init mysql */
    conn = mysql_init(NULL);

    /* connect to database */
    if ( mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) )
    {
        /* execute query
        mysql_query gibt 0 zurück
        wenn alles ok ist
        */
        if ( !mysql_query(conn, query))
        {
            /* Result abholen */
            res = mysql_store_result(conn);
            /* Result durchlaufen */
            while ((row = mysql_fetch_row(res)) != NULL)
            {
				std::cout << row[0] << "=" << row[1] << "\n";
            }
            /* Result wieder freigeben */
            mysql_free_result(res);
        }
        else
        {
			std::cout << "Query failed! " << mysql_error(conn) << "\n";
        }
    }
    else
    {

        std::cout << "Connection failed! " << mysql_error(conn) << "\n";
    }

    /* close connection */
    mysql_close(conn);
	return 0;
}
