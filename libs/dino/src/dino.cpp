#include "libs/dino/include/dino.hpp"
#include <SFML/Window/Event.hpp>

using namespace DinoAI;

Dino::Dino(int floorHeight) {
  textures.walking1.loadFromFile("assets/dino/walking1.png");
  textures.walking2.loadFromFile("assets/dino/walking2.png");
  textures.sneaking1.loadFromFile("assets/dino/sneaking1.png");
  textures.sneaking2.loadFromFile("assets/dino/sneaking2.png");
  textures.dead.loadFromFile("assets/dino/dead.png");

  dimensions.walking = textures.walking1.getSize();
  dimensions.sneaking = textures.sneaking1.getSize();
  dimensions.dead = textures.dead.getSize();

  sprites.walking1.setTexture(textures.walking1);
  sprites.walking2.setTexture(textures.walking2);
  sprites.sneaking1.setTexture(textures.sneaking1);
  sprites.sneaking2.setTexture(textures.sneaking2);
  sprites.dead.setTexture(textures.dead);

  position = {10, 0};
  velocity = 0;
  acceleration = 0.18;

  isAlive = true;
  isSneaking = false;
  isJumping = false;

  this->floorHeight = floorHeight;
}

void Dino::update() {
  velocity += acceleration;
  position.y += velocity;

  if (isSneaking && position.y >= floorHeight - dimensions.sneaking.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.sneaking.y;
  } else if (isAlive && position.y >= floorHeight - dimensions.walking.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.walking.y;
  } else if (!isAlive && position.y >= floorHeight - dimensions.dead.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.dead.y;
  }
}

void Dino::draw(sf::RenderWindow &window, int frame) {
  if (frame % 100 < 50) {
    if (isSneaking) {
      sprites.sneaking1.setPosition(position);
      window.draw(sprites.sneaking1);
    } else {
      sprites.walking1.setPosition(position);
      window.draw(sprites.walking1);
    }
  } else {
    if (isSneaking) {
      sprites.sneaking2.setPosition(position);
      window.draw(sprites.sneaking2);
    } else {
      sprites.walking2.setPosition(position);
      window.draw(sprites.walking2);
    }
  }
}

void Dino::jump() {
  velocity = -10;
  isJumping = true;
}

void Dino::sneak() {
  isSneaking = true;
  position.y = floorHeight - dimensions.sneaking.y;
}

void Dino::standUp() {
  isSneaking = false;
  position.y = floorHeight - dimensions.walking.y;
}

void Dino::die() { isAlive = false; }
