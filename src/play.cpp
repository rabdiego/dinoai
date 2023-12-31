#include "SFML/Window/Keyboard.hpp"
#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <random>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
  window.setFramerateLimit(60);

  // Player textures
  DinoAI::DinoTextures dinoTextures;
  dinoTextures.walking1.loadFromFile("assets/dino/walking1.png");
  dinoTextures.walking2.loadFromFile("assets/dino/walking2.png");
  dinoTextures.sneaking1.loadFromFile("assets/dino/sneaking1.png");
  dinoTextures.sneaking2.loadFromFile("assets/dino/sneaking2.png");
  dinoTextures.dead.loadFromFile("assets/dino/dead.png");

  // Obstacles textures
  DinoAI::ObstacleTextures obstacleTextures;
  obstacleTextures.cactae1.loadFromFile("assets/obstacles/cactae1.png");
  obstacleTextures.cactae2.loadFromFile("assets/obstacles/cactae2.png");
  obstacleTextures.cactae3.loadFromFile("assets/obstacles/cactae3.png");
  obstacleTextures.ptero1.loadFromFile("assets/obstacles/ptero1.png");
  obstacleTextures.ptero2.loadFromFile("assets/obstacles/ptero2.png");

  // Game information
  DinoAI::Dino player(350, &dinoTextures);
  int frame = 0;
  int gameVelocity = 15;

  // Random number generator - used to generate obstacles
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rng3(0, 3);

  // Obstacle
  DinoAI::Obstacle obstacle(rng3(rng), 350, 260, &obstacleTextures);

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
        obstacle.reborn(rng3(rng));
        gameVelocity = 15;
        frame = 0;
      }
    }

    // Clearing the window
    window.clear(sf::Color::White);

    // Updating and drawing the player
    player.update();
    player.draw(window, frame);

    // Updating and drawing the obstacle
    obstacle.update(gameVelocity);
    obstacle.draw(window, frame);

    // Checking collisions
    if (obstacle.collidedWithDino(player)) {
      player.die();
      gameVelocity = 0;
    }

    // Regenerating obstalces
    if (obstacle.getPosition().x < -80) {
      obstacle.reborn(rng3(rng));
    }

    window.display();
    frame++;
  }
}