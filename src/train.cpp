#include "SFML/Window/Keyboard.hpp"
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

  int numberOfBots = 50;
  std::vector<DinoAI::Bot *> bots;

  for (int i = 0; i < numberOfBots; i++) {
    bots.push_back(new DinoAI::Bot(350));
  }

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
      } else if (allBotsDead(bots) && event.key.code == sf::Keyboard::Space) {
        for (int i = 0; i < numberOfBots; i++) {
          bots.push_back(new DinoAI::Bot(350));
        }
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

    for (auto &bot : bots) {
      arma::mat input = arma::mat(8, 1);
      input[0] = bot->rect.top / 400;
      input[1] = bot->rect.height / 96;
      input[2] = obstacles[0]->rect.left / 800;
      input[3] = obstacles[0]->rect.top / 400;
      input[4] = obstacles[0]->rect.width / 120;
      input[5] = obstacles[0]->rect.height / 90;
      input[6] =
          (obstacles[0]->rect.top + obstacles[0]->rect.height - 350) / 70;
      input[7] = (double)gameVelocity / 17;

      bot->update(input);
      bot->draw(window, frame);
    }

    // Updating and drawing the obstacles
    int obsIdx = 0;
    for (auto &obstacle : obstacles) {
      obstacle->update(gameVelocity);
      obstacle->draw(window, frame);

      int botIdx = 0;
      for (auto &bot : bots) {
        if (obstacle->collidedWithDino(*bot)) {
          bot->die();
          bots.erase(bots.begin() + botIdx);
          botIdx--;
        }
        botIdx++;
      }

      if (obstacle->getPosition().x < -80) {
        obstacles.erase(obstacles.begin() + obsIdx);
        obsIdx--;
      }

      obsIdx++;
    }

    if (allBotsDead(bots)) {
      gameVelocity = 0;
    }

    window.display();
    frame++;
  }
}