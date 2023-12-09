#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
  window.setFramerateLimit(60);

  DinoAI::Dino player(350);
  std::vector <DinoAI::Obstacle*> obstacles;
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

    if (frame % 100 == 0) {
      obstacles.push_back(new DinoAI::Obstacle(3, 350, 250));
    }

    window.clear(sf::Color::White);

    player.update();
    player.draw(window, frame);

    int obsIdx = 0;
    for (auto& obstacle : obstacles) {
      obstacle->update(9);
      obstacle->draw(window, frame);

      if (obstacle->getPosition().x < -80) {
        obstacles.erase(obstacles.begin() + obsIdx);
      }

      obsIdx++;
    }

    window.display();
    frame++;
  }
}