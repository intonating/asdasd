#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipe.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode({400, 600}), "Flappy Bird");
    window.setFramerateLimit(60);
    
    Bird bird;
    std::vector<Pipe> pipes;
    sf::Clock clock, pipeTimer;
    float pipeInterval = 2.0f;
    int score = 0;
    bool gameOver = false;
    
    sf::Font font;
    font.openFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
    sf::Text scoreText(font), gameOverText(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({180, 30});
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R");
    gameOverText.setPosition({100, 200});
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Space && !gameOver) bird.jump();
                if (key->code == sf::Keyboard::Key::R && gameOver) {
                    bird.reset();
                    pipes.clear();
                    score = 0;
                    gameOver = false;
                    pipeTimer.restart();
                }
                if (key->code == sf::Keyboard::Key::Escape) window.close();
            }
        }
        
        float dt = clock.restart().asSeconds();
        
        if (!gameOver) {
            bird.update(dt);
            if (pipeTimer.getElapsedTime().asSeconds() >= pipeInterval) {
                pipes.emplace_back(400);
                pipeTimer.restart();
            }
            for (auto& pipe : pipes) pipe.update(dt);
            
            for (auto& pipe : pipes) {
                auto intersectTop = bird.getBounds().findIntersection(pipe.getTopBounds());
                auto intersectBottom = bird.getBounds().findIntersection(pipe.getBottomBounds());
                if (intersectTop.has_value() || intersectBottom.has_value()) {
                    gameOver = true;
                }
            }
            if (bird.isDead()) gameOver = true;
            
            for (auto& pipe : pipes) {
                // Проверяем, что труба прошла мимо птицы и её ещё не засчитали
                if (pipe.getX() + 80 < bird.getBounds().position.x && pipe.getX() > 0) {
                    score++;
                    pipe.reset(-100);
                }
            }
        }
        
        scoreText.setString(std::to_string(score));
        
        window.clear(sf::Color::Cyan);
        bird.draw(window);
        for (auto& pipe : pipes) pipe.draw(window);
        window.draw(scoreText);
        if (gameOver) window.draw(gameOverText);
        window.display();
    }
    return 0;
}