#include <ScreenshotManager.hpp>


ScreenshotManager::ScreenshotManager() {
  imProc = ImageProcessor();
  displayON = false;
}

void ScreenshotManager::Shot() {
  shared_ptr<Screenshot> scr = std::make_shared<Screenshot>(); // <--- Screenshot
  this->screenshots.push_back(scr);
}

void ScreenshotManager::Display(const int n, const bool timestampShow, const bool labelShow) {
  displayON = true;
  // TODO
  const shared_ptr<const Mat> ImageToDisplay = this->screenshots[n]->ImageGet();

  cv::namedWindow("Display", cv::WND_PROP_FULLSCREEN);
  cv::setWindowProperty("Display", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
  imshow("Display", *ImageToDisplay);

  int key = -1;
  while (true) {
    key = waitKey(10);
    if ( key == 27 ) { // Esc
      displayON = false;
      break;
    }
  }
}

void ScreenshotManager::MainLoop() {
  int key = -1;

  while (true) {
    // TODO: Linux - register global hotkey using xhklib
    // TODO: Win - AHK or try to register global hotkey on windows: https://msdn.microsoft.com/en-us/library/windows/desktop/ms646309%28v=vs.85%29.aspx
    key = waitKey(10);

    if ( key == 27 ) // Esc
      break;
    if ( key == 's' ) { // Screenshot
      this->Shot();
    }
    if ( key >= '1' && key <= '9' ) { // Display
      this->Display( (key - '0') % 48 ); // Convert char to int
    }
  }
}
