# DinoAI
> by `rabdiego`

## Brief

DinoAI is a personal project that aims to build a bot capable of playing the Chrome Dino game, using Machine Learning techniques.

## Dependencies

Make sure to have the following softwares installed, in order to run this repository locally:

- C++
- CMake
- Armadillo library
- SFML library

## Compile and run

1. Using CMake, generate the Make build system:  
`cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .`
2. Then choose which binary to make:  
`make train`
3. Run  
`./bin/train`

## Usage

This project is subdivided in three programs:

- train
- play
- pvc

### Train
This program will train a model capable of playing the game, using a Machine Learning method called Reinforcement Learning.  

Basically, it will generate a number `N` of random bots, with different **Neural Networks** initialized, and then it will make them play the game.  
When all of them lose, the program will then take the best bots (using a user defined metric, in this case it can be simple as just seeing how far the bot gone), and copying their "brains" to the rest of the `N` bots.  
Finally, it will apply some mutations to those bots, trying to get a better bot by chance.  
After some epochs of training, it is expected to, just like how evolution works IRL, have a bot truly capable of playing the game.

### Play
This one is simple - it is just the Chrome Dino game, where the user can play it. `W` for jumping, and `S` for sneaking.

### PvC
In this program, the user can compete against the computer (given a saved model).
