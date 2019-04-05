//
//  Supermarket.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 4/1/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Supermarket_hpp
#define Supermarket_hpp

#include <stdio.h>
#include "Event.hpp"
#include "Cashier.hpp"
#include "Establishment.hpp"
#include <iostream>
#include <queue>

class Supermarket : public Establishment{
public:
    std::deque<Event*> serviceQ;
    Supermarket(std::priority_queue<Event *, std::vector<Event *>, Compare > &events)
    : Establishment(events){
        serviceQ = std::deque<Event*> ();
    };
    
    
    void nextEvent(){
        Event *current = eventQ.top();
        if(current->type == "Arrive"){
            assert(getExpectedCustomers() == currentCustomers);
            currentCustomers += 1;
            //update the clock
            assert(current -> arrivalTime >= currentTime);
            currentTime = current->arrivalTime;
            //if there is a line...
            if(availableCashier() == nullptr){
                //find the shortest Line
                assert(maxQueueLen() >= 1);
                eventQ.pop();
                Cashier* cashier = getCahierWithMinQueue();
                current->cashier = cashier;
                calcBeginService(cashier, current);
                assert(cashier->line.back()-> endService == current->beginService);
                cashier->line.push_back(current);
                
                current -> queueLen = cashier->line.size();
                current->type = "Servicing";
                eventQ.push(current);
//                serviceQ.push_back(current);
                //get in line
            }else{
                long expectedMin = minQueueLen();
                assert(expectedMin < 1);
                Cashier* cashier = getCahierWithMinQueue();
                current->cashier = cashier;
                current -> queueLen = 1;
                cashier->line.push_back(current);
                current->elapsedWaitTime = 0;
                current-> beginService = currentTime;
                current->type = "Servicing";
                nextEvent();// restart
                return;
            }
            //add BegService event
        }else if(current->type == "Servicing"){
            Cashier* cashier = current->cashier;
            if(cashier == nullptr ){
                std::cout << "Error: trying to begin service w/o available cashier" << std::endl;
                exit(1);
            }
            currentTime = current->beginService;
            cashier->helpCustomer(current);
            
            eventQ.pop();
            calcEndServiceTime(current);
            current -> type = "Finishing";
            eventQ.push(current);
        }
        else if (current->type == "Finishing"){
            assert(current -> endService >= currentTime);
            currentTime = current -> endService;
            current->calcTotalServiceTime();
            
            eventQ.pop();
            current-> cashier->line.pop_front();
            current -> queueLen -= 1;
            currentCustomers -= 1;
            //Cashier* cashier = current->cashier;
            //current->cashier-> finishCustomer();
            current->cashier-> currentlyServicing = nullptr;
            processedCustomers.push_back(*current);
            if(current->cashier->line.empty()){
                current->cashier-> isAvailable = true;
            }
        }else{
            std::cout << "Error: undeterminable type";
            exit(1);
        }
    }
    
    void openForBusiness(long maxDuration){
        int count = 0;
        while(!eventQ.empty()){
            nextEvent();
            count++;
            if (currentTime > maxDuration){
                break;
            }
        }
    }
    
    void calcBeginService(Cashier* cashier, Event * e){
        Event * endOfLine = cashier->line.back();
        e->beginService = endOfLine->beginService + endOfLine -> serviceDuration;
        e->elapsedWaitTime = e->beginService - currentTime;
        e->endService = e->beginService + e->serviceDuration;
        e->nextOccurance = e-> beginService;
    }
    
    long maxQueueLen(){
        long max = 0;
        for(int i = 0; i < cashiers.size(); i++){
            if(cashiers.at(i)->line.size() > max){
                max = cashiers.at(i)-> line.size();
            }
        }
        return max;
    }
    
    long minQueueLen(){
        long min = INT_MAX;
        for(int i = 0; i < cashiers.size(); i++){
            if(cashiers.at(i)->line.size() == 0){
                return 0;
            }
            if(cashiers.at(i)->line.size() < min){
                min = cashiers.at(i)-> line.size();
            }
        }
        return min;
    }
    
    Cashier* getCahierWithMinQueue(){
        long earliestStart = INT_MAX;
        int index = -1;
        for(int i = 0; i < cashiers.size(); i++){
            if(cashiers.at(i)->line.empty()){
                return cashiers.at(i);
            }else{
                Event * e = cashiers.at(i)->line.back();
                //Think more
                if( (e->beginService + e->serviceDuration) < earliestStart){
                    earliestStart = e->beginService + e-> serviceDuration;
                    index = i;
                }
            }
        }
        assert(index != - 1);
        return cashiers.at(index);
    }
    
    int getExpectedCustomers(){
        int count = 0;
        for(int i = 0; i < cashiers.size(); i++){
//            if(!(cashiers.at(i)->isAvailable)){
//                count++;
//            }
            count += cashiers.at(i)->line.size();
        }
        return count;
    }
    
};
#endif /* Supermarket_hpp */
