//
// Created by Jiazhuo Mi on 2019/4/17.
//
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

//build an enum to represent elements in map
enum MapElements{
    EMPTY_ROOM, BLOOD, SLIM, GOOP, WUMPUS, PIT
};
//arrow and hunter moving direction
enum Direction{
    TO_UP, TO_DOWN, TO_LEFT, TO_RIGHT
};
//recording pos where hunter in map, x pos an y pos are positive
//move to another room
//move up: y++;    move down: y--; move left :   x--; move right: x++
class Hunter{
public:
    Hunter(int x, int y): x(x),y(y){

    }
    //get hunter pos
    int getXPos(){
        return x;
    }

    int getYPos(){
        return y;
    }

    //move hunter pos
    void move(Direction direction){
        if(direction == Direction::TO_UP){
            y++;
        } else if(direction == Direction::TO_DOWN){
            y--;
        } else if(direction == Direction::TO_LEFT){
            x--;
        } else if(direction == Direction::TO_RIGHT){
            x++;
        } else{
            cout<<"ERR: direction undefined"<<endl;
        }
        checkIsCloseToEdge(x);
        checkIsCloseToEdge(y);
    }

private:
    int x;
    int y;

    void checkIsCloseToEdge(int &pos){
        if(pos > 11){
            pos = pos - 12;
        } else if(pos < 0){
            pos = 12 + pos;
        }
    }
};

//Map for game will be grid of cave room,
// cave room can be occupied by the Hunter,the Wumpus,the pit
//player can hear wind near pit;smell something foul near Wumpus
//map is 12X12 grid room;3,4,5 pits
class Map{
public:
    Map(){
        hunter = nullptr;
        //init rooms
        vector<MapElements> rows(12,MapElements::EMPTY_ROOM);
        vector<vector<MapElements >> map(12, rows);
        rooms = map;
        visitedRooms = map;
    }
    ~Map(){
        delete hunter;
    }
    //rand init map
    void init(){


        //add pits
        int pitsNumber = 3 + (rand()%30)/10;
        addPits(pitsNumber);

        //add wumpus
        int WumpusXPos = rand()%12,WumpusYPos = rand()%12;
        while(rooms[WumpusYPos][WumpusXPos] == MapElements::PIT){
            WumpusXPos = rand()%12;
            WumpusYPos = rand()%12;
        }
        initWumpus(WumpusXPos,WumpusYPos);

        int hunterXPos = rand()%12;
        int hunterYPos = rand()%12;
        while(rooms[hunterXPos][hunterYPos] != MapElements::EMPTY_ROOM){
            hunterXPos  = rand() % 12;
            hunterYPos = rand()% 12;
        }
        initHunter(hunterXPos,hunterYPos);
    }


    //init hunter
    void initHunter(int x,int y){
        delete hunter;
        hunter = new Hunter(x,y);
    }
    //can smell blood
    void initWumpus(int x, int y){
        int upFirstPos = y+1;
        int upSecondPos = y+2;
        int downFirstPos = y-1;
        int downSecondPos = y-2;
        int leftFirstPos = x - 1;
        int leftSecondPos = x - 2;
        int rightFirstPos = x+1;
        int rightSecondPos = x+2;
        //check edge pos
        checkEdgeElements(upFirstPos);
        checkEdgeElements(upSecondPos);
        checkEdgeElements(downFirstPos);
        checkEdgeElements(downSecondPos);
        checkEdgeElements(leftFirstPos);
        checkEdgeElements(leftSecondPos);
        checkEdgeElements(rightFirstPos);
        checkEdgeElements(rightSecondPos);

        //insert wumpus
        rooms[y][x] = MapElements ::WUMPUS;
        //insert blood
        checkGoopPos(leftFirstPos,y);
        checkGoopPos(leftSecondPos,y);
        checkGoopPos(rightFirstPos,y);
        checkGoopPos(rightSecondPos,y);

        checkGoopPos(x,upFirstPos);
        checkGoopPos(x,upSecondPos);
        checkGoopPos(x,downFirstPos);
        checkGoopPos(x,downSecondPos);

        checkGoopPos(leftFirstPos,upFirstPos);
        checkGoopPos(rightFirstPos,upFirstPos);
        checkGoopPos(leftFirstPos,downFirstPos);
        checkGoopPos(rightFirstPos,downFirstPos);
    }

