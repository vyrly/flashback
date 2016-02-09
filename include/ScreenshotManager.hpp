#ifndef SCREENSHOT_MANAGER_HPP
#define SCREENSHOT_MANAGER_HPP

#include <ImageProcessor.hpp>
#include <Screenshot.hpp>

using namespace std;

//------------------------------------------------------------------------------

class ScreenshotManager {
  public:
    ScreenshotManager();
    void Shot(); // Get screenshot using SreenshotProvider
    void Display(const int n, const bool timestampShow = true, const bool labelShow = true);

    void MainLoop();

  private:
    bool displayON;
    vector<shared_ptr<Screenshot>> screenshots;
    ImageProcessor imProc;
};

#endif // SCREENSHOT_MANAGER_HPP
