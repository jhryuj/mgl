#ifdef documentation
=========================================================================

     program: mglDisplayMouse.c
          by: justin gardner
        date: 02/10/07
   copyright: (c) 2007 Justin Gardner, Jonas Larsson (GPL see mgl/COPYING)
     purpose: mex function to display/hide the mouse
       usage: mglDisplayMouse(<display>)

$Id$
=========================================================================
#endif


/////////////////////////
//   include section   //
/////////////////////////
#include "mgl.h"

/////////////////////////
//   OS Specific calls //
/////////////////////////
void showCursor();
void hideCursor();

/////////////
//   main   //
//////////////
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  // if called with no arguments
  if (nrhs == 0) {
    // Restore cursor
    showCursor();
  }
  // if called with one argument
  else if (nrhs == 1) {
    int display = 1;
    if (mxGetPr(prhs[0]) != NULL) {
	    // get whether to display the cursor or not
	    display = (int) *mxGetPr( prhs[0] );
      if (display)
	      showCursor();
      else
	      hideCursor();
    }
    else {
      usageError("mglDisplayCursor");
      return;
    }
  }
}

//-----------------------------------------------------------------------------------///
// ******************************* mac specific code  ******************************* //
//-----------------------------------------------------------------------------------///
#ifdef __APPLE__
////////////////////
//   showCursor   //
////////////////////
void showCursor()
{
  // display cursor
  CGDisplayShowCursor( kCGDirectMainDisplay ) ; 
  // mexPrintf("Display cursor\n");
  //[NSCursor setHiddenUntilMouseMoves:false];
  //[NSCursor unhide];
  //[[NSCursor pointingHandCursor] set];
}
////////////////////
//   hideCursor   //
////////////////////
void hideCursor()
{
  // Hide cursor
  CGDisplayHideCursor( kCGDirectMainDisplay ) ; 
  // mexPrintf("Hide cursor\n");
  //[NSCursor setHiddenUntilMouseMoves:false];
  //[NSCursor hide];
}
#endif//__APPLE__
//-----------------------------------------------------------------------------------///
// ****************************** linux specific code  ****************************** //
//-----------------------------------------------------------------------------------///
#ifdef __linux__
#error Linux version undefined

////////////////////
//   showCursor   //
////////////////////
void showCursor()
{
}
////////////////////
//   hideCursor   //
////////////////////
void hideCursor()
{
}
#endif


//-----------------------------------------------------------------------------------///
// **************************** Windows specific code  ****************************** //
//-----------------------------------------------------------------------------------///
#ifdef _WIN32
#error Windows version undefined

////////////////////
//   showCursor   //
////////////////////
void showCursor()
{
}

////////////////////
//   hideCursor   //
////////////////////
void hideCursor()
{
}

#endif // _WIN32
