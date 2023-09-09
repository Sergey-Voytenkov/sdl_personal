#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "loader_params.hpp"

class Object {
public:
        virtual void draw()=0;
        virtual void update()=0;
        virtual void clean()=0;
    
protected:
    Object(const LoaderParams* pParams) {};
    virtual ~Object() {};
};
#endif
