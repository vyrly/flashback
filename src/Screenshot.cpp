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

  XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap); // TODO?
  Bpp = img->bits_per_pixel;

  // TODO: Size of a vector???
  Pixels.resize(Width * Height * 4);

  memcpy(&Pixels[0], img->data, Pixels.size());

  //TODO Conversion to RGBA 32 bit needed

  // Extract values for all pixels in image
  for(int y=0; y<Height; y++){
    for(int x=0; x<Width; x++){
      unsigned long c;
      XColor color;

      int centry;

      color.pixel = XGetPixel(img, x, y);

      // TODO: LUT for XGetPixel???

      XQueryColor(display, DefaultColormap(display, DefaultScreen (display)), &color);

      Pixels[(y*Width+x)*4] = color.red/256;
      Pixels[(y*Width+x)*4+1] = color.green/256;
      Pixels[(y*Width+x)*4+2] = color.blue/256;
      Pixels[(y*Width+x)*4+3] = 255;
    }
  }

  XDestroyImage(img);
  XCloseDisplay(display);

  if (Width && Height) {
    //TODO !!! The pixel array is assumed to contain 32-bits RGBA pixels, and have the given width and height. If not, this is an undefined behavior. If pixels is null, an empty image is created.
    originalImage->create(Width, Height, &Pixels[0]);
    // Don't work:
    // originalImage->loadFromMemory(img->data, Pixels.size());
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
