#ifndef OBJETOXEY_H
#define OBJETOXEY_H

class ObjetoXeY{

public:
    ObjetoXeY(){
        x=0;
        y=0;
    }
    ObjetoXeY(const int x,const int y){
        this->x = x;
        this->y = y;
    }    
    int x;
    int y;
};

#endif