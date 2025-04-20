/**
 * @file OutputMachine.cpp
 * @author Tyler Stefan
 */

#include "pch.h"

#include "OutputMachine.h"

#include "Part.h"

/**
 * constructor
 * @param game game this output machine is in
 */
OutputMachine::OutputMachine(FactoryGame* game) : Item(game)
{
    SetImage(L"OutputMachine.png");
    mConveyorBelt = std::make_shared<Item>(game);
    mConveyorBelt->SetImage(L"ConveyorBelt1.png");
    mConveyorBelt->SetPosition(wxPoint(250.0, 568.0));
}

/**
 * Draw this output machine
 * @param gc graphics context
 */
void OutputMachine::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    Item::Draw(gc);
    mConveyorBelt->Draw(gc);
}

/**
 * get the global part spawn position
 * @return part spawn position
 */
wxPoint OutputMachine::GetPartSpawnPosition()
{
    return wxPoint(GetX(), GetY()) + mPartSpawnPoint;
}
/**
 * create a part
 * @param game game the part will be in
 * @param speed the movement speed of the part
 * @return the part created
 */
std::shared_ptr<Part> OutputMachine::CreatePart(FactoryGame* game, double speed)
{
    std::shared_ptr<Part> part = std::make_shared<Part>(game, speed);
    part->SetPosition(wxPoint(GetX(), GetY()) + mPartSpawnPoint);

    return part;
}
/**
 * get the left edge x position of the conveyer belt
 * @return conveyer belt edge x position
 */
int OutputMachine::GetConveyorBeltEndX()
{
    return mConveyorBelt->GetX();
}
