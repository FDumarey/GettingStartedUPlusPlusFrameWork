#include <Core/Core.h> // includes core library
#include <Skylark/Skylark.h> // includes the Skylark library

using namespace Upp;

SKYLARK(HomePage, "") // makes a handler for the root URL - http://127.0.0.1/myapp
{
    http << "<!DOCTYPE html><html><body>Welcome to Skylark web services!</body></html>";
}

SKYLARK(Param, "*/param") // makes a handler to capture a single parameter
{
    http << "<!DOCTYPE html><html><body>Parameter: " << http[0] << "</html></body>";
}

SKYLARK(Params, "params/**") // makes a handler for multiple parameters
{
    http << "<!DOCTYPE html><html><body>Parameters: ";
    for(int i = 0; i < http.GetParamCount(); i++) // loops through all the parameters
        http << http[i] << " "; // [] operator will show the parameter
    http << "</html></body>";
}

SKYLARK(CatchAll, "**") // makes a handler for all other url's
{
    http.Redirect(HomePage); // redirects to the Homepage
}

SKYLARK(Witz, "/witz") // makes a handler for the /witz URL
{
    ValueArray va; // defines a value array
    va.Add(1); // adds an integer
    va.Add("Hello"); // adds a string
    
    ValueMap m; // defines a value map type
    m.Add("key1", "first value"); // adds a key and value
    m.Add("key2", "second value"); // adds a key and value

    http("MyValue", "some value") // defines a element MyValue with a value
        ("MyRawValue", Raw("<b>raw <u>html</u></b>")) // defines an explicit raw value
        ("MyRawValue2", "<b>another raw <u>html</u></b>") // defines a raw value in a value
        ("MyArray", va) // defines a container type as element
        ("MyMap", m) // defines a map type as element
        // render using the index witz template
        // or render using the index2 witz template for include and define example
        .RenderResult("GetStart12/2/index2");
}

SKYLARK(Get,"/get")
{
	http.RenderResult("GetStart12/2/get");
}

SKYLARK(Submit,"/submit")
{
	http("RESULT", ToUpper((String)http["id"]))
		.RenderResult("GetStart12/2/submit");
}

SKYLARK(Post,"/post")
{
	http.RenderResult("GetStart12/2/post");
}

SKYLARK(SubmitPost,"submit:POST")
{
	http("RESULT", ToUpper((String)http["id"]))
		.RenderResult("GetStart12/2/submit");
}

SKYLARK(Session, "/session")
{
    http.RenderResult("GetStart12/2/session");
}

SKYLARK(SubmitList, "submitsession:POST")
{
    Value h = http[".LIST"]; // copies current .LIST session collection to value h
    ValueArray va; // defines a valuearray
    if(IsValueArray(h)) // if .LIST already contains elements
        va = h; // copies existing container to the valuearray
    va.Add(http["id"]); // adds the id "name" to the collection
    http.SessionSet(".LIST", va); // sets the .list session to the collection
    http.Redirect(Session); // redirects to the session url
}

SKYLARK(Ajax, "/ajax")
{
    http.RenderResult("GetStart12/2/ajax");
}

SKYLARK(Add, "add:POST")
{
    // nvl = return first non null value
    String r = AsString(Nvl(http.Int("number1")) + Nvl(http.Int("number2"))); 
    http.Ux("result", "The result is: " + r) // replaces result text by the sum in html
        .UxSet("number1", r); // sets the value of number1 to the sum
}

struct MyApp : SkylarkApp { // makes a class inherited from the skylarkapp class
    MyApp() // defines the constructor for the application
    {
        root = "myapp"; // sets the root url to myapp
        port = 80; // sets the web server TCP port to 80
    	#ifdef _DEBUG // if we are in debug mode
        prefork = 0; // main process will handle http requests directly
        use_caching = false; // no caching is used
    	#endif
    }
};

CONSOLE_APP_MAIN // the entry point of the application
{
	#ifdef _DEBUG // if we are in debug mode
    StdLogSetup(LOG_FILE|LOG_COUT); // outputs log to log file and the console output
    Ini::skylark_log = true; // enables skylark logging
	#endif
    
    MyApp().Run(); // runs our application
}