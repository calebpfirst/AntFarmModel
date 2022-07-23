//
//  antBase.hpp
//  AntFarmModel
//
//  Created by Caleb Price on 6/21/22.
//

#ifndef antBase_hpp
#define antBase_hpp

#include <stdio.h>
#include <cstring>
#include <vector>
#include <stdlib.h>

static int ANT_ID_CODE = 1;

enum class ANT_INVENTORY : int {
    EMPTY = 0,
    SUGAR_WATER = 1,
    ANT_HEAD = 2,
    ANT_TORSO = 3,
    ANT = 4,
    SAND = 5,
    BREADCRUMB = 6
};

enum class ANT_ACTIONS : int {
    DO_GET_FOOD = 0,
    DO_EAT= 1,
    DO_WORK = 2,
    DO_SLEEP = 3,
    DO_DEFENSE = 4,
    DO_ATTACK = 5,
    DO_SPAWN = 6,
    DO_PROTECT = 7,
    DO_SCAVENGE_FOOD = 8,
    //DO_DIG = 8,
    //DO_BRIDGE = 9,
    IS_WAITING = 100,
    IS_DEAD = 101
};

typedef ANT_INVENTORY ITEM_ID;

struct antInventoryItem
{
public:
    bool operator==(const antInventoryItem& right)
    {
        
        return ((right.item == this->item) &&
                (right.weight == this->weight));
    }
    void operator=(const antInventoryItem& right)
    {
        this->item = right.item;
        this->weight = right.weight;
    }
    ANT_INVENTORY item;
    int weight;
};

struct antSensors
{
    int leftTile, rightTile, upTile, downTile;
    int leftUpTile, rightUpTile, leftDownTile, rightDownTile;
    int tileValue;
};

class antBase
{
public:
    // functions
    /* ctor */
    antBase();
    /* cpy ctor */
    antBase(const antBase& cpy);
    /* dtor */
    ~antBase();
    // functions
    inline std::vector<antInventoryItem> getItems() const;
    inline int getHitPoints();
    inline bool getIsDead();
    inline float getHungerLevel();
    inline float getExhaustionLevel();
    inline ITEM_ID getItemID();
    void decideAction();
    void performAction();
    int getCrumbID();
protected:
    // todo: need to re-work
    int pinch();
    // todo: need to re-work
    bool takeDamage(int);
    bool pickUp(const antInventoryItem);
    // todo: needs to re-work
    bool eat(const antInventoryItem);
    bool drop(const antInventoryItem);
    bool drop(int);
    bool move(const antSensors);
    void sleep();
    // functions
    inline bool inventoryIsFull ();
    // variables
    antSensors sensors;
    int invCap;
    int strength, hitpoints, maxHitpoints;
    int carryWeightGrams, carryWeightGramMax;
    int antID;
    float hunger, exhaustion, exhaustionIncrements;
    ANT_ACTIONS currentAction;
    ITEM_ID itemID;
    std::vector<antInventoryItem> inventory;
};

float antBase::getExhaustionLevel()
{
    
    return this->exhaustion;
}

float antBase::getHungerLevel()
{
    
    return this->hunger;
}

int antBase::getCrumbID()
{
    
    return this->antID;
}

ITEM_ID antBase::getItemID()
{
    
    return this->itemID;
}

std::vector<antInventoryItem> antBase::getItems() const
{
    
    return this->inventory;
}

bool antBase::getIsDead()
{
    
    return this->hitpoints <= 0;
}

int antBase::getHitPoints()
{
    
    return this->hitpoints;
}

bool antBase::inventoryIsFull()
{
    
    return this->carryWeightGrams >= this->carryWeightGramMax;
}


#endif /* antBase_hpp */
