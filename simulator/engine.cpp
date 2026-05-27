#include <SFML/Graphics.hpp>
#include <cstdint>
#include <U8g2lib.h>
#include <Arduino.h>

static sf::RenderTexture canvas;

// U8G2 internal needs to talk to canvas
void _sim_clearCanvas() {
    canvas.clear(sf::Color::Black);
}

// Forward declarations for functions defined in main.ino
void setup();
void loop();

// Include the Arduino sketch directly
#include "../sketch/main.ino"

// Allow sketch to override FPS via macro
#ifndef SIM_FPS
#define SIM_FPS 60
#endif

int main() {
    simFrameRate = SIM_FPS;
    sf::RenderWindow window(sf::VideoMode(256, 128), "PageStream - U8g2 Simulator");
    window.setFramerateLimit(simFrameRate);

    canvas.create(256, 128);
    canvas.clear(sf::Color::Black);

    sf::RectangleShape pixel(sf::Vector2f(2.0f, 2.0f));
    pixel.setFillColor(sf::Color::White);

    setup();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseMoved) {
                _sim_mouseX = event.mouseMove.x;
                _sim_mouseY = event.mouseMove.y;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) _sim_btnSpace = true;
                if (event.key.code == sf::Keyboard::Up) {
                    simFrameRate += 20;
                    window.setFramerateLimit(simFrameRate);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    simFrameRate = (simFrameRate > 20) ? simFrameRate - 20 : 20;
                    window.setFramerateLimit(simFrameRate);
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) _sim_btnSpace = false;
            }
        }

        loop();

        for (int x = 0; x < 128; x++) {
            for (int bit = 0; bit < 8; bit++) {
                int screenY = (u8g2.pageIndex * 8) + bit;
                pixel.setPosition(x * 2.0f, screenY * 2.0f);
                pixel.setFillColor(((u8g2.buffer[x] >> bit) & 1) ? sf::Color::White : sf::Color::Black);
                canvas.draw(pixel);
            }
        }
        canvas.display();

        window.clear();
        window.draw(sf::Sprite(canvas.getTexture()));
        window.display();

        u8g2.pageIndex++;
        if (u8g2.pageIndex >= u8g2.totalPages) u8g2.pageIndex = 0;
        u8g2.clearBuffer();
    }
    return 0;
}
