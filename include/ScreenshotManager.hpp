#ifndef SCREENSHOT_MANAGER_HPP
#define SCREENSHOT_MANAGER_HPP

#include <ImageProcessor.hpp>
#include <Screenshot.hpp>

//------------------------------------------------------------------------------

class ScreenshotsSet {
  public:

    typedef list<shared_ptr<Screenshot>> ScrSet;

    typedef ScrSet::iterator iterator;
    typedef ScrSet::const_iterator const_iterator ;

    iterator begin() { return set.begin(); }
    iterator end() { return set.end(); }

    const_iterator cbegin() const { return set.begin(); }
    const_iterator cend() const { return set.end(); }

    size_t size() const { return set.size(); }

    ScreenshotsSet() {}
    ScreenshotsSet(shared_ptr<Screenshot> scr) {
      set.push_back(scr);
    }
    void push_front(shared_ptr<Screenshot> scr) {
      set.push_front(scr);
    }
  private:
    ScrSet set;
};

class ScreenshotsSession {
  public:

    typedef list<shared_ptr<ScreenshotsSet>> ScrSession;

    typedef ScrSession::iterator iterator;
    typedef ScrSession::const_iterator const_iterator ;

    iterator begin() { return session.begin(); }
    iterator end() { return session.end(); }

    const_iterator cbegin() const { return session.begin(); }
    const_iterator cend() const { return session.end(); }

    size_t size() const { return session.size(); }

    ScreenshotsSession() {}
    ScreenshotsSession(shared_ptr<ScreenshotsSet> set) {
      session.push_back(set);
    }
    void push_front(shared_ptr<ScreenshotsSet> set) {
      session.push_front(set);
    }
    // TODO:
    void save() {}
    void load() {}
  private:
    ScrSession session;
};

class ScreenshotManager {
  public:
    ScreenshotManager() {
      imProc = ImageProcessor();
      displayON = false;
      font.loadFromFile("../fonts/LiberationMono-Bold.ttf");

      // Initialize session structure
      cout << "Initialize session structure" << endl;
      currentSession = ScreenshotsSession(); // <--- New session
      currentSession.push_front(std::make_shared<ScreenshotsSet>()); // Assigning set to session
      itCurrentSet = currentSession.begin();
    }

    void Shot(); // Get screenshot using SreenshotProvider
    void Main(); // Main loop of screenshot Manager

    void RedrawScr();

  private:
    ScreenshotsSet::iterator itCurrentScr;
    ScreenshotsSession::iterator itCurrentSet;
    ScreenshotsSession currentSession; // Collection of sets

    int n;
    bool displayON;
    sf::Font font;

    ImageProcessor imProc;

    shared_ptr<sf::Image> screenshotImage;
    sf::Texture screenshotTexture;
    sf::Sprite screenshotSprite;
    sf::Text timestampText;
};



#endif // SCREENSHOT_MANAGER_HPP
