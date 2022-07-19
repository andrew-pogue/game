#pragma once

class Graphic {
public:

    virtual ~Graphic() {}
    virtual void draw(float x, float y) const = 0;

private:

};