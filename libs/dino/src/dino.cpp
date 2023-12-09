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

  position = {10, (float)floorHeight - dimensions.walking.y};
  velocity = 0;
  acceleration = 0.8;

  rect = sf::Rect<float>(position.x, position.y, textures.walking1.getSize().x,
                         textures.walking1.getSize().y);

  isAlive = true;
  isSneaking = false;
  isJumping = false;

  this->floorHeight = floorHeight;
}

Dino::Dino() {}

void Dino::update() {
  velocity += acceleration;
  position.y += velocity;
  rect.top = position.y;

  if (isSneaking && position.y >= floorHeight - dimensions.sneaking.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.sneaking.y;
    rect.top = position.y;
    rect.height = textures.walking1.getSize().y;

  } else if (isAlive && position.y >= floorHeight - dimensions.walking.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.walking.y;
    rect.top = position.y;
    rect.height = textures.walking1.getSize().y;

  } else if (!isAlive && position.y >= floorHeight - dimensions.dead.y) {
    isJumping = false;
    position.y = floorHeight - dimensions.dead.y;
    rect.top = position.y;
    rect.height = textures.sneaking1.getSize().y;
  }
}

void Dino::draw(sf::RenderWindow &window, int frame) {
  int framerate = 20;
  if (isAlive) {
    if (frame % framerate < framerate / 2) {
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
  } else {
    sprites.dead.setPosition(position);
    window.draw(sprites.dead);
  }
}

void Dino::jump() {
  velocity = -17;
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

void Dino::reborn() {
  isAlive = true;
  position.y = (float)floorHeight - dimensions.walking.y;
}