#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void jump();
    void reset();
    sf::FloatRect getBounds() const;
    bool isDead() const;

private:
    sf::CircleShape shape;
    float velocity;
    float gravity;
    float jumpStrength;
    float startX, startY;
    bool dead;
};

#endif