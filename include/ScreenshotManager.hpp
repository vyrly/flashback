#ifndef SCREENSHOT_MANAGER_HPP
#define SCREENSHOT_MANAGER_HPP

#include <ImageProcessor.hpp>
#include <Screenshot.hpp>

using namespace std;

//------------------------------------------------------------------------------

class ScreenshotsSet {
  public:
    ScreenshotsSet() {}
    ScreenshotsSet(shared_ptr<Screenshot> scr) {
      set.push_back(scr);
    }
    void push_back(shared_ptr<Screenshot> scr) {
      set.push_back(scr);
    }
    shared_ptr<Screenshot> at(int n) {
      return set.at(n);
    }
    int size() {
      return set.size();
    }
  private:
    vector<shared_ptr<Screenshot>> set;
};

class ScreenshotsSession {
  public:
    ScreenshotsSession() {}
    ScreenshotsSession(shared_ptr<ScreenshotsSet> set) {
      session.push_back(set);
    }
    void push_back(shared_ptr<ScreenshotsSet> set) {
      session.push_back(set);
    }
    shared_ptr<ScreenshotsSet> at(int n) {
      return session.at(n);
    }
    int size() {
      return session.size();
    }
    // TODO:
    void save() {}
    void load() {}
  private:
    vector<shared_ptr<ScreenshotsSet>> session;
};

class ScreenshotManager {
  public:
    ScreenshotManager() {
      imProc = ImageProcessor();
      displayON = false;
      font.loadFromFile("../fonts/LiberationMono-Bold.ttf");

      currentSet = std::make_shared<ScreenshotsSet>();  // <--- Set
      currentSession = std::make_shared<ScreenshotsSession>(); // <--- Session
      currentSession->push_back(currentSet); // Assigning set to session
      sessions.push_back(currentSession); // Assigning session to collection of sessions
    }

    void Shot(); // Get screenshot using SreenshotProvider
    void Main(const int n); // Main loop of screenshot Manager

  private:
    int n;
    bool displayON;
    sf::Font font;

    shared_ptr<Screenshot> currentScr;
    shared_ptr<ScreenshotsSet> currentSet; // Collection of screenshots
    shared_ptr<ScreenshotsSession> currentSession; // Collection of sets
    vector<shared_ptr<ScreenshotsSession>> sessions; // Collection of sessions

    ImageProcessor imProc;

    shared_ptr<sf::Image> screenshotImage;
    sf::Texture screenshotTexture;
    sf::Sprite screenshotSprite;
    sf::Text timestampText;
};



#endif // SCREENSHOT_MANAGER_HPP
