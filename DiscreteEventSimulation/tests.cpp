//
//  tests.cpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "tests.hpp"
#include "Establishment.hpp"
#include "Supermarket.hpp"
template<typename T>void createTestEvents (T& events){
    events.push(new Event(0, 5, 1)); //1
    events.push( new Event(0, 1, 2));
    events.push( new Event(0, 3, 3));
    events.push( new Event(0, 7, 4));
    events.push( new Event(0, 3, 5));
    events.push( new Event(0, 4, 6));
    events.push( new Event(0, 4, 7));
    events.push( new Event(0, 8, 8));
    events.push( new Event(0, 1, 9));
    events.push( new Event(0, 3, 10));
    events.push( new Event(0, 5, 11));
    events.push( new Event(0, 2, 12));
    events.push( new Event(0, 2, 13));
    events.push( new Event(0, 3, 14));
    events.push( new Event(2, 8, 15));
    events.push( new Event(2, 5, 16));
}
void testBankInit(){
     auto events = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
    createTestEvents(events);
    Bank bank = Bank(events);
    bank.openForBusiness(1000);
    for(int i = 0; i < bank.processedCustomers.size(); i++){
        std::cout << "\n";
        std::cout << "ID: " << bank.processedCustomers.at(i).id << std::endl;
        std::cout << "Arrived at: " << bank.processedCustomers.at(i).arrivalTime << std::endl;
        std::cout << "Begin Service: " << bank.processedCustomers.at(i).beginService << std::endl;
        std::cout << "Duration: " << bank.processedCustomers.at(i).serviceDuration << std::endl;
        std::cout << "End Service: " << bank.processedCustomers.at(i).endService << std::endl;
        std::cout << "Wait Time: " << bank.processedCustomers.at(i).elapsedWaitTime << std::endl;
        std::cout << "\n";
    }
}


//template<typename T>void testPriorityQ (T& events){
//    long previous = -1;
//    for(int i = 0; i < events.size(); i++){
//        long a = events.front().arrivalTime;
//        assert(a < previous);
//        previous = a;
//    }
//}

void testArrivePartWayThroughService(){
    auto events = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
   
    events.push( new Event(4, 2, 1)); //1
    events.push( new Event(0, 5, 2));
    events.push( new Event(0, 5, 3));
    events.push( new Event(0, 5, 4));
    events.push( new Event(0, 5, 5));
    events.push( new Event(0, 5, 6));
    
    events.push( new Event(0, 5, 7));
    events.push( new Event(4, 2, 8));
    events.push( new Event(4, 2, 9));
    Bank bank = Bank(events);
    bank.openForBusiness(1000);
    bank.sortProcessedCustomers();
    bank.printWaitTimes();
    bank.print_stats();
    assert(bank.find(1)-> elapsedWaitTime == 1);
    assert(bank.find(2)-> elapsedWaitTime == 0);
    assert(bank.find(8)-> elapsedWaitTime == 1);
    assert(bank.find(9)-> elapsedWaitTime == 1);
}

void testSupermarket(){
    auto events = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
    
    events.push( new Event(0, 2, 1)); //1
    events.push( new Event(0, 3, 2));
    events.push( new Event(0, 4, 3));
    events.push( new Event(0, 5, 4));
    events.push( new Event(0, 6, 5));
    events.push( new Event(0, 7, 6));
    
    events.push( new Event(1, 7, 7));
    events.push( new Event(1, 6, 8));
    events.push( new Event(1, 5, 9));
    events.push( new Event(1, 4, 10));
    events.push( new Event(1, 3, 11));
    events.push( new Event(1, 2, 12));
    
    events.push( new Event(2, 2, 13));
    events.push( new Event(2, 3, 14));
    events.push( new Event(2, 8, 15));
    events.push( new Event(2, 5, 16));
    Supermarket supermarket = Supermarket(events);
    supermarket.openForBusiness(1000);
    supermarket.sortProcessedCustomers();
    supermarket.printWaitTimes();
    supermarket.print_stats();
    
    assert(supermarket.find(2)-> elapsedWaitTime == 0);
    assert(supermarket.find(8)-> elapsedWaitTime == 2);
    assert(supermarket.find(13)-> elapsedWaitTime == 7);
}

void testGapSupermarket(){
    auto events = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
    
    events.push( new Event(0, 2, 1)); //1
    events.push( new Event(0, 3, 2));
    events.push( new Event(0, 4, 3));
    events.push( new Event(0, 5, 4));
    events.push( new Event(0, 6, 5));
    events.push( new Event(0, 7, 6));
    
    events.push( new Event(15, 7, 7));
   
    Supermarket supermarket = Supermarket(events);
    supermarket.openForBusiness(1000);
    supermarket.sortProcessedCustomers();
    supermarket.printWaitTimes();
    supermarket.print_stats();
    
    assert(supermarket.find(7)-> elapsedWaitTime == 0);
}


