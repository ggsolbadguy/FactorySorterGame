/**
 * @file FactoryGame.cpp
 * @author Tyler Stefan
 */

#include "pch.h"
#include "FactoryGame.h"
#include "Bucket.h"
#include <random>

#include "Part.h"

/**
 * Constructor
 */
FactoryGame::FactoryGame()
{
    std::random_device rd;
    mRandom.seed(rd());
}

/// relative to the resources directory.
const std::wstring ImagesDirectory = L"/images";
/// relative to the resources directory.
const std::wstring LevelsDirectory = L"/levels";

/**
 * set the images directory of the game
 * @param dir directory to set
 */
void FactoryGame::SetImagesDirectory(const std::wstring &dir)
{
    mImagesDirectory = dir + ImagesDirectory;
}
/**
 * set the levels directory of the game
 * @param dir directory to set
 */
void FactoryGame::SetLevelsDirectory(const std::wstring &dir)
{
    mLevelsDirectory = dir + LevelsDirectory;
}

/**
 *  Handle updates for animation
 * @param elapsed The time since the last update
 */
void FactoryGame::Update(double elapsed)
{
    mTimeSinceSpawned += elapsed;

    if (mTimeSinceSpawned >= mPartGenerationInterval)
    {
        mTimeSinceSpawned = 0;
        CreatePart();
    }

    for (auto item : mItems)
    {
        item->Update(elapsed);
    }

    mItems.erase(std::remove_if(mItems.begin(), mItems.end(),
           [](const std::shared_ptr<Item>& item) {
               return item->IsDelete();
           }),
       mItems.end());
}

/** Draw the game
  * @param gc The GDI+ graphics context to draw on
  */
void FactoryGame::OnDraw(std::shared_ptr<wxGraphicsContext> gc)
{
    for (auto item : mItems)
    {
        item->Draw(gc);
    }
    mOutputMachine->Draw(gc);

}

/**  Load the level from a XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* @param filename The filename of the file to load the level from.
*/
void FactoryGame::Load(const wxString &filename)
{
    wxString levelfile = mLevelsDirectory + L"/" + filename;
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(levelfile))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    // Once we know it is open, clear the existing data
    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    if (root->GetName() == "level")
    {
        root->GetAttribute("interval").ToDouble(&mPartGenerationInterval);
        root->GetAttribute("speed").ToDouble(&mPartSpeed);
    }
    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    wxXmlNode* itemsParentNode = nullptr;

    auto node = root->GetChildren();
    for( ; node; node=node->GetNext())
    {
        if (node->GetName() == L"items")
        {
            itemsParentNode = node;
        }
    }

    //iterate through items
    auto item = itemsParentNode->GetChildren();
    for ( ; item; item=item->GetNext())
    {
        auto name = item->GetName();
        XmlItem(item);
    }
}

/**
 * load in xml item node
 * @param node xml item node
 */
void FactoryGame::XmlItem(wxXmlNode* node)
{
    std::shared_ptr<Item> item;

    auto name = node->GetName();


    if (name == L"bucket")
    {
        mBucket = std::make_shared<Bucket>(this);
        item = mBucket;
    }

    if (name == L"output_machine")
    {
        mOutputMachine = std::make_shared<OutputMachine>(this);
        mOutputMachine->SetPosition(wxPoint(730.0, 368.0));
    }
    if (name == L"background")
    {
        item = std::make_shared<Item>(this);

        item->SetImage(node->GetAttribute("file").ToStdWstring());
    }
    if (item != nullptr)
    {
        //item->XmlLoad(node);
        mItems.push_back(item);
    }

}
/**
*  Clear the item data.
*
* Deletes all known items in the game.
*/
void FactoryGame::Clear()
{
    mItems.clear();
}

/**
 * handle the input fr the game
 * @param event keyboard input
 */
void FactoryGame::HandleInput(wxKeyEvent& event)
{
    if (IsInstructions() && event.GetKeyCode() == WXK_RETURN)
    {
        mGameState = GameState::Playing;
    }
    if (IsGameWon() && event.GetKeyCode() == WXK_RETURN )
    {
        if (mCurrentLevel < 3)
            mCurrentLevel++;
        else
            mCurrentLevel = 1;
        Load(L"level" + std::to_wstring(mCurrentLevel) + L".xml");
        mGameState = GameState::Instructions;
    }
    else if (IsGameOver() && event.GetKeyCode() == 'R')
    {
        Load(L"level" + std::to_wstring(mCurrentLevel) + L".xml");
        mGameState = GameState::Playing;
    }
    else if (event.GetKeyCode() == WXK_LEFT)
    {
        mBucket->SetType(PartType::Nuts);
    }
    else if (event.GetKeyCode() == WXK_RIGHT)
    {
        mBucket->SetType(PartType::Bolts);
    }
    else if (event.GetKeyCode() == WXK_UP && mCurrentLevel >= 2)
    {
        mBucket->SetType(PartType::Cogs);
    }
    else if (event.GetKeyCode() == WXK_DOWN && mCurrentLevel >= 3)
    {
        mBucket->SetType(PartType::Batteries);
    }

}

/**
 * Create a Part
 */
void FactoryGame::CreatePart()
{
    auto part = mOutputMachine->CreatePart(this, mPartSpeed);
    mItems.push_back(part);
}

