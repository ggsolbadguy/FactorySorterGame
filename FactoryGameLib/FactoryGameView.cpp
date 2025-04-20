/**
 * @file FactoryGameView.cpp
 * @author Tyler Stefan
 */
#include "pch.h"
#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include "FactoryGameView.h"


using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;
/// How long each level lasts
const int LevelDuration = 30;

/**
 * Constructor
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
FactoryGameView::FactoryGameView(wxFrame* parent) : wxWindow(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    mResourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    mFactoryGame.SetImagesDirectory(mResourcesDir);
    mFactoryGame.SetLevelsDirectory(mResourcesDir);

    Bind(wxEVT_PAINT, &FactoryGameView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &FactoryGameView::OnKeyDown, this);
    Bind(wxEVT_TIMER, &FactoryGameView::OnTimer, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &FactoryGameView::OnLevel1, this, XRCID("Level1"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &FactoryGameView::OnLevel2, this, XRCID("Level2"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &FactoryGameView::OnLevel3, this, XRCID("Level3"));

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

    mFactoryGame.Load("level1.xml");
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FactoryGameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    // update game first
    if (mFactoryGame.IsPlaying())
        mFactoryGame.Update(elapsed);

    //draw all objects
    mFactoryGame.OnDraw(graphics);

    //draw timer
    if (mFactoryGame.IsPlaying())
    {

        wxFont font(wxSize(30, 60),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
        dc.SetFont(font);

        dc.SetTextForeground(wxColour(0, 0, 0));
        // how many seconds in a level
        int totalTime = LevelDuration;
        int totalSeconds = mStopWatch.Time() / 1000;
        int minutes = (totalTime - totalSeconds) / 60;
        int seconds = (totalTime - totalSeconds) % 60;
        wxString time = wxString::Format("%01d:%02d",minutes, seconds);
        dc.DrawText(time,  // Text to draw
                10,     // x coordinate for the left size of the text
                10);    // y coordinate for the top of the text

        if (minutes <= 0 && seconds <= 0)
        {
            mFactoryGame.SetGameWon();
        }
    }

    /// display game over message
    if (mFactoryGame.IsGameOver())
    {
        mStopWatch.Pause();
        wxImage image(mResourcesDir + L"/images/youlosebox.png", wxBITMAP_TYPE_PNG);
        wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(image);
        double x = GetSize().GetWidth() / 2 - image.GetWidth() / 2;
        double y = GetSize().GetHeight() / 2 - image.GetHeight() / 2;
        graphics->DrawBitmap(bitmap, x, y, image.GetWidth(), image.GetHeight());
    }
    /// display victory message
    if (mFactoryGame.IsGameWon())
    {
        mStopWatch.Pause();
        wxImage image;
        if (mFactoryGame.GetLevelNumber() < 3)
            image = wxImage(mResourcesDir + L"/images/youwinbox.png", wxBITMAP_TYPE_PNG);
        else
            image = wxImage(mResourcesDir + L"/images/youwinboxalt.png", wxBITMAP_TYPE_PNG);
        wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(image);
        double x = GetSize().GetWidth() / 2 - image.GetWidth() / 2;
        double y = GetSize().GetHeight() / 2 - image.GetHeight() / 2;
        graphics->DrawBitmap(bitmap, x, y, image.GetWidth(), image.GetHeight());
    }
    if (mFactoryGame.IsInstructions())
    {
        mStopWatch.Pause();
        wxImage image;
        if (mFactoryGame.GetLevelNumber() == 1)
            image = wxImage(mResourcesDir + L"/images/instructionsbox1.png", wxBITMAP_TYPE_PNG);
        else if (mFactoryGame.GetLevelNumber() == 2)
            image = wxImage(mResourcesDir + L"/images/instructionsbox2.png", wxBITMAP_TYPE_PNG);
        else
            image = wxImage(mResourcesDir + L"/images/instructionsbox3.png", wxBITMAP_TYPE_PNG);

        wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(image);
        double x = GetSize().GetWidth() / 2 - image.GetWidth() / 2;
        double y = GetSize().GetHeight() / 2 - image.GetHeight() / 2;
        graphics->DrawBitmap(bitmap, x, y, image.GetWidth(), image.GetHeight());
    }
}

/**
 * Handle a keyboard button down event
 * @param event The keyboard key event
 */
void FactoryGameView::OnKeyDown(wxKeyEvent& event)
{
    if (mFactoryGame.IsInstructions() && event.GetKeyCode() == WXK_RETURN)
    {
        mTime = 0;
        mStopWatch.Start();
    }
    else if (mFactoryGame.IsGameOver() && event.GetKeyCode() == 'R')
    {
        mTime = 0;
        mStopWatch.Start();
    }
    mFactoryGame.HandleInput(event);
}

/**
 * Handle timer events
 * @param event timer event
 */
void FactoryGameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}
/**
 * Handle the level 1 menu option event
 * @param event The command  event
 */
void FactoryGameView::OnLevel1(wxCommandEvent& event)
{
    ResetGame(L"level1.xml");
    mFactoryGame.SetLevelNumber(1);
}
/**
 * Handle the level 2 menu option event
 * @param event The command  event
 */
void FactoryGameView::OnLevel2(wxCommandEvent& event)
{
    ResetGame(L"level2.xml");
    mFactoryGame.SetLevelNumber(2);
}
/**
 * Handle the level 3 menu option event
 * @param event The command  event
 */
void FactoryGameView::OnLevel3(wxCommandEvent& event)
{
    ResetGame(L"level3.xml");
    mFactoryGame.SetLevelNumber(3);

}
/**
 * reset the game state and timer and load a new file
 * @param file file to load
 */
void FactoryGameView::ResetGame(std::wstring file)
{
    mTime = 0;
    mStopWatch.Start();
    mFactoryGame.Load(file);
    mFactoryGame.SetGameInstructions();
}
