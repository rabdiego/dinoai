#include "SFML/Window/Keyboard.hpp"
#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
  window.setFramerateLimit(60);

  DinoAI::Dino player(350);
  std::vector<DinoAI::Obstacle *> obstacles;
  int frame = 0;
  int gameVelocity = 7;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rng3(0, 3);

  while (window.isOpen()) {
    // Handling events
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
      } else if (event.key.code == sf::Keyboard::Space) {
        player.reborn();
        obstacles = std::vector<DinoAI::Obstacle *>();
        gameVelocity = 7;
        frame = 0;
      }
    }

    // Appending a new obstacle
    if (frame % 100 == 0) {
      obstacles.push_back(new DinoAI::Obstacle(rng3(rng), 350, 270));
    }

    if (frame % 1000 == 0) {
      gameVelocity += 2;
    }

    // Clearing the window
    window.clear(sf::Color::White);

    // Updating and drawing the player
    player.update();
    player.draw(window, frame);

    // Updating and drawing the obstacles
    int obsIdx = 0;
    for (auto &obstacle : obstacles) {
      obstacle->update(gameVelocity);
      obstacle->draw(window, frame);

      if (obstacle->collidedWithDino(player)) {
        player.die();
        gameVelocity = 0;
      }

      if (obstacle->getPosition().x < -80) {
        obstacles.erase(obstacles.begin() + obsIdx);
      }

      obsIdx++;
    }

    window.display();
    frame++;
  }
}