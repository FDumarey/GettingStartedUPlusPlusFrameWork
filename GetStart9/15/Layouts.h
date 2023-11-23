#ifndef _Layouts_Layouts_h_
#define _Layouts_Layouts_h_

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <GetStart9/15/layouttabs.lay> // Layouts will be visible in all files that #include Layouts.h
#include <CtrlCore/lay.h>

// FirstTabDlg will be visible in all files that #include Layouts.h
struct FirstTabDlg : WithTab1<ParentCtrl> { // ParentCtrl is a good base class for tabs
	typedef FirstTabDlg CLASSNAME;
	FirstTabDlg();
};

#endif
