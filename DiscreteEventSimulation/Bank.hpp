//
//  Bank.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Bank_hpp
#define Bank_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <functional>
#include "Event.hpp"
#include "Compare.hpp"
#include "Establishment.hpp"
//#include <algorithm>

class Bank : public Establishment {
public:
    std::deque<Event*> serviceQ;
    Bank(std::priority_queue<Event *, std::vector<Event *>, Compare > &events)
    : Establishment(events){
        serviceQ = std::deque<Event*> ();
    };
    
    void nextEvent() override {
        Event *current = eventQ.top();
        //assert(current -> serviceDuration != 0);
        //std::cout << current->type <<": " <<current-> arrivalTime << std::endl;
        if(current->type == "Arrive"){
            if(currentCustomers > 6){
                assert(!availableCashier());
            }else{
                int cashiersInUse = 6 - countAvailableCashiers() ;
                assert( cashiersInUse == currentCustomers);
            }
            currentCustomers += 1;
            //update the clock
            currentTime = current->arrivalTime;
            //if there is a line...
            if(availableCashier() == nullptr){
                eventQ.pop();
                current->type = "Queuing";
                current -> queueLen = serviceQ.size() + 1;
                serviceQ.push_back(current);
                //get in line
            }else{
                assert(serviceQ.size() == 0);
                current->elapsedWaitTime = 0;
                current -> queueLen = 0;
                current-> beginService = currentTime;
                current->type = "Servicing";
                current->typeRank = 1;
                nextEvent();// restart
                return;
            }
            //add BegService event
        }else if(current->type == "Servicing"){

            //if I don't already have a cashier, find one that is avaialable
            Cashier *cashier = availableCashier();
            if(cashier == nullptr){
                std::cout << "Error: trying to begin service w/o cashier" << std::endl;
                exit(1);
            }
            calcWaitTime(current);//calc wait ;
            assert(current ->arrivalTime <= current->beginService );
            assert(current ->endService  == 0);
            cashier->helpCustomer(current);
            current -> cashier = cashier;

            eventQ.pop();
            calcEndServiceTime(current);
            current -> type = "Finishing";
            current->typeRank =2;
            eventQ.push(current);
        }
        else if (current->type == "Finishing"){
            currentTime = current -> endService;
            current->calcTotalServiceTime();
            processedCustomers.push_back(*current);
            eventQ.pop();

            current->cashier-> finishCustomer();
            currentCustomers -= 1;
            if(serviceQ.empty()){
                return;
            }
            serviceQ.front()-> type = "Servicing";
            current->typeRank = 1;
            eventQ.push(serviceQ.front());
            serviceQ.pop_front();
        }else{
            std::cout << "Error: undeterminable type";
            exit(1);
        }
    }
    
    
    
    
    
    
    void openForBusiness(long maxDuration){
        int count = 0;
        while(!(eventQ.empty())){
            nextEvent();
            count++;
            if (currentTime > maxDuration){
                break;
            }
        }
    }
    
};


#endif /* Bank_hpp */
