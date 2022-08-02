#pragma once
#include <string>
#include <iostream>
#include <memory>

class PictureNode;
class Picture {
public:
    Picture(const std::initializer_list<std::string> &list);
    void Print(std::ostream &out = std::cout) const;
    void PrintLine(std::ostream &, std::size_t, std::size_t) const;
    Picture &FrameSplicing();
    Picture &RemoveFrame();
    Picture &VerticalSplicing(Picture);
    Picture &HorizontalSplicing(Picture);
    std::size_t GetMaxWidth() const;
    std::size_t GetMaxHeight() const;

private:
    std::shared_ptr<PictureNode> p{nullptr};
};

