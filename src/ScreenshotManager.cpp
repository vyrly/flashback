#include <ScreenshotManager.hpp>

void ScreenshotManager::Shot() {
  shared_ptr<Screenshot> scr = std::make_shared<Screenshot>(); // <--- Screenshot
  currentSet->push_back(scr);
  cout << "Number of screenshots in current set: " << currentSet->size() << endl;
  cout << "Number of sets in current session: " << currentSession->size() << endl;
  cout << "Number of sessions: " << sessions.size() << endl;
}

void ScreenshotManager::Main(const int n) {

  // Prepare screenshot to be drawn
  currentScr = currentSet->at(n);
  screenshotImage = currentScr->ImageGet(); // Get Image pointer
  screenshotTexture.loadFromImage(*screenshotImage); // Load a texture from Image
  screenshotSprite.setTexture(screenshotTexture); // Assign it to a sprite

  // Prepare timestamp to be drawn
  time_point<system_clock> timestamp = currentScr->TimestampGet();
  // Convert timestamp to string
  auto in_time_t = std::chrono::system_clock::to_time_t(timestamp);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  timestampText.setFont(font); // select the font
  timestampText.setString(ss.str()); // set the string to display
  timestampText.setCharacterSize(22); // // set the character size in pixels
  timestampText.setColor(sf::Color::Red); // set the color
  timestampText.setStyle(sf::Text::Bold); // set the text style

  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Flashback", sf::Style::Fullscreen);

  // the event/logic/whatever loop
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // check the type of the event...
      switch (event.type) {
        // "close requested" event: close the window
        case sf::Event::Closed:
          window.close();
          cout << "Close screenshot manager" << endl;
          break;
        // key pressed
        case sf::Event::KeyPressed:
          // "ESC": close the window
          if (event.key.code == sf::Keyboard::Escape) {
            window.close();
            cout << "Close screenshot manager" << endl;
          }
          // "Down": change displayed screenshot
          if (event.key.code == sf::Keyboard::Down) {
            cout << "Key: Down" << endl;
          }
          // "Up": change displayed screenshot
          if (event.key.code == sf::Keyboard::Up) {
            cout << "Key: Up" << endl;
          }
          // "Right": next set
          if (event.key.code == sf::Keyboard::Up) {
            cout << "Key: Up" << endl;
          }
          // "Left": previous set
          if (event.key.code == sf::Keyboard::Up) {
            cout << "Key: Up" << endl;
          }
          break;
        // don't process other types of events
        default:
            break;
      }
    }
    // clear the window with black color
    window.clear(sf::Color::Black);

    // Draw everything here...
    window.draw(screenshotSprite); // Textured sprite
    window.draw(timestampText); // Timestamp string
    // TODO: Draw UI

    // end the current frame
    window.display();
    displayON = true;
  }
}
