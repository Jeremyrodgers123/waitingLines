//
//  main.cpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include "Event.hpp"
#include "Bank.hpp"
#include "Supermarket.hpp"
#include "tests.hpp"
#include <fstream>
template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        Event *e = q.top();
        q.pop();
        std::cout << "arrival: " << e->arrivalTime << " SD: " << e->serviceDuration << std::endl;
    }
}
template<typename T>void testPriorityQ (T& events){
    long previous = -1;
    for(int i = 0; i < events.size(); i++){
        long a = events.top()->arrivalTime;
        events.pop();
        assert(a >= previous);
        previous = a;
    }
}

template<typename T>void createEvents (T& events, long simDuration, long arrivalCount, long maxServiceDur){
    long arrival;
    long serviceDuration;
    for(int i = 0; i < arrivalCount; i++){
      arrival = 0 + rand() % simDuration;
      serviceDuration = 0 + rand() % maxServiceDur;
      events.push(new Event (arrival, serviceDuration, i));
    }
}


double calcNumberOfArrivals(double arrivalRate){
    //12 * 60
    double SimulationMinutes = 60 *12;
    //std::cout << "SimulationMinutes " << SimulationMinutes << std::endl;
    double arrivals = arrivalRate * SimulationMinutes;
     // std::cout << "arrivals " << arrivals << std::endl;
    return arrivals;
}
template<typename T>
void writeToFile(std::ofstream &os, std::string filename, T& processedEvents){
    os.open(filename);
      os << "id arrival begin end wait queue duration serviceTime order" << std::endl;
    for(int i = 0 ; i < processedEvents.size(); i++){
        os << processedEvents.at(i).id << " " <<
             processedEvents.at(i).arrivalTime << " " <<
             processedEvents.at(i).beginService << " " <<
             processedEvents.at(i).endService << " " <<
             processedEvents.at(i).elapsedWaitTime << " " <<
             processedEvents.at(i).queueLen << " " <<
             processedEvents.at(i).serviceDuration << " " <<
            processedEvents.at(i).totalServiceTime  << " " <<
             i <<
        std::endl;
    }
}

int main(int argc, const char * argv[]) {
    double arrivalRate = atof(argv[1]); //minutes
    double maxServiceDur = atof(argv[2]);
    maxServiceDur *= 60; //convert to seconds
    unsigned int randSeed = atoi(argv[3]);
    srand(randSeed);
    int simulationDuration = 12 * 60 * 60;
    //std::cout << "sim secs " <<simulationDuration<< std::endl;
    long arrivalCount = calcNumberOfArrivals(arrivalRate);
    auto bankEvents = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
    createEvents(bankEvents,simulationDuration, arrivalCount, maxServiceDur);
    Bank bank = Bank(bankEvents);
    //testPriorityQ(bank.eventQ);
    bank.openForBusiness(simulationDuration);
    //std::cout << "bank service times in minutes: " << std::endl;
    //bank.getStats();
    //bank.get90PerStats();
    //std::cout << std::endl;
//    std::ofstream bankfile;
//    bank.sortProcessedCustomers();
//    writeToFile(bankfile, "bank.txt", bank.processedCustomers);
  
    
    srand(randSeed);
    auto supermarketEvents = std::priority_queue<Event *, std::vector<Event *>, Compare> ();
    createEvents(supermarketEvents, simulationDuration, arrivalCount, maxServiceDur);
    //print_queue(supermarketEvents);
    Supermarket supermarket = Supermarket(supermarketEvents);
    supermarket.openForBusiness(simulationDuration);
    //std::cout << "supermarket service times in minutes: " << std::endl;
    //supermarket.getStats();
    supermarket.get90PerStats();
        std::ofstream supermarketfile;
         supermarket.sortProcessedCustomers();
        writeToFile(supermarketfile, "supermarket.txt", supermarket.processedCustomers);

    return 0;
}
