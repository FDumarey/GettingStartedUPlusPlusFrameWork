#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// Thread class
	
	Thread t; // defines a new thread instance
	t.Run([] { // runs a thread using a lambda function
		for (int i=0; i<10; i++) { // does a simple loop
		LOG("In the thread " << i); // logs that we are in the thread instance
		Sleep(100); // sleeps for 100ms
		}
		LOG("Thread is ending..."); // logs end of thread instance
		});
		
	for(int i=0; i<5; i++) // does a loop in the main thread
	{
		LOG("In the main thread " << i); // logs the counter
		Sleep(100); // sleeps for 100ms
	}
	LOG("Waiting for thread to finish...");
	t.Wait(); // waits for the thread to finish
	LOG("All threads finished");
	
	
	// Mutex
	
	Thread t2; // defines a new thread instance
	Mutex m; // defines a mutex to serialize a variable
	int sum=0; // defines the variable that will be protected by the mutex
	t2.Run([&sum, &m] // runs the thread using a lambda function
	{
		for(int i=0; i<100000; i++) // does a big loop
		{
			m.Enter(); // this will lock the mutex so other threads cannot write
			sum++; // increases value of variable
			m.Leave(); // this unlocks the mutex m, so giving access to sum again
		}
		});
	
	for(int i=0; i<100000;i++) // does a big loop in the main thread
	{
		Mutex::Lock __(m); // helper class of mutex to lock until the end of the {}
		sum++; // increases sum variable
	}
	
	t2.Wait(); // waits until the threads finishes
	DUMP(sum); // shows value
	
	
	// ConditionVariable
	
	bool stop = false; // defines a boolean
	BiVector<int> data; // defines a bivector instance of integers
	Mutex mu; // defines a mutex instance
	ConditionVariable cv; // defines a condition variable to control the thread flow
	
	Thread th; // defines a thread instance
	th.Run([&stop, &data, &mu, &cv] // runs the thread using a lambda function
	{
		Mutex::Lock __(mu); // locks the mutex inside the {}
		for (;;) // endless loop
		{
			while(data.GetCount()) // loops through data collection
			{
				int q = data.PopTail(); // pops an integer from the LIFO queue
				LOG("Data received: " << q); // logs data
			}
			if (stop) // checks if the stop variable is true
				break; // breaks the endless loop
			cv.Wait(mu); // waits for condition variable linked to mutex mu
		}
	});
	
	for (int i=0; i<10; i++) // a classic loop
	{
		{
			Mutex::Lock __(mu); // locks the mutex inside this scope
			data.AddHead(i); // adds integer to the LIFO queue
		}
		cv.Signal(); // signals the condition variable, so the thread is awakened
		Sleep(1); // waits 1ms
	}
	stop = true; // sets the stop boolean
	cv.Signal(); // awakens the thread using the condition variable
	t.Wait(); // waits for thread to finish
	
	
	// CoWork
	
	long lSum; // defines a long integer
	int iLoop; // defines an integer
	Mutex mCowork; // defines a mutex
	CoWork co; // defines an instance of cowork class
	
	for (iLoop=0; iLoop < 10; iLoop++) // loops 10 times
	{
		co & [&lSum, &mCowork] // starts a new thread from the worker thread pool
		{
			if(CoWork::IsCanceled()) // checks if all worker threads are canceled
			{
				LOG("Job was canceled"); // logs cancellation
				return; // returns from thread
			}
			Mutex::Lock __(mCowork); // uses a mutex to protect variable lsum
			// CoWork::FinLock(); // replaces the mutex, locked till end of job
			for (int i=0; i<99000;i++) // a big loop
				lSum += i; // adds integer to lsum
		};
	}
	co.Finish(); // waits for all worker threads to be finished
	co.Cancel(); // cancels all worker threads, running ones will execute until ended
	DUMP(lSum); // logs final result
	
	
	// AsyncWork
	
	auto a = Async([] (int n) -> double { // defines a async instance using a lambda function
		double f=1; // defines a double variable
		for(int i=2;i<=n;i++) // simple loop
			f *= i; // multiplication
		return f; // returns result
	}, 100);
	
	DUMP(a.Get()); // the get method waits for async thread to be finished
	
	
	// CoPartition
	
	int isum=0; // defines integer
	Vector<int> vdata; // defines a collection
	for(int i=0;i<10000;i++) // makes a big loop
		vdata.Add(i); // adds loop integers to the collection
	CoPartition(vdata, [&isum](const auto& subrange) { // parallel processing of arrays using a subrange
		int partial_sum=0; // a temporary variable
		for(const auto& x : subrange) // loops through the subrange using range for loop
			partial_sum += x; // summates results
		CoWork::FinLock(); // copartition inherits cowork so we can use finlock function
		isum += partial_sum; // collects subrange result
	});
	DUMP(isum); // shows result
	
	
	// CoDo
	
	Vector<String> sdata; // defines collection of strings
	for (int i=0; i<100; i++) // does a loop
		sdata.Add(AsString(1.0/i)); // adds rational number converted to string
	double dsum=0; // a double definition
	
	std::atomic<int> ii(0); //atomic variable, defined behavior when multiple threads write and read at the same time
	
	CoDo([&] { // defines a codo instance using a lambda function
		double m=0; // defines and initialize a double
		for (int i=ii++; i < sdata.GetCount(); i=ii++) // makes a loop
			m += atof(sdata[i]); // summates the collection data
		CoWork::FinLock(); // protects the variable from run conditions
		dsum += m; // adds the result
	});
	DUMP(dsum); // shows result
	
	
	// Parallel algorithms
	
	// define a collection of strings
	Vector<String> x {"zero", "one", "two", "three", "four", "five", "six", "seven"}; 
	DUMP(FindIndex(x, "two")); // finds the index using main thread function
	DUMP(CoFindIndex(x, "two")); // finds the index using concurrency function
	CoSort(x); // sorts the collection using concurrency function
	DUMP(x); // shows the resulting collection
}