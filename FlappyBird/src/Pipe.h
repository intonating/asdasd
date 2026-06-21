#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float x);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;
    float getX() const;
    void reset(float x);

private:
    sf::RectangleShape top, bottom;
    float speed;
    float gap;
};

#endif