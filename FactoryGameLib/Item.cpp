/**
 * @file Item.cpp
 * @author Tyler Stefan
 */

#include "pch.h"

#include "Item.h"

#include "FactoryGame.h"

/**
 * Constructor
 * @param game game this item is in
 */
Item::Item(FactoryGame* game) : mFactoryGame(game)
{

}

/**
 * Draw this item
 * @param gc graphics context
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{

    double wid = mItemBitmap->GetWidth();
    double height = mItemBitmap->GetHeight();


    gc->DrawBitmap(*mItemBitmap, mX, mY, wid, height);
}
/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Item::SetImage(const std::wstring &file)
{
    if (!file.empty())
    {
        std::wstring filename = mFactoryGame->GetImagesDirectory() + L"/" + file;
        mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);

        double scale = mFactoryGame->GetImageScale();
        int wid = mItemImage->GetWidth() * scale;
        int height = mItemImage->GetHeight() * scale;

        mItemImage->Rescale(wid, height, wxIMAGE_QUALITY_NEAREST);

        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }
    else
    {
        mItemImage.release();
        mItemBitmap.release();
    }

    mFile = file;
}

/**
 * set location of this item
 * @param pos pos
 */
void Item::SetPosition(wxPoint pos)
{
    mX = pos.x;
    mY = pos.y;
}
