//
//  antBase.cpp
//  AntFarmModel
//
//  Created by Caleb Price on 6/21/22.
//

#include "antBase.hpp"

antBase::antBase() :
sensors{0},
invCap(0),
strength(1),
exhaustionIncrements(0.1f),
exhaustion(0.0f),
maxHitpoints(5),
carryWeightGrams(0),
carryWeightGramMax(20),
inventory(),
itemID(ANT_INVENTORY::ANT),
currentAction(ANT_ACTIONS::IS_WAITING)
{
    this->hitpoints = this->maxHitpoints;
    this->antID = ANT_ID_CODE++;
}

antBase::antBase(const antBase& cpy)
{
    std::memcpy(&this->sensors, &cpy.sensors, sizeof(antSensors));
    this->invCap = cpy.invCap;
    this->inventory = cpy.inventory;
}

antBase::~antBase()
{
    --ANT_ID_CODE;
}

bool antBase::takeDamage(int damage)
{
    if (!this->getIsDead())
    {
        this->hitpoints -= damage;
        
        return true;
    }
    
    return false;
}

bool antBase::pickUp(const antInventoryItem item)
{
    if (this->carryWeightGrams + item.weight <= this->carryWeightGramMax)
    {
        this->inventory.push_back(item);
        this->carryWeightGrams += item.weight;
        
        return true;
    }
    
    return false;
}

bool antBase::drop(const antInventoryItem item)
{
    for (int i = 0; i < this->inventory.size(); ++i)
    {
        if (this->inventory[i] == item)
        {
            this->carryWeightGrams -= item.weight;
            this->inventory.erase(this->inventory.begin() + i);
            
            return true;
        }
    }
    
    return false;
}

bool antBase::drop(int itemIdx)
{
    if (itemIdx < this->inventory.size() - 1)
    {
        this->carryWeightGrams -= this->inventory[itemIdx].weight;
        this->inventory.erase(this->inventory.begin() + itemIdx);
        
        return true;
    }
    
    return false;
}

int antBase::pinch()
{
    if (this->sensors.tileValue == (int)ANT_INVENTORY::ANT)
    {
        
        return this->strength;
    }
    
    return 0;
}

bool antBase::move(const antSensors destTile)
{
    if ((destTile.tileValue == (int)ANT_INVENTORY::EMPTY) || (destTile.tileValue == (int)ANT_INVENTORY::SUGAR_WATER))
    {
        this->sensors = destTile;
        
        return true;
    }
    
    return false;
}

bool antBase::eat(const antInventoryItem item)
{
    if (item.item == ANT_INVENTORY::SUGAR_WATER)
    {
        // we can eat it
        if (this->hunger < 1.0f)
        {
            this->hunger = 1.0f;
        }
        else
        {
            this->hitpoints = this->maxHitpoints;
        }
        
        return false;
    }
    
    return false;
}

void antBase::performAction()
{
    // decide what the ant should do next based on priority...
    // are we hurt or hungry?
    if ((this->hitpoints < this->maxHitpoints) || (this->hunger < 1.0f))
    {
        switch (this->currentAction)
        {
            case ANT_ACTIONS::DO_GET_FOOD:
                this->currentAction = ANT_ACTIONS::DO_SCAVENGE_FOOD;
                for (antInventoryItem& item : this->inventory)
                {
                    if (item.item == ANT_INVENTORY::SUGAR_WATER)
                    {
                        this->currentAction = ANT_ACTIONS::DO_EAT;
                        break;
                    }
                }
                break;
            case ANT_ACTIONS::DO_EAT:
                for (antInventoryItem& item : this->inventory)
                {
                    if (item.item == ANT_INVENTORY::SUGAR_WATER)
                    {
                        this->currentAction = ANT_ACTIONS::IS_WAITING;
                        this->eat(item);
                        break;
                    }
                }
                break;
            case ANT_ACTIONS::DO_WORK:
                break;
            case ANT_ACTIONS::DO_SLEEP:
                break;
            case ANT_ACTIONS::DO_DEFENSE:
                break;
            case ANT_ACTIONS::DO_ATTACK:
                break;
            case ANT_ACTIONS::DO_SPAWN:
                break;
            case ANT_ACTIONS::DO_PROTECT:
                break;
            case ANT_ACTIONS::DO_SCAVENGE_FOOD:
                if (this->sensors.downTile == (int)ANT_INVENTORY::SUGAR_WATER)
                {
                    this->move(<#const antSensors destTile#>)
                }
                break;
            case ANT_ACTIONS::IS_WAITING:
            case ANT_ACTIONS::IS_DEAD:
                break;
            default:
                break;
        }
    }
    this->exhaustion-=exhaustionIncrements;
}

void antBase::sleep()
{
    if (this->exhaustion < 1.0f)
    {
        this->exhaustion = (this->exhaustion + this->exhaustionIncrements > 1.0f) ? 1.0f : this->exhaustion + this->exhaustionIncrements;
    }
}
