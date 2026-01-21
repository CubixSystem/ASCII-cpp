#include "Config.hpp"
#include "json.h"
#include <fstream>
#include <stdexcept>

namespace plotter {

PlotterConfig Config::LoadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open config file: " + filename);
    }
    return LoadFromString(file);
}

PlotterConfig Config::LoadFromString(std::istream &json_str) {
    PlotterConfig config;

    Document doc = Load(json_str);

    const auto &root = doc.GetRoot().AsMap();

    auto width_it = root.find("width");
    if (width_it != root.end()) {
        config.width = width_it->second.AsInt();
    } else {
        throw std::runtime_error("Missing 'width' field");
    }

    auto height_it = root.find("height");
    if (height_it != root.end()) {
        config.height = height_it->second.AsInt();
    } else {
        throw std::runtime_error("Missing 'height' field");
    }

    auto bg_it = root.find("background_char");
    if (bg_it != root.end()) {
        std::string bg = bg_it->second.AsString();
        if (bg.empty()) {
            config.background_char = ' ';
        } else {
            config.background_char = bg[0];
        }
    } else {
        throw std::runtime_error("Missing 'background_char' field");
    }

    auto palette_it = root.find("palette");
    if (palette_it != root.end()) {
        std::string palette_str = palette_it->second.AsString();
        config.palette = ParsePalette(palette_str);
    }

    auto type_it = root.find("plotter_type");
    if (type_it != root.end()) {
        config.plotter_type = type_it->second.AsString();
    } else {
        config.plotter_type = "basic";
    }

    if (!ValidateConfig(config)) {
        throw std::runtime_error("Config validation failed");
    }

    return config;
}

std::vector<char> Config::ParsePalette(const std::string &palette_str) {
    std::vector<char> palette;
    for (char c : palette_str) {
        palette.push_back(c);
    }
    return palette;
}

bool Config::ValidateConfig(const PlotterConfig &config) {
    if (config.width <= 0 || config.height <= 0) {
        return false;
    }

    if (config.plotter_type != "basic" && config.plotter_type != "grayscale") {
        return false;
    }

    if (!config.palette.empty() && config.palette.size() < 2) {
        return false;
    }

    return true;
}

PlotterConfig Config::DefaultConfig() {
    PlotterConfig config;
    config.width = 80;
    config.height = 40;
    config.background_char = ' ';
    config.palette = {};
    config.plotter_type = "basic";
    return config;
}

} // namespace plotter
