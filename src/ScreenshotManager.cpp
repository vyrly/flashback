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
  // create the window
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Flashback");

  displayON = true;

  shared_ptr<sf::Image> ImageToDisplay = this->screenshots[n]->ImageGet();

  // Load a texture from a file
  sf::Texture texture;
  texture.loadFromImage(*ImageToDisplay);

  // Assign it to a sprite
  sf::Sprite sprite;
  sprite.setTexture(texture);

  // run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed)
              window.close();
      }

      // clear the window with black color
      window.clear(sf::Color::Black);

      // Draw everything here...
      // Draw the textured sprite
      window.draw(sprite);

      // end the current frame
      window.display();
  }


/*  // cvStartWindowThread();
  imshow("Display", *ImageToDisplay);
  cout << "Display ON" << endl;

  int key = -1;
  int shotNumber = 0;
  while (displayON) {
    key = waitKey(0);
    cout << key << endl; // DBG
    if ( key == 1048603 ) { // Esc: comparing to 27 don't work for all platforms: https://stackoverflow.com/questions/14494101/using-other-keys-for-the-waitkey-function-of-opencv
      cout << "Closing display" << endl;
      displayON = false;
    }
    if ( key >= 1048625 && key <= 1048633 ) { // Display n screenshot
      shotNumber = key - 1048625;
      if (this->screenshots.size() < shotNumber)
        shotNumber = this->screenshots.size() - 1;
      cout << shotNumber << endl; // DBG
      ImageToDisplay = this->screenshots[shotNumber]->ImageGet(); // Segfault when displaying last screenshot
      imshow("Display", *ImageToDisplay);
    }
  }
  cv::destroyAllWindows();
  waitKey(1);
  waitKey(1);
  waitKey(1);
  waitKey(1); // To close window? - https://stackoverflow.com/questions/6116564/destroywindow-does-not-close-window-on-mac-using-python-and-opencv
*/
  cout << "Display OFF" << endl;
}
