/**
 * @file Item.h
 * @author Tyler Stefan
 *
 * Base item class for everything on screen
 */
 
#ifndef ITEM_H
#define ITEM_H

class FactoryGame;

/**
 * Base item class for everything on screen
 */
class Item {
private:
    /// the game this item is in
    FactoryGame* mFactoryGame;

    /// The image for this item
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap for this item
    std::unique_ptr<wxBitmap> mItemBitmap;
    /// file name for the item image
    std::wstring mFile;

    int   mX = 0;     ///< X location for the center of the item
    int   mY = 0;     ///< Y location for the center of the item

    /// represents whether the item should be deleted or not.
    bool mDelete = false;

public:
    /// delete default constructor
    Item() = delete;

    Item(FactoryGame* game);

    virtual ~Item() { }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);
    void SetImage(const std::wstring& file);
    /**
     * get the game of this item
     * @return mFactoryGame
     */
    FactoryGame* GetGame() { return mFactoryGame; }

    ///  Handle updates for animation
    /// @param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    void SetPosition(wxPoint pos);

    /**
     * set the x position of this item
     * @param x x pos to set
     */
    void SetX(int x) { mX = x; }
    /**
    * get the x position of this item
    * @return x pos
    */
    int GetX() const { return mX; }

    /**
     * set the y position of this item
     * @param y x pos to set
     */
    void SetY(int y) { mY = y; }
    /**
     * get the y position of this item
     * @return y pos
     */
    int GetY() const { return mY; }
    /**
     * get the width of the image of this item
     * @return image width
     */
    int GetImageWidth() const { return mItemImage->GetWidth(); }
    /**
     * get the height of the image of this item
     * @return image height
     */
    int GetImageHeight() const { return mItemImage->GetHeight(); }

    /**
     * set whether this item should be deleted
     * @param deleted bool to set
     */
    void SetDelete(bool deleted) { mDelete = deleted; }
    /**
     * returns bool representing if this item should be deleted
     * @return mDelete
     */
    bool IsDelete() const { return mDelete; }
};



#endif //ITEM_H
