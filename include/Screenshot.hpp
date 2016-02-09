#ifndef SCREENSHOT_HPP
#define SCREENSHOT_HPP

// Required for taking screenshot. Platform dependent
#ifdef __gnu_linux__
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
#elif _WIN32 // Defined for both 32-bit and 64-bit environments
  //TODO
#else
  #error OS not supported
#endif

#include <vector>
#include <iostream>
#include <chrono> // Timestamps
#include <memory> // shared_ptr

// Required for image manipulations
#include <opencv2/opencv.hpp>
using cv::Mat;
using cv::imshow;
using cv::waitKey;

using namespace std;
using chrono::time_point;
using chrono::system_clock;

class Screenshot {
  // TODO: const corectness
  public:
    Screenshot()
      : imageData(this->Shot()),
        timestamp(this->TimestampSet())
    {}
    const time_point<system_clock> TimestampGet();
    const shared_ptr<const Mat> ImageGet();
    string LabelGet();
    // Only Label can be set
    void LabelSet(string text);

  private:
    #ifdef __gnu_linux__
      vector<uint8_t> Pixels; //TODO: const
      const shared_ptr<const Mat> Shot();
    #elif _WIN32 // Defined for both 32-bit and 64-bit environments
      //TODO
    #endif
    const time_point<system_clock>  TimestampSet(); // const?

    // Set during construction
    const shared_ptr<const Mat> imageData;
    const time_point<system_clock> timestamp; // = std::chrono::system_clock::now()

    string label;
};

#endif // SCREENSHOT_HPP
