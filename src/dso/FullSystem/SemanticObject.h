#pragma once

#include <sys/types.h> 

#include <vector>

class SemanticObject {
public:
    SemanticObject(std::vector<int> raw_data);
    SemanticObject(int, int, int, int, int);
    int get_x();
    int get_y();
    int get_type();
    int get_height();
    int get_width();
private:
	int x,y,h,w;
	int object_type;
};
