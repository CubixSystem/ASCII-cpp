#include "Canvas.hpp"
#include "CanvasIterators.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>

namespace plotter {

Canvas::Canvas(int width, int height, char background_char)
    : width_(width), height_(height), background_(background_char),
      data_(width * height, background_char) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
}

Canvas::Canvas(Canvas &&other) noexcept
    : width_(other.width_), height_(other.height_),
      background_(other.background_), data_(std::move(other.data_)) {
    other.width_ = 0;
    other.height_ = 0;
}

Canvas &Canvas::operator=(const Canvas &other) {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        background_ = other.background_;
        data_ = other.data_;
    }
    return *this;
}

Canvas &Canvas::operator=(Canvas &&other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        background_ = other.background_;
        data_ = std::move(other.data_);
        other.width_ = 0;
        other.height_ = 0;
    }
    return *this;
}

int Canvas::Width() const noexcept {
    return width_;
}

int Canvas::Height() const noexcept {
    return height_;
}

int Canvas::Size() const noexcept {
    return width_ * height_;
}

char &Canvas::at(int x, int y) {
    if (!InBounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data_[y * width_ + x];
}

const char &Canvas::at(int x, int y) const {
    if (!InBounds(x, y)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data_[y * width_ + x];
}

char &Canvas::operator()(int x, int y) noexcept {
    return data_[y * width_ + x];
}

const char &Canvas::operator()(int x, int y) const noexcept {
    return data_[y * width_ + x];
}

bool Canvas::InBounds(int x, int y) const noexcept {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

void Canvas::Clear(char fill_char) {
    std::fill(data_.begin(), data_.end(), fill_char);
    background_ = fill_char;
}

void Canvas::FillRegion(int x1, int y1, int x2, int y2, char fill_char) {
    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);

    x1 = std::max(0, x1);
    y1 = std::max(0, y1);
    x2 = std::min(width_ - 1, x2);
    y2 = std::min(height_ - 1, y2);

    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            data_[y * width_ + x] = fill_char;
        }
    }
}

void Canvas::Render(std::ostream &os) const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            os << data_[y * width_ + x];
        }
        os << '\n';
    }
    os.flush();
}

void Canvas::SaveToFile(const std::filesystem::path &filepath) const {
    auto parent_path = filepath.parent_path();
    if (!parent_path.empty() && !std::filesystem::exists(parent_path)) {
        std::filesystem::create_directories(parent_path);
    }

    std::ofstream file(filepath);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing: " +
                                 filepath.string());
    }

    file << "Canvas " << width_ << "x" << height_ << '\n';
    file << "Background: " << "'" << background_ << "'" << '\n';
    file << "Content:" << '\n';

    Render(file);
}

void Canvas::SaveToFile(const std::string &filename) const {
    SaveToFile(std::filesystem::path(filename));
}

Canvas::RowIterator Canvas::RowBegin(int row) {
    return RowIterator(this, row, 0);
}

Canvas::RowIterator Canvas::RowEnd(int row) {
    return RowIterator(this, row, width_);
}

Canvas::ColumnIterator Canvas::ColBegin(int col) {
    return ColumnIterator(this, col, 0);
}

Canvas::ColumnIterator Canvas::ColEnd(int col) {
    return ColumnIterator(this, col, height_);
}

Canvas::PixelIterator Canvas::begin() {
    return PixelIterator(this, 0);
}

Canvas::PixelIterator Canvas::end() {
    return PixelIterator(this, Size());
}

} // namespace plotter
