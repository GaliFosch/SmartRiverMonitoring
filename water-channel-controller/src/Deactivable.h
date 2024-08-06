#ifndef __DEACTIVABLE_H__
#define __DEACTIVABLE_H__

class Deactivable {
    public:
        virtual void deactivate() { isActive = false; return; };
        virtual void activate() { isActive = true; return; };
    protected:
        int isActive;
};

#endif