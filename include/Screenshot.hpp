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
#include <memory> // shared_ptr

#include <chrono> // Timestamps
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time

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
      : originalImage(this->Shot()),
        timestamp(this->TimestampSet())
    {
      //cout << "Copying Screenshot" << endl;
      overlayedImage = make_shared<Mat>(*originalImage, cv::Range::all(), cv::Range::all());
      //cout << "Creating Timestamp string" << endl;
      auto in_time_t = std::chrono::system_clock::to_time_t(timestamp);
      std::stringstream ss;
      ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

      int fontFace = cv::FONT_HERSHEY_PLAIN;
      double fontScale = 1;
      int thickness = 1;
      cv::Point textOrg(5, 20);
      //cout << "Adding text to image" << endl;
      // TODO: Display label
      putText( *overlayedImage, ss.str(), textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness, cv::LINE_AA);
    }
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
    const shared_ptr<const Mat> originalImage;
    const time_point<system_clock> timestamp; // = std::chrono::system_clock::now()

    // Modified Screenshot
    shared_ptr<Mat> overlayedImage;

    string label;
};

#endif // SCREENSHOT_HPP
