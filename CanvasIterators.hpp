#pragma once
#include "Canvas.hpp"
#include <iterator>

namespace plotter {

class Canvas::RowIterator {
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = std::ptrdiff_t;
    using pointer = char *;
    using reference = char &;

    RowIterator(Canvas *canvas, int row, int col)
        : canvas_(canvas), row_(row), col_(col) {}

    reference operator*() {
        return canvas_->at(col_, row_);
    }

    pointer operator->() {
        return &canvas_->at(col_, row_);
    }

    reference operator[](difference_type n) {
        return canvas_->at(col_ + n, row_);
    }

    RowIterator &operator++() {
        ++col_;
        return *this;
    }

    RowIterator operator++(int) {
        RowIterator tmp = *this;
        ++col_;
        return tmp;
    }

    RowIterator &operator--() {
        --col_;
        return *this;
    }

    RowIterator operator--(int) {
        RowIterator tmp = *this;
        --col_;
        return tmp;
    }

    RowIterator &operator+=(difference_type n) {
        col_ += n;
        return *this;
    }

    RowIterator &operator-=(difference_type n) {
        col_ -= n;
        return *this;
    }

    RowIterator operator+(difference_type n) const {
        return RowIterator(canvas_, row_, col_ + n);
    }

    RowIterator operator-(difference_type n) const {
        return RowIterator(canvas_, row_, col_ - n);
    }

    difference_type operator-(const RowIterator &other) const {
        return col_ - other.col_;
    }

    bool operator==(const RowIterator &other) const {
        return canvas_ == other.canvas_ && row_ == other.row_ &&
               col_ == other.col_;
    }

    bool operator!=(const RowIterator &other) const {
        return !(*this == other);
    }

    bool operator<(const RowIterator &other) const {
        return col_ < other.col_;
    }

    bool operator>(const RowIterator &other) const {
        return col_ > other.col_;
    }

    bool operator<=(const RowIterator &other) const {
        return col_ <= other.col_;
    }

    bool operator>=(const RowIterator &other) const {
        return col_ >= other.col_;
    }

  private:
    Canvas *canvas_;
    int row_;
    int col_;
};

class Canvas::ColumnIterator {
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = std::ptrdiff_t;
    using pointer = char *;
    using reference = char &;

    ColumnIterator(Canvas *canvas, int col, int row)
        : canvas_(canvas), col_(col), row_(row) {}

    reference operator*() {
        return canvas_->at(col_, row_);
    }

    pointer operator->() {
        return &canvas_->at(col_, row_);
    }

    reference operator[](difference_type n) {
        return canvas_->at(col_, row_ + n);
    }

    ColumnIterator &operator++() {
        ++row_;
        return *this;
    }

    ColumnIterator operator++(int) {
        ColumnIterator tmp = *this;
        ++row_;
        return tmp;
    }

    ColumnIterator &operator--() {
        --row_;
        return *this;
    }

    ColumnIterator operator--(int) {
        ColumnIterator tmp = *this;
        --row_;
        return tmp;
    }

    ColumnIterator &operator+=(difference_type n) {
        row_ += n;
        return *this;
    }

    ColumnIterator &operator-=(difference_type n) {
        row_ -= n;
        return *this;
    }

    ColumnIterator operator+(difference_type n) const {
        return ColumnIterator(canvas_, col_, row_ + n);
    }

    ColumnIterator operator-(difference_type n) const {
        return ColumnIterator(canvas_, col_, row_ - n);
    }

    difference_type operator-(const ColumnIterator &other) const {
        return row_ - other.row_;
    }

    bool operator==(const ColumnIterator &other) const {
        return canvas_ == other.canvas_ && col_ == other.col_ &&
               row_ == other.row_;
    }

    bool operator!=(const ColumnIterator &other) const {
        return !(*this == other);
    }

    bool operator<(const ColumnIterator &other) const {
        return row_ < other.row_;
    }

    bool operator>(const ColumnIterator &other) const {
        return row_ > other.row_;
    }

    bool operator<=(const ColumnIterator &other) const {
        return row_ <= other.row_;
    }

    bool operator>=(const ColumnIterator &other) const {
        return row_ >= other.row_;
    }

  private:
    Canvas *canvas_;
    int col_;
    int row_;
};

class Canvas::PixelIterator {
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = std::ptrdiff_t;
    using pointer = char *;
    using reference = char &;

    PixelIterator(Canvas *canvas, size_t pos) : canvas_(canvas), pos_(pos) {}

    reference operator*() {
        int x = pos_ % canvas_->Width();
        int y = pos_ / canvas_->Width();
        return canvas_->at(x, y);
    }

    pointer operator->() {
        int x = pos_ % canvas_->Width();
        int y = pos_ / canvas_->Width();
        return &canvas_->at(x, y);
    }

    reference operator[](difference_type n) {
        size_t new_pos = pos_ + n;
        int x = new_pos % canvas_->Width();
        int y = new_pos / canvas_->Width();
        return canvas_->at(x, y);
    }

    PixelIterator &operator++() {
        ++pos_;
        return *this;
    }

    PixelIterator operator++(int) {
        PixelIterator tmp = *this;
        ++pos_;
        return tmp;
    }

    PixelIterator &operator--() {
        --pos_;
        return *this;
    }

    PixelIterator operator--(int) {
        PixelIterator tmp = *this;
        --pos_;
        return tmp;
    }

    PixelIterator &operator+=(difference_type n) {
        pos_ += n;
        return *this;
    }

    PixelIterator &operator-=(difference_type n) {
        pos_ -= n;
        return *this;
    }

    PixelIterator operator+(difference_type n) const {
        return PixelIterator(canvas_, pos_ + n);
    }

    PixelIterator operator-(difference_type n) const {
        return PixelIterator(canvas_, pos_ - n);
    }

    difference_type operator-(const PixelIterator &other) const {
        return pos_ - other.pos_;
    }

    bool operator==(const PixelIterator &other) const {
        return canvas_ == other.canvas_ && pos_ == other.pos_;
    }

    bool operator!=(const PixelIterator &other) const {
        return !(*this == other);
    }

    bool operator<(const PixelIterator &other) const {
        return pos_ < other.pos_;
    }

    bool operator>(const PixelIterator &other) const {
        return pos_ > other.pos_;
    }

    bool operator<=(const PixelIterator &other) const {
        return pos_ <= other.pos_;
    }

    bool operator>=(const PixelIterator &other) const {
        return pos_ >= other.pos_;
    }

  private:
    Canvas *canvas_;
    size_t pos_;
};

} // namespace plotter
