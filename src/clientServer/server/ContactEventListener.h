/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __ContactEventListener_H__
#define __ContactEventListener_H__


#include <Box2D/Box2D.h>

class ContactEventListener: public b2ContactListener{
public:
    ContactEventListener() = default;
    ~ContactEventListener() = default;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};


#endif //__ContactEventListener_H__
