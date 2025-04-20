/**
 * @file FactoryGameView.h
 * @author Tyler Stefan
 *
 * View class for the factory game
 *
 */

#ifndef FACTORYGAMEVIEW_H
#define FACTORYGAMEVIEW_H

#include "FactoryGame.h"
/**
 * View class for the factory game
 */
class FactoryGameView final : public wxWindow {
private:
    /// The factory game object
    FactoryGame mFactoryGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// resources directory
    std::wstring mResourcesDir;

    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);
    void ResetGame(std::wstring file);
    void OnPaint(wxPaintEvent& event);

public:
    FactoryGameView(wxFrame* parent);
};

#endif //FACTORYGAMEVIEW_H
