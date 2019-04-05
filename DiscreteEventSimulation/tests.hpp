//
//  tests.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 3/30/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp
#include <vector>
#include <queue>
#include <stdio.h>
#include "Event.hpp"
#include "Bank.hpp"
#include "Compare.hpp"
template<typename T>void createTestEvents (T& events);
void testBankInit();
void testArrivePartWayThroughService();
void testSupermarket();
void testGapSupermarket();
//template<typename T>void testPriorityQ (T& events);
#endif /* tests_hpp */
