#include "SFML/Window/Keyboard.hpp"
#include "libs/dino/include/bot.hpp"
#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <random>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "PvC");
  window.setFramerateLimit(60);

  DinoAI::DinoTextures dinoTextures;
  dinoTextures.walking1.loadFromFile("assets/dino/walking1.png");
  dinoTextures.walking2.loadFromFile("assets/dino/walking2.png");
  dinoTextures.sneaking1.loadFromFile("assets/dino/sneaking1.png");
  dinoTextures.sneaking2.loadFromFile("assets/dino/sneaking2.png");
  dinoTextures.dead.loadFromFile("assets/dino/dead.png");

  DinoAI::ObstacleTextures obstacleTextures;
  obstacleTextures.cactae1.loadFromFile("assets/obstacles/cactae1.png");
  obstacleTextures.cactae2.loadFromFile("assets/obstacles/cactae2.png");
  obstacleTextures.cactae3.loadFromFile("assets/obstacles/cactae3.png");
  obstacleTextures.ptero1.loadFromFile("assets/obstacles/ptero1.png");
  obstacleTextures.ptero2.loadFromFile("assets/obstacles/ptero2.png");

  DinoAI::Bot bot("runs/0/best_hidden.bin", "runs/0/best_out.bin", 350,
                  &dinoTextures);
  DinoAI::Dino player(750, &dinoTextures);

  int frame = 0;
  int gameVelocity = 15;

  int pVelocity = gameVelocity;
  int bVelocity = gameVelocity;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rng3(0, 3);
  int obsId = rng3(rng);
  DinoAI::Obstacle obstacle(obsId, 350, 260, &obstacleTextures);
  DinoAI::Obstacle obstacle2(obsId, 750, 660, &obstacleTextures);

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
      } else if ((!player.isAlive || !bot.isAlive) &&
                 event.key.code == sf::Keyboard::Space) {
        bot.reborn();
        player.reborn();
        pVelocity = gameVelocity;
        bVelocity = gameVelocity;
        obsId = rng3(rng);
        obstacle.reborn(obsId);
        obstacle2.reborn(obsId);
        frame = 0;
      }
    }

    // Clearing the window
    window.clear(sf::Color::White);

    // Updating and drawing the player
    if (bot.isAlive) {
      arma::mat input = arma::mat(7, 1);
      input[0] = bot.rect.top / 400;
      input[1] = bot.rect.height / 96;
      input[2] = obstacle.rect.left / 800;
      input[3] = obstacle.rect.top / 280;
      input[4] = obstacle.rect.width / 104;
      input[5] = obstacle.rect.height / 100;
      input[6] = (350 - obstacle.rect.top + obstacle.rect.height) / 220;

      bot.update(input);
    }
    bot.draw(window, frame);

    player.update();
    player.draw(window, frame);

    // Updating and drawing the obstacle
    obstacle.update(bVelocity);
    obstacle.draw(window, frame);
    obstacle2.update(pVelocity);
    obstacle2.draw(window, frame);

    if (obstacle.collidedWithDino(bot)) {
      bot.die();
      bVelocity = 0;
    }

    if (obstacle2.collidedWithDino(player)) {
      player.die();
      pVelocity = 0;
    }

    if (obstacle.getPosition().x < -80) {
      obsId = rng3(rng);
      obstacle.reborn(obsId);
      obstacle2.reborn(obsId);
    }

    window.display();
    frame++;
  }
}