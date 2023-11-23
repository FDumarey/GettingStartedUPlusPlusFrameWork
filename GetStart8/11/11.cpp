#include <Core/Core.h> // includes core library
#include <windows.h> //includes the Win32 API

using namespace Upp;

void Alarm(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)  // defines timer callback function
{
	Cout() << "Timer callback function call with time:" << dwTime << '\n'; // shows the time
}

CONSOLE_APP_MAIN // console entry point
{
	MSG Msg; // defines a windows message variable
	UINT TimerId = SetTimer(NULL, 0, 1000, (TIMERPROC) &Alarm); // defines a timer
    Cout() << "TimerId: " << TimerId << '\n'; // shows the timerid of the new timer
    if (!TimerId) SetExitCode(99); // if no timerid is returned, then exit the application
    while (GetMessage(&Msg, NULL, 0, 0)) // gets messages from the desktop manager queue
    {
      if (Msg.message == WM_TIMER) Cout() << "Timer message received" << '\n'; // checks if timer message
      DispatchMessage(&Msg); // gets message from queue
    }
    KillTimer(NULL, TimerId); // deletes the timer
    SetExitCode(0); // exits the application with error code 0
}