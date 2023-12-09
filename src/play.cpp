#include "libs/dino/include/dino.hpp"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
  window.setFramerateLimit(60);

  DinoAI::Dino player(350);
  int frame = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (player.isAlive) {
        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::W && player.isSneaking == false &&
              player.isJumping == false) {
            player.jump();
          } else if (event.key.code == sf::Keyboard::S &&
                     player.isJumping == false && player.isSneaking == false) {
            player.sneak();
          }
        } else if (event.type == sf::Event::KeyReleased) {
          if (event.key.code == sf::Keyboard::S && player.isSneaking == true) {
            player.standUp();
          }
        }
      }
    }

    window.clear(sf::Color::White);
    player.update();
    player.draw(window, frame);
    window.display();
    frame++;
  }
}