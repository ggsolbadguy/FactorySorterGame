/**
 * @file Part.h
 * @author Tyler Stefan
 *
 *  a class for the factory parts
 */
 
#ifndef PART_H
#define PART_H
#include <complex.h>
#include <random>

#include "Bucket.h"
#include "Item.h"
#include "PartType.h"


/**
 * a class for the factory parts
 */
class Part : public Item {

public:
    /// enum class for the type of part
private:
    /// the part type
    PartType mType;
    /// movement speed of part
    double mSpeed = 0.0;
    /// bool for if the object is falling
    bool mFalling = false;
    /// y velocity of this part
    int mVelocityY = 0;
    /// store the position of the end of the conveyor belt
    int mConveyorBeltEndX = 0;




public:
    Part() = delete;

    Part(FactoryGame* game, double speed);
    void SetType(PartType type);
    PartType GetRandomPartType(std::mt19937& rng);
    /**
     * get the part type of this part
     * @return mType
     */
    PartType GetType() { return mType; }
    void Update(double elapsed) override;
    bool HitTest(std::shared_ptr<Bucket> bucket);
    bool MatchesBucket(std::shared_ptr<Bucket> bucket);

    ~Part() { }
};



#endif //PART_H
