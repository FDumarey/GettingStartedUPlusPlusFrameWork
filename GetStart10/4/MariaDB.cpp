#include <Core/Core.h> // includes core library
#include <MySql/MySql.h> // includes mysql library
#include <iostream> // library for console streaming

using namespace Upp;

#define SCHEMADIALECT <MySql/MySqlSchema.h> // using the MySQL schema definitions
#define MODEL <MariaDB/schema.sch> // your schema file within MyApps
#include <Sql/sch_header.h> // includes schema header library
#include <Sql/sch_source.h> // includes schema source library
#include <Sql/sch_schema.h> // includes schema schema library

CONSOLE_APP_MAIN
{
	char input; // a char type for user interaction on the console
	std::cout << "Demo application on MariaDB database\n"; // sends text to the console
	std::cin >> input; // press ENTER to continue
	
	MySqlSession session; // defines a MySQL session variable
	//user, password, database name, host, port
	if(session.Connect("user", "password", "dbname", "192.168.0.1", 3307)) 
	{
		std::cout << "Connected to database\n"; // connection successful
		std::cin >> input; // press ENTER to continue
		
		SQL = session; // SQL is a global variable, ok if you work with one database in project
		
		SqlSchema sch(MY_SQL); // definess a MySQL schema
		All_Tables(sch); // generates SQL scripts in the schema file
		
		SqlPerformScript(sch.Upgrade()); // updates the tables and columns if needed
		SqlPerformScript(sch.Attributes()); //updates the constraints and indices if needed
		SQL.ClearError(); // clears all errors before executing real queries
		
		try // we will do exception handling with the & operator, so a try...catch statement
		{
			int i; // defines an integer for a loop
			for(i=0;i<100;i++) // makes a loop of 101 iterations
			{
				// insert some data & operator = exception handling in code
				SQL & Insert(TEST_TABLE)(VALUE, Uuid::Create().ToString()); 
			}
			
			Sql sql; // defines a Sql object
			
			// selects data using * operator = manual check for errors
			sql * Select(ID, VALUE).From(TEST_TABLE).OrderBy(Descending(ID)).Limit(5); 
			
			while(sql.Fetch()) // fetches data from the sql query
				// use SqlId defined in the schema for returning values from the query
				Cout() << AsString(sql[0]) << ":" << AsString(sql[VALUE]) << "\n"; 
		}
		catch(SqlExc &ex) // catches errors of type SqlExc(eption)
		{
			Cerr() << "ERROR: " << ex << "\n"; // shows the error
			SetExitCode(1); // exits the application with error code 1 (0=no error)
		}
		
	}
	else
	{
		Cerr() << "ERROR: Unable to connect to the database\n"; // manually sets an error
		SetExitCode(1); // exits the application with error code 1 (0=no error)
	}
	
	std::cout << "End of application\n"; // application ended normally
}