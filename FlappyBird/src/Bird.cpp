#include "Bird.h"

Bird::Bird() : velocity(0), gravity(400), jumpStrength(-200), dead(false), startX(100), startY(300) {
    shape.setRadius(15);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition({startX, startY});
}

void Bird::update(float dt) {
    if (!dead) {
        velocity += gravity * dt;
        shape.move({0, velocity * dt});
        if (shape.getPosition().y < 0) { 
            shape.setPosition({shape.getPosition().x, 0}); 
            velocity = 0; 
        }
        if (shape.getPosition().y + 30 > 600) { 
            shape.setPosition({shape.getPosition().x, 570}); 
            dead = true; 
        }
    }
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Bird::jump() {
    if (!dead) velocity = jumpStrength;
}

void Bird::reset() {
    shape.setPosition({startX, startY});
    velocity = 0;
    dead = false;
}

sf::FloatRect Bird::getBounds() const { return shape.getGlobalBounds(); }
bool Bird::isDead() const { return dead; }