#include <Screenshot.hpp>

#ifdef __gnu_linux__
void Screenshot::Shot() {
  // TODO: Make it cleaner and safe
  int Width = 0;
  int Height = 0;
  int Bpp = 0;

  Display* display = XOpenDisplay(nullptr);
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes = {0};
  XGetWindowAttributes(display, root, &attributes);

  Width = attributes.width;
  Height = attributes.height;

  XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
  Bpp = img->bits_per_pixel;
  Pixels.resize(Width * Height * 4);

  memcpy(&Pixels[0], img->data, Pixels.size());

  XDestroyImage(img);
  XCloseDisplay(display);

  if (Width && Height) {
    originalImage->create(Height, Width, &Pixels[0]);
  }
}
#elif _WIN32 // Defined for both 32-bit and 64-bit environments
  //TODO
#endif

const time_point<system_clock>  Screenshot::TimestampSet() {
  return system_clock::now();
}

const time_point<system_clock> Screenshot::TimestampGet(){
  return timestamp;
}

shared_ptr<sf::Image> Screenshot::ImageGet() {
  return originalImage;
}

string Screenshot::LabelGet() {
  return label;
}

void Screenshot::LabelSet(string text) {
  this->label = text;
}
