/**
 * @file Bucket.cpp
 * @author Tyler Stefan
 */

#include "pch.h"

#include "Bucket.h"

#include "FactoryGame.h"

/// Image for nut bucket
const std::wstring NutBucketImage = L"nut_bucket.png";

/// Image for the bolt bucket
const std::wstring BoltBucketImage = L"bolt_bucket.png";

/// Image for the cog bucket
const std::wstring CogBucketImage = L"cog_bucket.png";

/// Image for the battery bucket
const std::wstring BatteryBucketImage = L"battery_bucket.png";


/**
 * Constructor
 * @param game game this item is in
 */
Bucket::Bucket(FactoryGame* game) : Item(game)
{
    SetType(PartType::Nuts);
    SetPosition(wxPoint(100, 600));
}

// void Bucket::Draw(std::shared_ptr<wxGraphicsContext> gc)
// {
// }

/**
 * set bucket type
 * @param type type given
 */
void Bucket::SetType(PartType type)
{
    mType = type;
    switch (mType)
    {
        case PartType::Bolts:
            SetImage(BoltBucketImage);
            break;
        case PartType::Nuts:
            SetImage(NutBucketImage);
            break;
        case PartType::Cogs:
            SetImage(CogBucketImage);
            break;
        case PartType::Batteries:
            SetImage(BatteryBucketImage);
            break;
        default:
            break;
    }
}
