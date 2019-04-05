//
//  Cashier.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Cashier_hpp
#define Cashier_hpp

#include <stdio.h>
#include <queue>
//#include "Event.hpp"
class Event;
class Cashier{
public:
    bool isAvailable;
    long nextAvailTime;
    Event* currentlyServicing;
    std::deque<Event*> line;
    Cashier(){
        isAvailable = true;
        currentlyServicing = nullptr;
        line = std::deque<Event*>();
        nextAvailTime = 0;
    };
    
    void helpCustomer(Event * e){
        isAvailable = false;
        currentlyServicing = e;
    };
    
    void finishCustomer(){
        isAvailable = true;
        currentlyServicing = nullptr;
    };
};
#endif /* Cashier_hpp */
