#include "libs/dino/include/obstacle.hpp"

using namespace DinoAI;

Obstacle::Obstacle(int id, int floorHeight, int skyHeight) {
  textures.cactae1.loadFromFile("assets/obstacles/cactae1.png");
  textures.cactae2.loadFromFile("assets/obstacles/cactae2.png");
  textures.cactae3.loadFromFile("assets/obstacles/cactae3.png");
  textures.ptero1.loadFromFile("assets/obstacles/ptero1.png");
  textures.ptero2.loadFromFile("assets/obstacles/ptero2.png");

  dimensions.cactae1 = textures.cactae1.getSize();
  dimensions.cactae2 = textures.cactae2.getSize();
  dimensions.cactae3 = textures.cactae3.getSize();
  dimensions.ptero = textures.ptero2.getSize();

  sprites.cactae1.setTexture(textures.cactae1);
  sprites.cactae2.setTexture(textures.cactae2);
  sprites.cactae3.setTexture(textures.cactae3);
  sprites.ptero1.setTexture(textures.ptero1);
  sprites.ptero2.setTexture(textures.ptero2);

  this->floorHeight = floorHeight;
  this->id = id;
  position.x = 880;

  switch (id) {
  case 0:
    position.y = (float)floorHeight - dimensions.cactae1.y;
    break;
  case 1:
    position.y = (float)floorHeight - dimensions.cactae2.y;
    break;
  case 2:
    position.y = (float)floorHeight - dimensions.cactae3.y;
    break;
  case 3:
    position.y = (float)skyHeight - dimensions.ptero.y;
    break;
  default:
    position.y = (float)floorHeight - dimensions.cactae1.y;
    break;
  }
}

void Obstacle::update(float gameVelocity) { position.x -= gameVelocity; }

void Obstacle::draw(sf::RenderWindow &window, int frame) {
  int framerate = 20;
  switch (id) {
  case 0:
    sprites.cactae1.setPosition(position);
    window.draw(sprites.cactae1);
    break;
  case 1:
    sprites.cactae2.setPosition(position);
    window.draw(sprites.cactae2);
    break;
  case 2:
    sprites.cactae3.setPosition(position);
    window.draw(sprites.cactae3);
    break;
  case 3:
    if (frame % framerate < framerate / 2) {
      sprites.ptero1.setPosition(position);
      window.draw(sprites.ptero1);
      break;
    } else {
      sprites.ptero2.setPosition(position);
      window.draw(sprites.ptero2);
      break;
    }
  default:
    sprites.cactae1.setPosition(position);
    window.draw(sprites.cactae1);
    break;
  }
}

sf::Vector2f Obstacle::getPosition() { return position; }