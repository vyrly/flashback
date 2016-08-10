#include <ScreenshotManager.hpp>

// Required for global hotkey. Platform dependent
#ifdef __gnu_linux__
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
#elif _WIN32 // Defined for both 32-bit and 64-bit environments
  //TODO
#else
  #error OS not supported
#endif

// TODO ???
//#include <easylogging++.h>
//INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
  ScreenshotManager ScrMan;

  // TODO: separate hotkey code
  // Global Hotkey based on https://stackoverflow.com/questions/4037230/global-hotkey-with-x11-xlib

  Display*    dpy     = XOpenDisplay(0);
  Window      root    = DefaultRootWindow(dpy);
  XEvent      ev;

  unsigned int    modifiers       = AnyModifier; // TODO: configurable

  int             keycode1         = XKeysymToKeycode(dpy,XK_Pause); // TODO: configurable
  int             keycode2         = XKeysymToKeycode(dpy,XK_Print); // TODO: configurable

  Window          grab_window     = root;
  Bool            owner_events    = False;
  int             pointer_mode    = GrabModeAsync;
  int             keyboard_mode   = GrabModeAsync;

  XGrabKey(dpy, keycode1, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
  XGrabKey(dpy, keycode2, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);

  XSelectInput(dpy, root, KeyPressMask);
  while(true)
  {
    XNextEvent(dpy, &ev);

    switch (ev.type)  {
      case KeyPress:
        if (XLookupKeysym(&ev.xkey, 0) == XK_Pause ) {
          if ((ev.xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod4Mask)) == None) {
            cout << "Open screenshot manager" << endl;
            ScrMan.Main(); // ---> Open screenshot manager
            // TODO: Don't diplay manager if it's already open
            // TODO: Display last opened screenshot
          }
        }
        else if (XLookupKeysym(&ev.xkey, 0) == XK_Print ) {
          if ((ev.xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod4Mask)) == None) {
            ScrMan.Shot(); // ---> Make a screenshot
          }
        }
      default:
        break;
    }
  }

  XUngrabKey(dpy,keycode1,modifiers,grab_window);
  XUngrabKey(dpy,keycode2,modifiers,grab_window);
  XCloseDisplay(dpy);
}
