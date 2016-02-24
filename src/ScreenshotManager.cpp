#include <ScreenshotManager.hpp>

ScreenshotManager::ScreenshotManager() {
  imProc = ImageProcessor();
  displayON = false;
}

void ScreenshotManager::Shot() {
  shared_ptr<Screenshot> scr = std::make_shared<Screenshot>(); // <--- Screenshot
  this->screenshots.push_back(scr);
  cout << "Shot " << this->screenshots.size() << endl;
}

void ScreenshotManager::Display(const int n, const bool timestampShow, const bool labelShow) {
  // Create window
  cv::namedWindow("Display", cv::WND_PROP_FULLSCREEN);
  // Make it fullscreen
  //cv::setWindowProperty("Display", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

  // TODO: Display time and label

  displayON = true;

  shared_ptr<const Mat> ImageToDisplay = this->screenshots[n]->ImageGet();

  // cvStartWindowThread();
  imshow("Display", *ImageToDisplay);
  cout << "Display ON" << endl;

  int key = -1;
  while (displayON) {
    key = waitKey(0);
    cout << key << endl; // DBG
    if ( key == 1048603 ) { // Esc: comparing to 27 don't work for all platforms: https://stackoverflow.com/questions/14494101/using-other-keys-for-the-waitkey-function-of-opencv
      cout << "Closing display" << endl;
      displayON = false;
    }
    if ( key >= '1' && key <= '9' ) { // Display
      cout << "Display" << endl;
      ImageToDisplay = this->screenshots[(key - '0') % 48]->ImageGet(); // Convert char to int // TODO make it safe
      imshow("Display", *ImageToDisplay);
    }
  }
  cv::destroyAllWindows();
  waitKey(1);
  waitKey(1);
  waitKey(1);
  waitKey(1); // WTF? - To close window? - https://stackoverflow.com/questions/6116564/destroywindow-does-not-close-window-on-mac-using-python-and-opencv
  cout << "Display OFF" << endl;
}
