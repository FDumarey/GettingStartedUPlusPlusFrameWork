#include <Core/Core.h> // includes core library
#include <Skylark/Skylark.h> // includes skylark library
#include <MySql/MySql.h> // includes mysql/mariadb connectivity

using namespace Upp;

#define SCHEMADIALECT <MySql/MySqlSchema.h> // using the MySQL schema definitions
#define MODEL <GetStart12/2SQL/myapp.sch> // your schema file within MyApps
#include <Sql/sch_header.h> // includes schema files
#include <Sql/sch_source.h> // includes schema files
#include <Sql/sch_schema.h> // includes schema files

SKYLARK(HomePage, "") // defines handler homepage to url /myapp = root
{
    Sql sql; // defines a sql command
    sql * Select(ID, NAME, LASTNAME) // selects query for all info in the table
          .From(PERSON) // from the table person
          .OrderBy(LASTNAME, NAME); // sorted using lastname and then name
    ValueArray person; // defines a valuearray collection
    ValueMap vm; // defines a valuemap collection
    while(sql.Fetch(vm)) // executes the sql query and put in valuemap collection
        person.Add(vm); // adds info in valuearray
    http("PERSON", person) // defines element person with the valuearray
        .RenderResult("GetStart12/2SQL/index"); // using the witz template
}

struct MyApp : SkylarkApp { // makes a class inherited from SkylarkApp
	virtual void WorkThread(); // overrides the WorkThread function
    MyApp() { // default constructor
        root = "myapp"; // sets the root URL
        threads = 1; // databases do not like threads
    #ifdef _DEBUG // if in debug mode
        prefork = 0; // main thread handles http requests
        use_caching = false; // no caching
    #endif
    }
};

void InitModel() // used for database initialization
{
#ifdef _DEBUG
    SqlSchema sch(MY_SQL); // defines a mysql schema variable
    All_Tables(sch); // generates sql scripts in the schema file
    SqlPerformScript(sch.Upgrade()); // updates tables and columns
    SqlPerformScript(sch.Attributes()); // updates constraints and indices
    sch.SaveNormal(); // this will save all the scripts in you app directory
#endif
}

void OpenSQL(MySqlSession& mysql) // function to open a database
{
    if(!mysql.Connect("user", "password", "db", "192.168.0.1", 3307)) { // connects
        LOG("Can't create or open database file\n"); // error message
        Exit(1); // exits error code
    }
	#ifdef _DEBUG // if in debug mode
    mysql.LogErrors(); // logs errors to the console
    mysql.SetTrace(); // logs traces to the console
	#endif
    SQL = mysql; // sets the global SQL variable
    SQL.ClearError(); // clears all errors before executing real queries
}

void MyApp::WorkThread() // defines the worker thread
{
    MySqlSession mysql; // defines a new mysql session variable
    OpenSQL(mysql); // opens the database
    RunThread(); // runs the thread
}

void InitDB() // function for database initialization
{
    MySqlSession sqlsession; // defines a mysql session
    OpenSQL(sqlsession); // opens the database
    SqlSchema sch(MY_SQL); // instances a schema variable
    All_Tables(sch); // generates sql script in schema file
    SqlPerformScript(sch.Upgrade()); // updates table and columns
    SqlPerformScript(sch.Attributes()); // updates constraints and indices

    SQL * Insert(PERSON)(NAME,"Joe")(LASTNAME,"Smith"); // inserts some data in the table
    SQL * Insert(PERSON)(NAME,"Mike")(LASTNAME,"Carpenter"); // inserts some data
    SQL * Insert(PERSON)(NAME,"Jon")(LASTNAME,"Goober"); // inserts some data
}

CONSOLE_APP_MAIN // the entry macro for console applications
{
	#ifdef _DEBUG // if in debug mode
    StdLogSetup(LOG_FILE|LOG_COUT); // sets log to file and console
    Ini::skylark_log = true; // sets skylark logging on
	#endif
	InitDB(); // calls database initialization function
    MyApp().Run(); // runs the application
}