#include <iostream>
#include <iomanip>
#include <utility>

#include "picture_node.h"
#include "picture.h"

Picture::Picture(const std::initializer_list<std::string> &list) {
    p = std::shared_ptr<BasePictureNode>(new BasePictureNode(list));
}

void Picture::Print(std::ostream &out) const {
    auto maxWidth = GetMaxWidth();
    auto maxHeight = GetMaxHeight();
    out << std::setiosflags(std::ios::left);
    out << "\n--- start print ---" << std::endl;
    for (int i = 1; i <= maxHeight; ++i) {
        p->PrintLine(out, i, maxWidth);
        out << std::endl;
    }
    out << "--- stop  print ---\n" << std::endl;
}

void Picture::PrintLine(std::ostream &out, std::size_t line, std::size_t maxWidth) const {
    p->PrintLine(out, line, maxWidth);
}

Picture &Picture::FrameSplicing() {
    p = std::shared_ptr<FramePictureNode>(new FramePictureNode(*this));
    return *this;
}

Picture &Picture::RemoveFrame() {
    if (p->HadFrame()) {
        p = std::dynamic_pointer_cast<FramePictureNode>(p)->picture.p;
    }
    return *this;
}

Picture &Picture::VerticalSplicing(Picture target) {
    p = std::shared_ptr<VerticalPictureNode>(new VerticalPictureNode(*this, std::move(target)));
    return *this;
}

Picture &Picture::HorizontalSplicing(Picture target) {
    p = std::shared_ptr<HorizontalPictureNode>(new HorizontalPictureNode(*this, std::move(target)));
    return *this;
}

std::size_t Picture::GetMaxWidth() const {
    return p->GetMaxWidth();
}
std::size_t Picture::GetMaxHeight() const {
    return p->GetMaxHeight();
}
