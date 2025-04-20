/**
 * @file Part.cpp
 * @author Tyler Stefan
 */

#include "pch.h"
#include "Part.h"
#include <random>

#include "FactoryGame.h"

/// Image for nut bucket
const std::wstring NutImage = L"nut.png";

/// Image for the bolt bucket
const std::wstring BoltImage = L"bolt.png";

/// Image for the cog bucket
const std::wstring CogImage = L"cog.png";

/// Image for the cog bucket
const std::wstring BatteryImage = L"battery.png";

/// gravity constant for falling parts
const double Gravity = 980;

/**
 * constructor
 * @param game game this part is a part of
 * @param speed movement speed of part
 */
Part::Part(FactoryGame* game, double speed) : mSpeed(speed), Item(game)
{
    SetType(GetRandomPartType(game->GetRandom()));
    mConveyorBeltEndX = game->GetOutputMachine()->GetConveyorBeltEndX();
}

/**
 * set a part type for this part
 * @param type type to set
 */
void Part::SetType(PartType type)
{
    mType = type;
    switch (type)
    {
    case PartType::Bolts:
        SetImage(BoltImage);
        break;
    case PartType::Nuts:
        SetImage(NutImage);
        break;
    case PartType::Cogs:
        SetImage(CogImage);
        break;
    case PartType::Batteries:
        SetImage(BatteryImage);
        break;
    }
}

/**
 * generate a random part type
 * @param rnd random engine
 * @return random part type
 */
PartType Part::GetRandomPartType(std::mt19937& rnd)
{
    std::uniform_int_distribution<int> distribution(0, GetGame()->GetLevelNumber());
    int value = distribution(rnd);

    switch (value)
    {
        case 0:
            return PartType::Bolts;
        case 1:
            return PartType::Nuts;
        case 2:
            return PartType::Cogs;
        case 3:
            return PartType::Batteries;
    }
}

/**
 * update the part object
 * @param elapsed time elapse
 */
void Part::Update(double elapsed)
{
    if (!mFalling && GetX() + GetImageWidth()/2 < mConveyorBeltEndX)
    {
        mFalling = true;
    }
    if (mFalling)
    {
        mVelocityY += Gravity * elapsed;
        SetY(GetY() + mVelocityY * elapsed);

        auto *game = GetGame();
        auto bucket = game->GetBucket();
        if (HitTest(bucket))
        {
            if (!MatchesBucket(bucket) && !game->IsGameOver())
            {
                game->SetGameOver();
            }
            SetDelete(true);
        }
    }
    SetX(GetX() - mSpeed * elapsed);
}

/**
 * Test to see if the part landed in the bucket
 * @param bucket bucket
 * @return true if part is in bucket, otherwise false
 */
bool Part::HitTest(std::shared_ptr<Bucket> bucket)
{
    auto partLeft = GetX();
    auto partRight = GetX() + GetImageWidth();
    auto partTop = GetY();
    auto partBottom = GetY() + GetImageHeight();

    auto bucketLeft = bucket->GetX();
    auto bucketRight = bucket->GetX() + bucket->GetImageWidth();
    auto bucketTop = bucket->GetY();
    auto bucketBottom = bucket->GetY() + bucket->GetImageHeight();

    bool overlapX = partRight >= bucketLeft && partLeft <= bucketRight;
    bool overlapY = partBottom >= bucketTop && partTop <= bucketBottom;

    return overlapX && overlapY;
}

/**
 * check if part type matches the bucket type
 * @param bucket current bucket
 * @return true if part and bucket match type
 */
bool Part::MatchesBucket(std::shared_ptr<Bucket> bucket)
{
    if (GetType() == bucket->GetType())
    {
        return true;
    }
    return false;
}