    //can hear wind around the pit
    void initPits(int x, int y){
        int upPos = y+1;
        int downPos = y-1;
        int leftPos = x-1;
        int rightPos = x+1;

        //check edge pits
        checkEdgeElements(upPos);
        checkEdgeElements(downPos);
        checkEdgeElements(rightPos);
        checkEdgeElements(leftPos);

        //init elements
        rooms[y][x] = MapElements::PIT;
        insertSlime(x,upPos);
        insertSlime(x,downPos);
        insertSlime(leftPos,y);
        insertSlime(rightPos,y);
    }

    //print room graph
    void printMap(){
        //get rows,i == y,;j == x
        cout<<endl;
        for(int i = rooms.size() - 1; i >= 0;i--){
            auto &rows = rooms[i];
            //iterator
            for(int j = 0; j < rows.size();j++){
                auto &ele = rows[j];
                cout<<" ";
                if(j == hunter->getXPos() && i == hunter->getYPos()){
                    cout<<"O";
                } else if(ele == MapElements::EMPTY_ROOM){
                    cout<<"_";
                } else if(ele == MapElements::BLOOD){
                    cout<<"B";
                } else if(ele == MapElements::GOOP){
                    cout<<"G";
                } else if(ele == MapElements::PIT){
                    cout<<"P";
                } else if (ele == MapElements::SLIM){
                    cout<<"S";
                } else if(ele == MapElements::WUMPUS){
                    cout<<"W";
                } else{
                    //Error
                    cout<<"<E>";
                }
                cout<<" ";
            }
            cout<<endl;
        }
    }

    void printVisitedMap(){
        //get rows,i == y,;j == x
        cout<<endl;
        for(int i = visitedRooms.size() - 1; i >= 0;i--){
            auto &rows = visitedRooms[i];
            //iterator
            for(int j = 0; j < rows.size();j++){
                auto &ele = rows[j];
                cout<<" ";
                if(j == hunter->getXPos() && i == hunter->getYPos()){
                    cout<<"O";
                } else if(ele == MapElements::EMPTY_ROOM){
                    cout<<"_";
                } else if(ele == MapElements::BLOOD){
                    cout<<"B";
                } else if(ele == MapElements::GOOP){
                    cout<<"G";
                } else if(ele == MapElements::PIT){
                    cout<<"P";
                } else if (ele == MapElements::SLIM){
                    cout<<"S";
                } else if(ele == MapElements::WUMPUS){
                    cout<<"W";
                } else{
                    //Error
                    cout<<"<E>";
                }
                cout<<" ";
            }
            cout<<endl;
        }
    }

    //get room elements at hunter pos
    MapElements & getHunterSituation(){
        return rooms[hunter->getYPos()][hunter->getXPos()];
    }

    //update visitedMap
    void updateVisitedMap(){
        int x = hunter->getXPos();
        int y = hunter->getYPos();
        visitedRooms[y][x] = rooms[y][x];
    }

    Hunter *hunter;
    vector<vector<MapElements>> visitedRooms;
    vector<vector<MapElements>> rooms;
private:
    void checkEdgeElements(int &pos){
        if(pos > 11){
            pos = pos - 12;
        } else if (pos < 0){
            pos = 12 + pos;
        }
    }

    //insert after Slime
    void checkGoopPos(int x, int y){
        if(rooms[y][x] == MapElements::SLIM){
            rooms[y][x] = MapElements ::GOOP;
        }else if(rooms[y][x] != MapElements::PIT){
            rooms[y][x] = MapElements ::BLOOD;
        }
    }

