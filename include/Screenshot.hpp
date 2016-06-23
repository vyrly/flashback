#ifndef SCREENSHOT_HPP
#define SCREENSHOT_HPP

// Required for image manipulations
#include <SFML/Graphics.hpp> // Image
#include <vector>
#include <iostream>
#include <memory> // shared_ptr, make_shared
#include <chrono> // Timestamps
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <cstring> // memcpy

// X11.h must be the last header included in your .cpp file(s), because these smart guys define a macro named "None", which conflicts
// with SFML's sf::Style::None.
// http://en.sfml-dev.org/forums/index.php?topic=16882.0
// Required for taking screenshot. Platform dependent
#ifdef __gnu_linux__
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
#elif _WIN32 // Defined for both 32-bit and 64-bit environments
  //TODO
#else
  #error OS not supported
#endif

using namespace std;
using chrono::time_point;
using chrono::system_clock;

//------------------------------------------------------------------------------

class Screenshot {
  // TODO: const correctness
  public:
    Screenshot()
      : timestamp(this->TimestampSet())
    {
      originalImage = std::make_shared<sf::Image>();
      Shot();
    }
    // Image
    shared_ptr<sf::Image> ImageGet();
    // Timestamp
    const time_point<system_clock> TimestampGet();
    // Label
    string LabelGet();
    void LabelSet(string text); // Only Label can be set

  private:
    #ifdef __gnu_linux__
      vector<sf::Uint8> Pixels; //TODO: const
      void Shot();
    #elif _WIN32 // Defined for both 32-bit and 64-bit environments
      //TODO
    #endif

    const time_point<system_clock>  TimestampSet(); // const?
    // Set during construction
    shared_ptr<sf::Image> originalImage;
    const time_point<system_clock> timestamp; // = std::chrono::system_clock::now()

    string label;
};

#endif // SCREENSHOT_HPP
