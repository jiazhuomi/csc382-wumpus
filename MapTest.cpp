//
// Created by Jiazhuo Mi on 2019/4/17.
//
#include "catch.hpp"
#include <iostream>
#include "Wumpus.hpp"
using namespace std;
TEST_CASE("hunterDirectionTest"){
    Map map;
    map.initHunter(4,4);
    map.printMap();
    map.hunter->move(Direction::TO_UP);
    map.printMap();
    map.hunter->move(Direction::TO_DOWN);
    map.printMap();
    map.hunter->move(Direction::TO_LEFT);
    map.printMap();
    map.hunter->move(Direction::TO_RIGHT);
    map.printMap();
}

TEST_CASE("pitsLocation Test"){
    cout<<"====Pits Location Test===="<<endl;
    Map map;
    map.initPits(0,0);
    map.initPits(3,1);
    map.initPits(2,6);
    map.initPits(8,6);
    map.initPits(8,7);
    map.printMap();
}
TEST_CASE("WumpusLocationTest"){
    cout<<"==========Wumpus Location Test=========="<<endl;
    Map map;
    map.initWumpus(9,5);
    map.printMap();
    map.initWumpus(0,6);
    map.printMap();
    map.initWumpus(7,1);
    map.printMap();
}

TEST_CASE("pitsHunterAndWumpusLocationTest"){
    Map map;
    map.hunter->move(Direction::TO_LEFT);
    map.hunter->move(Direction::TO_LEFT);
    map.initPits(0,4);
    map.initPits(3,5);
    map.initPits(8,1);
    map.initPits(6,11);
    map.initWumpus(7,2);
    map.printMap();
}