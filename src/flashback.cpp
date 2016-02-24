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

// TODO
//#include <easylogging++.h>
//INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
// SCREENSHOT DEMO ON LINUX (X11)
//
//  // TODO: Make it cleaner and safe
//  int Width = 0;
//  int Height = 0;
//  int Bpp = 0;
//  std::vector<std::uint8_t> Pixels;
//
//  Display* display = XOpenDisplay(nullptr);
//  Window root = DefaultRootWindow(display);
//
//  XWindowAttributes attributes = {0};
//  XGetWindowAttributes(display, root, &attributes);
//
//  Width = attributes.width;
//  Height = attributes.height;
//
//  XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
//  Bpp = img->bits_per_pixel;
//  Pixels.resize(Width * Height * 4);
//
//  memcpy(&Pixels[0], img->data, Pixels.size());
//
//  XDestroyImage(img);
//  XCloseDisplay(display);
//
//  cv::Mat image = cv::Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]);
//
//  cv::namedWindow("ww", cv::WINDOW_AUTOSIZE);
//  cv::imshow("ww", image);
//
//  cv::waitKey(0);
//
//  return 0;

  ScreenshotManager ScrMan = ScreenshotManager();

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
            ScrMan.Display(0); // -> Open screenshot manager
            // TODO: Don't diplay manager if it's already open
          }
        }
        else if (XLookupKeysym(&ev.xkey, 0) == XK_Print ) {
          if ((ev.xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod4Mask)) == None) {
            ScrMan.Shot(); // -> Take a shot
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
