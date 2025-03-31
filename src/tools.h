#define ROWS      60
#define COLUMNS   80

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 720

// Note: This enum is different from the sf::Color class
// and does not contain any color information
enum ColorID { Black = 0, White, Red, Green, Blue, Yellow, Magenta, Cyan };
sf::Color getColor(ColorID color);
ColorID getColorID(sf::Color color);

void drawScanline(int, int, int, sf::Color, std::vector<std::uint8_t>&);
void drawCell(int, int, ColorID, std::vector<std::uint8_t>&);
void drawRect(int, int, int, int, ColorID, std::vector<std::uint8_t>& pixels);
void drawGrid(int, int, int, int, char[], std::vector<std::uint8_t>& pixels);

void drawImage(int, int, sf::Image&, std::vector<std::uint8_t>&);
bool saveGrid(int, int, char[], std::string);