    //insert Slime
    void insertSlime(int x,int y){
        if(rooms[y][x] != MapElements::SLIM && rooms[y][x] != MapElements ::PIT){
            rooms[y][x] = MapElements ::SLIM;
        }
    }

    //add pits
    void addPits(int num){
        int x = rand()%12;
        int y = rand()%12;
        for(int i = 0; i < num;i++){
            while(rooms[y][x] == MapElements::WUMPUS || rooms[y][x] == MapElements::PIT){
                x = rand() % 12;
                y = rand() % 12;
            }
            initPits(x,y);
        }
    }


};

//control of the whole logic flow
class Game{
public:
    Game(){
        map = new Map;
    }
    ~Game(){
        delete map;
    }
    void startGame(){
        srand(unsigned(time(0)));
        cout<<"Welcome To Hunt the Wumpus Game!"<<endl;
        map->init();
        map->printMap();
        while(input()){
            //move to next step
        }
        //game over
        cout<<"game over!"<<endl;
    }

    bool input(){
        char c = 0;
        char r = 0;
        while(true){
            cout<<"Type \"m\" to move hunter.Type \"s \" to shoot the Wumpus."<<endl;
            cin>>c;
            if(c == 'm' || c == 's'){
                cout<<"Type u(up),d(down),l(left),r(right) to point direction."<<endl;
                cin>>r;
                if(r == 'l' || r == 'r' || r == 'u' || r == 'd'){
                    break;
                }
            }
            cout<<"invalid input."<<endl;
        }
        Direction dir = Direction ::TO_DOWN;
        if(r == 'l'){
            dir = Direction ::TO_LEFT;
        } else if (r == 'r'){
            dir = Direction ::TO_RIGHT;
        } else if (r == 'u'){
            dir = Direction ::TO_UP;
        } else if (r == 'd'){
            dir = Direction ::TO_DOWN;
        }
        return (c == 'm') ? moveHunter(dir) : shoot(dir);
    }

    //move hunter position
    bool moveHunter(Direction dir){
        //move hunter pos
        map->hunter->move(dir);
        //update visitedMap
        map->updateVisitedMap();
        //report hunter status
        return reportState();
    }

    //shoot the wumpus
    bool shoot(Direction dir){
        bool isHitWumpus = false;
        //check arrow path whether located Wumpus
        if(dir == Direction::TO_DOWN || dir == Direction::TO_UP){
            int x = map->hunter->getXPos();
            for(auto & rows: map->rooms){
                if(rows[x] == MapElements::WUMPUS){
                    isHitWumpus = true;
                }
            }
        }else{
            int y = map->hunter->getYPos();
            for(auto &ele : map->rooms[y]){
                if(ele == MapElements::WUMPUS){
                    isHitWumpus =true;
                }
            }
        }
        //report result of game
        if(isHitWumpus){
            cout<<"Your arrow hit the wumpus. You win."<<endl;
        } else{
            cout<<"You just shot yourself. You lose."<<endl;
        }
        return false;
    }
    //return live or dead
    bool reportState(){
        cout<<"Your current position in the room is ("<<map->hunter->getXPos()<<","<<map->hunter->getYPos()<<")"<<endl;
        map->printVisitedMap();
        auto &ele =  map->getHunterSituation();
        if(ele == MapElements::PIT){
            cout<<"You fell down a bottomless pit,You lose."<<endl;
            return false;
        } else if (ele == MapElements::WUMPUS){
            cout<<"You walked into the Wumpus. You lose"<<endl;
            return false;
        } else if(ele == MapElements::SLIM){
            cout<<"I can hear the wind"<<endl;
        } else if(ele == MapElements::BLOOD){
            cout<<"I smell something foul"<<endl;
        } else if (ele == MapElements::GOOP){
            cout<<"I can hear the wind and smell something foul"<<endl;
        }
        return true;
    }

    Map *map;
};
