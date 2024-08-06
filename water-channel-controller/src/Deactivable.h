#ifndef __DEACTIVABLE_H__
#define __DEACTIVABLE_H__

class Deactivable {
    public:
        virtual void deactivate();
        virtual void activate();
    protected:
        int isActive;
};

#endif