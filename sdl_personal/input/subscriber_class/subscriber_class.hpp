#ifndef SUBSRIBER_HPP
#define SUBSRIBER_HPP

// This classes purpose is to make getting inputs easier. Instead of a single object checking for a change in 
class Subscriber {
public:
    virtual void activateResponse()=0;
};

#endif
