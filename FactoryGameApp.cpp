/**
 * @file FactoryGameApp.cpp
 * @author Tyler Stefan
 */

#include "pch.h"

#include "FactoryGameApp.h"
#include "MainFrame.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

/**
 * Initialize the application.
 * @return
 */
bool FactoryGameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Do not remove this line...
    wxSetWorkingDirectory(L"..");

    // Get pointer to XML resource system
    auto xmlResource = wxXmlResource::Get();

    // Initialize XRC handlers
    xmlResource->InitAllHandlers();

    // Load all XRC resources from the program resources
    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    if (!wxXmlResource::Get()->LoadAllFiles(standardPaths.GetResourcesDir() + "/xrc"))
    {
        return false;
    }

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
