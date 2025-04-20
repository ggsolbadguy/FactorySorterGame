/**
 * @file OutputMachine.h
 * @author Tyler Stefan
 *
 * a class for the output machine that spits out parts
 */
 
#ifndef OUTPUTMACHINE_H
#define OUTPUTMACHINE_H
#include "Item.h"

class Part;

/**
 * a class for the output machine that spits out parts
 */
class OutputMachine : public Item {
private:
    /// part spawn position
    wxPoint mPartSpawnPoint = wxPoint(0, 160);
    /// conveyer belt object
    std::shared_ptr<Item> mConveyorBelt;
public:
    /// delete default constuctor
    OutputMachine() = delete;
    OutputMachine(FactoryGame* game);
    wxPoint GetPartSpawnPosition();
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    std::shared_ptr<Part> CreatePart(FactoryGame* game, double speed);
    int GetConveyorBeltEndX();
};



#endif //OUTPUTMACHINE_H
