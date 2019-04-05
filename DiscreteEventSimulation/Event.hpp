//
//  Event.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <string>
#include "Cashier.hpp"
class Event {
public:
    long arrivalTime = 0;
    long beginService = 0;
    long endService = 0;
    int id;
    long serviceDuration = 0;
    long nextOccurance = 0;
    long elapsedWaitTime = 0;
    long queueLen = 0;
    std::string type;
    int typeRank;
    Cashier* cashier;
    double totalServiceTime = 0;
    Event(long _arrival, long _sd){
        arrivalTime = _arrival;
        nextOccurance = _arrival;
        serviceDuration = _sd;
        type = "Arrive";
        cashier = nullptr;
        typeRank = 0;
        
    }
    Event(long _arrival, long _sd, int _id){
        arrivalTime = _arrival;
        nextOccurance = _arrival;
        serviceDuration = _sd;
        type = "Arrive";
        id = _id;
        typeRank = 0;
        //remainingServiceDuration = 0;
        cashier = nullptr;
    }
    
    void calcTotalServiceTime(){
        totalServiceTime = serviceDuration + elapsedWaitTime;
    }
    
};
#endif /* Event_hpp */
