#include <plugin/zip/zip.h> // includes zip library

using namespace Upp;

CONSOLE_APP_MAIN {
	String filename = GetHomeDirFile("test.zip"); // defines file in homefolder

	// make a zip file
	FileZip zipfile(filename); // makes a filezip variable
	zipfile.WriteFolder("Folder1", GetSysTime()); // makes a folder
	
	// direct string write to a file
	zipfile.WriteFile(String("some data to test the zip"), "Folder1/string.txt");
	// copies a file to a file
	zipfile.WriteFile(LoadFile(GetDataFile("15.cpp")),"Folder1/zipsource.cpp");
	// uses a file handler to a zip file
	zipfile.BeginFile("file.txt");
	String somedata = "some other test data";
	zipfile.Put(somedata, strlen(somedata));
	zipfile.EndFile();
	// uses a stream handler to a zip file
	OutFilterStream outstream;;
	zipfile.BeginFile(outstream, "stream.txt");
	outstream << "some content";
	outstream.Close();
	// performs zip operation and check if okay
	if(zipfile.Finish())
		Cout() << filename << " zip file created succesfully\n\n";
	
	
	// unzip a zip file
	FileUnZip unzip(filename); // makes a fileunzip variable
	while(!(unzip.IsEof() || unzip.IsError())) { // repeats until end of file or error
		Cout() << "Path: " << unzip.GetPath(); // shows path
		Cout() << " ,time: " << unzip.GetTime() << '\n'; // shows time
		if(!unzip.IsFolder()) { // if object is file
			Cout() << "Size: " << unzip.GetLength(); // shows its size
			Cout() << " ,content: " << unzip.ReadFile().Left(100) << '\n'; // shows first 100 chars
		}
		else
			unzip.SkipFile(); // if folder then skip file
	}
}