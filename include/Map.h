#ifndef MAP_H
#define MAP_H

#include<string>

class Map {
public:
    void loadFromFile(const std::string& filename);
    void draw(); // placeholder for GUI integration
};

#endif //MAP_H
