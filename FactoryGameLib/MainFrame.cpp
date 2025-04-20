/**
 * @file MainFrame.cpp
 * @author Tyler Stefan
 */
#include "pch.h"

#include "MainFrame.h"

#include <wx/xrc/xmlres.h>

#include "FactoryGameView.h"


/**
 * Constructor
 */
MainFrame::MainFrame()
{

}


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

#ifdef WIN32
    // This sets the frame icon on Windows systems
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    mFactoryGameView = new FactoryGameView(this);


}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu event
 */
void MainFrame::OnAbout(wxCommandEvent&event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();\
}


