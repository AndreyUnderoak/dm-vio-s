#include "FullSystem/SemanticObject.h"


SemanticObject::SemanticObject(std::vector<int> raw_data){
    // Creating socket file descriptor 
    if ( raw_data.size() < 5 ) {
        x,y,h,w = 0;
		return;
	} 
    x           = raw_data.at(0);
    y           = raw_data.at(1);
    h           = raw_data.at(2);
    w           = raw_data.at(3);
    object_type = raw_data.at(4);

}
SemanticObject::SemanticObject(int x = 0, int y = 0, int h = 0, int w = 0, int object_type = 0):x(x),y(y),h(h),w(w),object_type(object_type){}
	
int SemanticObject::get_x(){
    return x;
}
int SemanticObject::get_y(){
    return y;
}
int SemanticObject::get_type(){
    return object_type;
}
int SemanticObject::get_height(){
    return h;
}
int SemanticObject::get_width(){
    return w;
}
