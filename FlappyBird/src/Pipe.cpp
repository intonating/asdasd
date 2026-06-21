#include "Pipe.h"
#include <random>

Pipe::Pipe(float x) : speed(200), gap(150) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(50, 400);
    float height = dist(gen);
    
    top.setSize({80, height});
    top.setFillColor(sf::Color::Green);
    top.setPosition({x, 0});
    
    bottom.setSize({80, 600 - height - gap});
    bottom.setFillColor(sf::Color::Green);
    bottom.setPosition({x, height + gap});
}

void Pipe::update(float dt) {
    top.move({-speed * dt, 0});
    bottom.move({-speed * dt, 0});
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(top);
    window.draw(bottom);
}

sf::FloatRect Pipe::getTopBounds() const { return top.getGlobalBounds(); }
sf::FloatRect Pipe::getBottomBounds() const { return bottom.getGlobalBounds(); }
float Pipe::getX() const { return top.getPosition().x; }

void Pipe::reset(float x) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(50, 400);
    float height = dist(gen);
    top.setPosition({x, 0});
    bottom.setPosition({x, height + gap});
    top.setSize({80, height});
    bottom.setSize({80, 600 - height - gap});
}