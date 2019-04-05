//
//  Establishment.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 4/1/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Establishment_hpp
#define Establishment_hpp

#include <stdio.h>
#include <queue>
#include "Event.hpp"
#include "Compare.hpp"
#include <iostream>
class Establishment{
public:
    std::priority_queue<Event *, std::vector<Event *>, Compare > eventQ;
    std::vector<Event> processedCustomers;
    std::vector<Cashier *> cashiers;
    long currentTime;
    int currentCustomers;
    Establishment(std::priority_queue<Event *, std::vector<Event *>, Compare > &events){
        eventQ = events;
        currentTime = 0;
        currentCustomers = 0;
        cashiers = std::vector<Cashier *>
        {new Cashier(), new Cashier(),new Cashier(),new Cashier(), new Cashier(), new Cashier()};
    }
    
    static bool compareEvents(Event e1, Event e2)
    {
        if(e1.elapsedWaitTime != e2.elapsedWaitTime){
            return (e1.elapsedWaitTime < e2.elapsedWaitTime);
        }
        
        return e1.id < e2.id;
        
    }
    
    static bool compareServiceTime(Event e1, Event e2)
    {
        if(e1.totalServiceTime != e2.totalServiceTime){
            return (e1.totalServiceTime < e2.totalServiceTime);
        }
        
        return e1.id < e2.id;
        
    }
    
    
    void sortProcessedCustomers(){
        std::sort(processedCustomers.begin(), processedCustomers.end(), this->compareServiceTime);
        
    }
    
    Cashier* availableCashier(){
        for(int i = 0; i < cashiers.size(); i++){
            if(cashiers.at(i)->isAvailable){
                return cashiers.at(i);
            }
        }
        return nullptr;
    };
    
    int countAvailableCashiers(){
        int count = 0;
        for(int i = 0; i < cashiers.size(); i++){
            if(cashiers.at(i)->isAvailable){
                count += 1;
            }
        }
        return count;
    }
    
    void calcWaitTime(Event *e){
        e->beginService = currentTime;
        //e->remainingServiceDuration = e->serviceDuration;
        e->elapsedWaitTime = e->beginService - e->arrivalTime;
        e->nextOccurance = e->beginService;
    }
    
    void calcEndServiceTime(Event *e){
        e->endService = e->beginService + e->serviceDuration;
        e->nextOccurance = e->endService;
    }
    
    template<typename T> void print_q(T q) {
        while(!q.empty()) {
            Event *e = q.top();
            q.pop();
            std::cout << "id: " << e-> id << e->type <<": " << e->nextOccurance << " SD: " << e->serviceDuration << std::endl;
        }
    }
    
    void print_stats(){
        for(int i = 0; i < processedCustomers.size(); i++){
            std::cout << "\n";
            std::cout << "ID: " << processedCustomers.at(i).id << std::endl;
            std::cout << "Arrived at: " << processedCustomers.at(i).arrivalTime << std::endl;
            std::cout << "Begin Service: " << processedCustomers.at(i).beginService << std::endl;
            std::cout << "Duration: " << processedCustomers.at(i).serviceDuration << std::endl;
            std::cout << "End Service: " << processedCustomers.at(i).endService << std::endl;
            std::cout << "Wait Time: " << processedCustomers.at(i).elapsedWaitTime << std::endl;
            std::cout << "\n";
        }
    }
    
    void printWaitTimes(){
        for(int i = 0; i < processedCustomers.size(); i++){
            std::cout << "ID: " << processedCustomers.at(i).id << ", " << "Wait Time: " << processedCustomers.at(i).elapsedWaitTime << std::endl;
        }
    }
    
    Event* find(int id){
        for(int i = 0; i < processedCustomers.size(); i++){
            if( processedCustomers.at(i).id == id){
                return &processedCustomers.at(i);
            }
        }
        return nullptr;
    }
    
    void getStats(){
        sortProcessedCustomers();
        long tenPerIndex = processedCustomers.size() * .10;
        long fiftyPerIndex = processedCustomers.size() * .50;
        long nintyPerIndex = processedCustomers.size() * .90;
        std::cout << " 10th %ile " << (processedCustomers[tenPerIndex].totalServiceTime / 60) << std::endl;
        std::cout << " 50th %ile " << (processedCustomers[fiftyPerIndex].totalServiceTime / 60) << std::endl;
        std::cout << " 90th %ile " << (processedCustomers[nintyPerIndex].totalServiceTime / 60) << std::endl;
    }
    
    void get90PerStats(){
        sortProcessedCustomers();
        long nintyPerIndex = processedCustomers.size() * .90;
        std::cout << (processedCustomers[nintyPerIndex].totalServiceTime / 60);
    }
    
};
#endif /* Establishment_hpp */
