#pragma once
#include <vector>

#include "picture.h"

class PictureNode {
    friend class Picture;
protected:
    virtual ~PictureNode()= default;

private:
    virtual std::size_t GetMaxWidth() const = 0;
    virtual std::size_t GetMaxHeight() const = 0;
    virtual void PrintLine(std::ostream &, std::size_t , std::size_t) const = 0;
    virtual bool HadFrame() {return false;};
};

class BasePictureNode : public PictureNode {
    friend class Picture;
private:
    BasePictureNode(const std::initializer_list<std::string> &list):
        words(list) {};
    std::size_t GetMaxWidth() const override;
    std::size_t GetMaxHeight() const override;
    void PrintLine(std::ostream &, std::size_t , std::size_t) const override;

private:
    std::vector<std::string> words;
};

class FramePictureNode : public PictureNode {
    friend class Picture;
private:
    explicit FramePictureNode(Picture target):
        picture(std::move(target)) {};
    std::size_t GetMaxWidth() const override;
    std::size_t GetMaxHeight() const override;
    void PrintLine(std::ostream &, std::size_t , std::size_t) const override;
    bool HadFrame() override {return true;};

private:
    Picture picture;
};

class VerticalPictureNode : public PictureNode {
    friend class Picture;
private:
    explicit VerticalPictureNode(Picture u, Picture d):
        up(std::move(u)), down(std::move(d)) {};
    std::size_t GetMaxWidth() const override;
    std::size_t GetMaxHeight() const override;
    void PrintLine(std::ostream &, std::size_t , std::size_t) const override;

private:
    Picture up;
    Picture down;
};

class HorizontalPictureNode : public PictureNode {
    friend class Picture;
private:
    HorizontalPictureNode(Picture l, Picture r):
            left(std::move(l)), right(std::move(r)) {};
    std::size_t GetMaxWidth() const override;
    std::size_t GetMaxHeight() const override;
    void PrintLine(std::ostream &, std::size_t , std::size_t) const override;

private:
    Picture left;
    Picture right;
};