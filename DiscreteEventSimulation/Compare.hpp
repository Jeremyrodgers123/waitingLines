//
//  Compare.hpp
//  DiscreteEventSimulation
//
//  Created by Jeremy Rodgers on 4/1/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Compare_hpp
#define Compare_hpp

#include <stdio.h>
#include "Event.hpp"
class Compare
{
public:
    bool operator() (const Event* a, const Event* b){
        
        if(a->nextOccurance != b-> nextOccurance){
            return a->nextOccurance > b->nextOccurance;
        }else{
            if(a->typeRank != b->typeRank){
                  return a->typeRank < b->typeRank;
            }
            return a-> id > b->id;
        }
        return false;
    }
};

#endif /* Compare_hpp */
