


// Settings singleton
// Based on:
// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// This is thread safe in C++11
// https://stackoverflow.com/questions/1661529/is-meyers-implementation-of-singleton-pattern-thread-safe
class Settings {
  public:
    // TMP

  private:

    void loadSettings();

  public:
    static Settings& getInstance() {
      static Settings instance; // Guaranteed to be destroyed.
      return instance; // Instantiated on first use.
    }

  private:
    Settings() {}; // Constructor? (the {} brackets) are needed here.

  public:
    // C++ 11 - Deleting the methods we don't want.
    Settings(Settings const&)        = delete;
    void operator=(Settings const&)  = delete;
    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
};
