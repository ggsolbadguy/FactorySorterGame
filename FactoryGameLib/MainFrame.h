/**
 * @file MainFrame.h
 * @author Tyler Stefan
 *
 * The top-level (main) frame of the application
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_


class FactoryGameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our edit window
    FactoryGameView *mFactoryGameView = nullptr;

public:
    MainFrame();
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif //_MAINFRAME_H_
