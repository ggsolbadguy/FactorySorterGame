/**
 * @file Bucket.h
 * @author Tyler Stefan
 *
 * Bucket where we will be sorting items.
 */
 
#ifndef BUCKET_H
#define BUCKET_H
#include "Item.h"
#include "PartType.h"


/**
 * Bucket where we will be sorting items.
 */
class Bucket : public Item {

private:
    /// bucket type
    PartType mType = PartType::Nuts;
public:
    Bucket() = delete;
    virtual ~Bucket() { }
    Bucket(FactoryGame* game);

   //void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void SetType(PartType type);

    /**
     * Get the type of the bucket
     * @return mType
     */
    PartType GetType() { return mType; }



};



#endif //BUCKET_H
