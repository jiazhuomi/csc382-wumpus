//
// Created by Jiazhuo Mi on 2019/4/17.
//

#include "catch.hpp"
#include <iostream>
#include "Wumpus.hpp"

TEST_CASE("randInitMapTest"){
    srand(unsigned(time(0)));
    Game game1;
    game1.map->init();
    game1.map->printMap();
    Game game2;
    game2.map->init();
    game2.map->printMap();
    Game game3;
    game3.map->init();
    game3.map->printMap();
    Game game4;
    game4.map->init();
    game4.map->printMap();
    Game game5;
    game5.map->init();
    game5.map->printMap();
    Game game6;
    game6.map->init();
    game6.map->printMap();
    Game game7;
    game7.map->init();
    game7.map->printMap();
    Game game8;
    game8.map->init();
    game8.map->printMap();
}

TEST_CASE("moveHunterToPitTest"){
    Game game9;
    game9.map->initPits(0,7);
    game9.map->initPits(3,5);
    game9.map->initPits(10,9);
    game9.map->initPits(2,4);
    game9.map->initWumpus(11,7);
    game9.map->initHunter(3,3);
    game9.map->printMap();
    game9.reportState();
    game9.moveHunter(TO_UP);
    game9.moveHunter(TO_UP);
}
TEST_CASE("moveHunterToWumpusTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(8,7);
    game.map->printMap();
    game.moveHunter(TO_RIGHT);
    game.moveHunter(TO_RIGHT);
    game.moveHunter(TO_RIGHT);
}
TEST_CASE("moveHunterToBloodTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(8,7);
    game.map->printMap();
    game.moveHunter(TO_RIGHT);
}
TEST_CASE("moveHunterToSlimeTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(1,5);
    game.map->printMap();
    game.moveHunter(TO_DOWN);
}
TEST_CASE("moveHunterToGoopTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(1,5);
    game.map->printMap();
    game.moveHunter(TO_UP);
    game.moveHunter(TO_UP);
}
TEST_CASE("shootArrowHitWumpusTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(3,7);
    game.map->printMap();
    game.shoot(TO_LEFT);
}
TEST_CASE("shootArrowHitHunterTest"){
    Game game;
    game.map->initPits(0,7);
    game.map->initPits(3,5);
    game.map->initPits(10,9);
    game.map->initPits(2,4);
    game.map->initWumpus(11,7);
    game.map->initHunter(3,7);
    game.map->printMap();
    game.shoot(TO_UP);
}