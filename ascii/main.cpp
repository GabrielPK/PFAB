#include <Magick++.h> 
#include <iostream> 

using namespace std; 
using namespace Magick; 

const string ASCII_MATRIX = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const unsigned ASCII_MATRIX_LEN = ASCII_MATRIX.length();
unsigned rgb_to_brightness(const unsigned& red, const unsigned& green, const unsigned& blue, const string& how="average", const bool& invert=false);
char brightness_to_char(const unsigned& brightness);
void print_image(char **&img_ascii, const unsigned& rows, const unsigned& cols);

// argv[1] : path to file
// argv[2] : how to compute brightness, one of ["average", "lightness", "luminosity"]
// argv[3] : whether to invert the brightness
int main(int argc, char **argv) 
{ 
  string brightness_how = "average";
  bool invert = false;
  if (argc < 2) {
    cout << "Filename required" << endl;
    return -1;
  } 
  else if (argc == 3)
  {
    string brightness_how = argv[2];
    bool invert = false;
  }
  else if (argc == 4)
  {
    string brightness_how = argv[2];
    invert = string("true").compare(string(argv[3])) == 0;
  }

  Image image;
  try { 
    // Read a file into image object 
    image.read(argv[1]);
    cout << "Loaded image" << endl;

    const unsigned max_height = 76;
    const unsigned max_width = -1;

    image.scale(Magick::Geometry(max_width, max_height));
    cout << "Resized image" << endl;

    const unsigned w = image.columns();
    const unsigned h = image.rows();
    cout << "Image size: " << w << " x " << h << endl;

    char ** img_ascii = new char *[h];
    
    for (unsigned row = 0; row < h; row++)
    {
      img_ascii[row] = new char [w];
      for (unsigned col = 0; col < w; col++)
      {
        ColorRGB px = image.pixelColor(col, row);
        unsigned red = px.red() * 255;
        unsigned green = px.green() * 255;
        unsigned blue = px.blue() * 255;
        unsigned bright_val = rgb_to_brightness(red, green, blue, brightness_how, invert);
        char bright_char = brightness_to_char(bright_val);
        img_ascii[row][col] = bright_char;
      }
    }
    cout << "Printing Image..." << endl;
    print_image(img_ascii, h, w);

  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    } 
  return 0; 
}

// helper to configure how to calculate brightness of a pixel given RGB values
// returns unsigned in range [0,255] 
unsigned rgb_to_brightness(const unsigned& red, const unsigned& green, const unsigned& blue, 
                           const string& how, const bool& invert)
{
  unsigned bright_out = 0;
  if (how.compare("average") == 0) 
  {
    bright_out = invert ? 255 - unsigned((red + green + blue) / 3) : unsigned((red + green + blue) / 3);
  } 
  else if (how.compare("lightness") == 0) 
  {
    bright_out = invert ? 255 - unsigned((max({red, green, blue}) + min({red, green, blue})) / 2) : unsigned((max({red, green, blue}) + min({red, green, blue})) / 2);
  }
  else if (how.compare("luminosity") == 0)
  {
    bright_out =  invert ? 255 - unsigned(0.21 * red + 0.72 * green + 0.07 * blue) : unsigned(0.21 * red + 0.72 * green + 0.07 * blue);
  }

  return bright_out;
}

// helper to convert a brightness value in range [0,255] to an ASCII character
// returns char from ASCII_MATRIX
char brightness_to_char(const unsigned& brightness)
{
  return ASCII_MATRIX[unsigned((double(brightness) / 255) * (ASCII_MATRIX_LEN-1))];
}

// prints image to stdout given a 2d array of chars and dimensions
void print_image(char **&img_ascii, const unsigned& rows, const unsigned& cols) 
{
  for (unsigned row = 0; row < rows; row++)
  {
    for (unsigned col = 0; col < cols; col++)
    {
      cout << img_ascii[row][col] << img_ascii[row][col] << img_ascii[row][col];
    }
    cout << endl;
  }
}
