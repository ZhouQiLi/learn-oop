#include "picture_node.h"

namespace {
    void PrintSpaces(std::ostream &out, std::size_t count) {
        if (count <= 0) {
            return;
        }
        while (count--) {
            out << ' ';
        }
        out << std::flush;
    }
}

std::size_t BasePictureNode::GetMaxWidth() const {
    std::size_t width = 0;
    for (const auto &word : words) {
        width = std::max(width, word.size());
    }
    return width;
}

std::size_t BasePictureNode::GetMaxHeight() const {
    return words.size();
}

void BasePictureNode::PrintLine(std::ostream &out, std::size_t line, std::size_t maxWidth) const {
    std::size_t spaceCount = maxWidth;
    if (line <= words.size()) {
        auto world = words[line-1];
        out << world;
        spaceCount = std::max(std::size_t(0), maxWidth - world.size());
    }
    PrintSpaces(out, spaceCount);
}

std::size_t FramePictureNode::GetMaxWidth() const {
    return picture.GetMaxWidth() + 2;
}

std::size_t FramePictureNode::GetMaxHeight() const {
    return picture.GetMaxHeight() + 2;
}

void FramePictureNode::PrintLine(std::ostream &out, std::size_t line, std::size_t maxWidth) const {
    auto pictureWidth = picture.GetMaxWidth();
    auto pictureHeight = picture.GetMaxHeight();
    std::size_t spaceCount = std::max(std::size_t(0), maxWidth - pictureWidth - 2);
    if (line > pictureHeight + 2) {
        spaceCount = maxWidth;
    } else if (line == 1 || line == pictureHeight + 2) {
        out << "+" << std::string(pictureWidth, '-') << "+";
    } else {
        out << "|";
        picture.PrintLine(out, line-1, pictureWidth);
        out << "|";
    }
    PrintSpaces(out,  spaceCount);
}

std::size_t VerticalPictureNode::GetMaxWidth() const {
    return std::max(up.GetMaxWidth(), down.GetMaxWidth());
}

std::size_t VerticalPictureNode::GetMaxHeight() const {
    return up.GetMaxHeight() + down.GetMaxHeight();
}

void VerticalPictureNode::PrintLine(std::ostream &out, std::size_t line, std::size_t maxWidth) const {
    std::size_t spaceCount = maxWidth;
    if (line <= GetMaxHeight()) {
        Picture realPicture = up;
        std::size_t realLine = line;
        if (line > up.GetMaxHeight()) {
            realPicture = down;
            realLine = line - up.GetMaxHeight();
        }
        realPicture.PrintLine(out, realLine, maxWidth);
        spaceCount = 0;
    }
    PrintSpaces(out, spaceCount);
}

std::size_t HorizontalPictureNode::GetMaxWidth() const {
    return left.GetMaxWidth() + right.GetMaxWidth();
}

std::size_t HorizontalPictureNode::GetMaxHeight() const {
    return std::max(left.GetMaxHeight(), right.GetMaxHeight());
}

void HorizontalPictureNode::PrintLine(std::ostream &out, std::size_t line, std::size_t maxWidth) const {
    std::size_t spaceCount = maxWidth;
    if (line <= GetMaxHeight()) {
        auto leftWidth = left.GetMaxWidth();
        auto rightWidth = right.GetMaxWidth();
        left.PrintLine(out, line, leftWidth);
        right.PrintLine(out, line, rightWidth);
        spaceCount = std::max(std::size_t(0), maxWidth - leftWidth - rightWidth);
    }
    PrintSpaces(out, spaceCount);
}