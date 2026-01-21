#pragma once
#include <string>
#include <vector>

namespace plotter {

struct PlotterConfig {
    int width;
    int height;
    char background_char;
    std::vector<char> palette;
    std::string plotter_type;
};

class Config {
  public:
    static PlotterConfig LoadFromFile(const std::string &filename);
    static PlotterConfig LoadFromString(std::istream &json_str);
    static bool ValidateConfig(const PlotterConfig &config);
    static PlotterConfig DefaultConfig();

  private:
    static std::vector<char> ParsePalette(const std::string &palette_str);
};

} // namespace plotter
