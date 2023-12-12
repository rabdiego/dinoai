#include "SFML/Window/Keyboard.hpp"
#include "libs/dino/include/bot.hpp"
#include "libs/dino/include/dino.hpp"
#include "libs/dino/include/obstacle.hpp"
#include "libs/dino/include/structures.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

/**
 * Check if all bots are dead
 *
 * @param bots List of bots with their scores
 *
 * @return boolean, if all the bots are dead
 */
bool allBotsDead(std::vector<std::pair<DinoAI::Bot *, int>> bots) {
  for (auto &bot : bots) {
    if (bot.first->isAlive) {
      return false;
    }
  }
  return true;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Play");
  window.setFramerateLimit(600);

  // Bot textures
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

  // Bots
  int numberOfBots = 1000;
  std::vector<std::pair<DinoAI::Bot *, int>> bots;

  // Random number generator - used to choose which bot to spread its genes
  int numberOfSuccessors = 5;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rngSuc(
      0, numberOfSuccessors - 1);

  // Initializing bots
  for (int i = 0; i < numberOfBots; i++) {
    bots.push_back(std::make_pair(new DinoAI::Bot(350, &dinoTextures), 0));
  }

  // Game information
  int frame = 0;
  int gameVelocity = 15;

  // Random number generator - used to generate obstacles
  std::uniform_int_distribution<std::mt19937::result_type> rng3(0, 3);
  DinoAI::Obstacle obstacle(rng3(rng), 350, 260, &obstacleTextures);

  // Max itteration limit
  int epoch = 0;
  int maxEpoch = 200;
  int scoreLimiar = 10000;

  int maxScore = 0;

  while (window.isOpen()) {
    // Handling events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // Clearing the window
    window.clear(sf::Color::White);

    // Sorting by score (how much time a bot could get being alive)
    std::sort(bots.begin(), bots.end(), [](auto &left, auto &right) {
      return left.second > right.second;
    });

    // Generating the input for bots
    for (auto &bot : bots) {
      if (bot.first->isAlive) {
        arma::mat input = arma::mat(7, 1);
        input[0] = bot.first->rect.top / 400;
        input[1] = bot.first->rect.height / 96;
        input[2] = obstacle.rect.left / 800;
        input[3] = obstacle.rect.top / 280;
        input[4] = obstacle.rect.width / 104;
        input[5] = obstacle.rect.height / 100;
        input[6] = (350 - obstacle.rect.top + obstacle.rect.height) / 220;

        bot.first->update(input);
        bot.second++;
        bot.first->draw(window, frame);
      }
    }

    // Updating and drawing the obstacle
    obstacle.update(gameVelocity);
    obstacle.draw(window, frame);

    // Checking collisions
    for (auto &bot : bots) {
      if (obstacle.collidedWithDino(*bot.first)) {
        bot.first->die();
      }
    }

    // Regenerating obstacles
    if (obstacle.getPosition().x < -80) {
      obstacle.reborn(rng3(rng));
    }

    // Checking if all bots are dead
    if (allBotsDead(bots)) {
      // Saving its information on disk
      if (bots[0].second > maxScore) {
        maxScore = bots[0].second;
        bots[0].first->brain->save("runs/best_hidden.bin", "runs/best_out.bin");
      }

      // Displaying info on screen
      std::cout << "EPOCH " << epoch + 1 << " - MAX = " << bots[0].second
                << "\n\n";

      /* Creating the new generation, with the genes of the
       * top (numberOfSuccessors) bots
       */
      int idx = 0;
      for (auto &bot : bots) {
        if (idx > numberOfSuccessors) {
          int asd = rngSuc(rng);
          bot.first = new DinoAI::Bot(*bots[asd].first);
        }
        idx++;
        bot.second = 0;
      }

      // Restarting the scene
      obstacle.reborn(rng3(rng));
      frame = 0;
      epoch++;
    }

    // Checking if bot already knows how to play the game
    if (bots[0].second > scoreLimiar) {
      bots[0].first->brain->save("runs/best_hidden.bin", "runs/best_out.bin");
      std::cout << "BEST MODEL ACHIEVED\n";
      break;
    }

    window.display();
    frame++;

    if (epoch > maxEpoch) {
      break;
    }
  }
}