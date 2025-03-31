#include <SFML/Graphics.hpp>
#include "tools.h"

void drawScanline(
    int row, int col,
    int line, sf::Color color,
    std::vector<std::uint8_t>& pixels
){
    int linewidth = SCREEN_WIDTH / COLUMNS;
    int lineheight = linewidth / 3;

    int y = (linewidth * row) + (lineheight * line);
    int x = linewidth * col;
    
    for (int b = y; b < y + lineheight; b++)
    {
        for (int a = x; a < x + linewidth; a++)
        {
	    int index = (SCREEN_WIDTH*b+a) * 4; // RGBA
	    if ( index + 3 < pixels.size() )
	    {
	        pixels[index + 0] = color.r;
	        pixels[index + 1] = color.g;
                pixels[index + 2] = color.b;
                pixels[index + 3] = color.a;
            }
        }
    }
}

void drawCell(
    int row, int col, ColorID color,
    std::vector<std::uint8_t>& pixels
){
    drawScanline(row, col, 0, sf::Color::Black, pixels);
    drawScanline(row, col, 1, sf::Color::Black, pixels);
    drawScanline(row, col, 2, sf::Color::Black, pixels);
    
    switch (color)
    {
    case White:
    case Red:
    case Yellow:
    case Magenta:
        drawScanline(row, col, 0, sf::Color::Red, pixels);
	break;
    }

    switch (color)
    {
    case White:
    case Green:
    case Yellow:
    case Cyan:
        drawScanline(row, col, 1, sf::Color::Green, pixels);
    }

    switch (color)
    {
    case White:
    case Blue:
    case Magenta:
    case Cyan:
        drawScanline(row, col, 2, sf::Color::Blue, pixels);
	break;
    }
}

void drawRect(
    int row, int col, int w, int h, ColorID color,
    std::vector<std::uint8_t>& pixels
){
    for (int r = row; r < row + h; r++)
    {
        for (int c = col; c < col + w; c++)
        {
            drawCell(r, c, color, pixels);
        }
    }
}

void drawGrid(
    int row, int col, int h, int w,
    char grid[], std::vector<std::uint8_t>& pixels
){
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            ColorID id = static_cast<ColorID>( grid[w*i+j] );
            drawCell(row + i, col + j, id, pixels);
        }
    }
}

sf::Color getColor(ColorID color)
{
  sf::Color colors[] = {
      sf::Color::Black, sf::Color::White,
      sf::Color::Red, sf::Color::Green, sf::Color::Blue,
      sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan
  };
  
  int c = static_cast<int>(color);
  if (c >= 0 && c < 8) return colors[c];
  else return sf::Color::Black;
}

ColorID getColorID(sf::Color color)
{
    sf::Color colors[] = {
      sf::Color::Black, sf::Color::White,
      sf::Color::Red, sf::Color::Green, sf::Color::Blue,
      sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan
  };
  
  for (int i = 0; i < 8; i++)
      if (color == colors[i])
          return static_cast<ColorID>(i);

  return ColorID::Black;
}

void drawImage(
    int row, int col,
    sf::Image& img, std::vector<std::uint8_t>& pixels
){
    auto [cols, rows] = img.getSize();
    
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            auto x = static_cast<unsigned int>(c);
            auto y = static_cast<unsigned int>(r);
            ColorID color = getColorID( img.getPixel({x, y}) );
            drawCell(row + r, col + c, color, pixels);
        }
    }
}

bool saveGrid(
    int rows, int cols,
    char grid[], std::string file
){
    auto ur = static_cast<unsigned int>(rows);
    auto uc = static_cast<unsigned int>(cols);
    auto path = static_cast<std::filesystem::path>(file);
    
    sf::Image img({ur, uc});
    for (unsigned int r = 0; r < rows; r++)
    {
        for (unsigned int c = 0; c < cols; c++)
        {
            ColorID color = static_cast<ColorID>( grid[uc*r+c] );
            img.setPixel({c, r}, getColor(color));
        }
    }
    
    return img.saveToFile(path);
}

