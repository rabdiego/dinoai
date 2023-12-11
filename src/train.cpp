#include "SFML/Window/Keyboard.hpp"
#include "libs/dino/include/structures.hpp"
#include "libs/dino/include/bot.hpp"
#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

bool allBotsDead(std::vector<DinoAI::Bot *> bots) {
  if (bots.size() == 0) {
    return true;
  }
  return false;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
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

  int numberOfBots = 500;
  std::vector<DinoAI::Bot *> bots;

  for (int i = 0; i < numberOfBots; i++) {
    bots.push_back(new DinoAI::Bot(350, &dinoTextures));
  }

  int frame = 0;
  int gameVelocity = 5;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rng3(0, 3);
  DinoAI::Obstacle obstacle(rng3(rng), 350, 260, &obstacleTextures);

  while (window.isOpen()) {
    // Handling events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (allBotsDead(bots) && event.key.code == sf::Keyboard::Space) {
        for (int i = 0; i < numberOfBots; i++) {
          bots.push_back(new DinoAI::Bot(350, &dinoTextures));
        }
        obstacle.reborn(rng3(rng));
        gameVelocity = 7;
        frame = 0;
      }
    }

    if (gameVelocity <= 25 && frame % 500 == 0) {
      gameVelocity += 5;
    }

    // Clearing the window
    window.clear(sf::Color::White);

    for (auto &bot : bots) {
      arma::mat input = arma::mat(8, 1);
      input[0] = bot->rect.top / 400;
      input[1] = bot->rect.height / 96;
      input[2] = obstacle.rect.left / 800;
      input[3] = obstacle.rect.top / 280;
      input[4] = obstacle.rect.width / 104;
      input[5] = obstacle.rect.height / 100;
      input[6] =
          (350 - obstacle.rect.top + obstacle.rect.height) / 220;
      input[7] = (double)gameVelocity / 30;

      bot->update(input);
      bot->draw(window, frame);
    }

    // Updating and drawing the obstacle
    obstacle.update(gameVelocity);
    obstacle.draw(window, frame);

    int botIdx = 0;
    for (auto &bot : bots) {
      if (obstacle.collidedWithDino(*bot)) {
        bot->die();
        bots.erase(bots.begin() + botIdx);
        botIdx--;
      }
      botIdx++;
    }

    if (obstacle.getPosition().x < -80) {
      obstacle.reborn(rng3(rng));
    }

    if (allBotsDead(bots)) {
      gameVelocity = 0;
    }

    window.display();
    frame++;
  }
}