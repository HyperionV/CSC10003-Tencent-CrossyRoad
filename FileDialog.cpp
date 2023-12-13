#include "FileDialog.h"
#include <sstream>


FileDialog::FileDialog(HWND hwnd) : hwnd_(hwnd) {}

std::string FileDialog::ShowOpenFileDialog() {
    // Save the current working directory
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);

    // Initialize the buffer
    _tcscpy_s(szFileName_, _T(""));

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd_;

    // Update the filter to include "Crossy Road Save Files"
    ofn.lpstrFilter = _T("Crossy Road Save Files (*.CR)\0*.CR\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");

    ofn.lpstrFile = szFileName_;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrInitialDir = _T("saves");

    std::string selectedFilePath;
    std::stringstream content;
    if (GetOpenFileName(&ofn) == TRUE) {
        // User selected a file
        selectedFilePath = ofn.lpstrFile;

        // Read content from the file
        std::ifstream file(selectedFilePath);
        content << file.rdbuf();
        file.close();
        // Handle the content as needed (you can print or return it)
        ofn.lpstrFile = currentDir;
        SetCurrentDirectory(currentDir);
        return content.str();
    } else {
        // User canceled the dialog
        selectedFilePath = "";
    }
    ofn.lpstrFile = currentDir;
    // Restore the current working directory
    SetCurrentDirectory(currentDir);

    return selectedFilePath;
}

std::string FileDialog::ShowSaveFileDialog(const std::string& contentToSave, const std::string& defaultFileName) {
    // Save the current working directory
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);

    // Initialize the buffer
    _tcscpy_s(szFileName_, _T(defaultFileName.c_str()));  // Set default file name with ".CR" extension

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd_;

    // Update the filter to include "Crossy Road Save Files"
    ofn.lpstrFilter = _T("Crossy Road Save Files (*.CR)\0*.CR\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");

    ofn.lpstrFile = szFileName_;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    //set directory to saves
    ofn.lpstrInitialDir = _T("saves");

    std::string savedFilePath;
    if (GetSaveFileName(&ofn) == TRUE) {
        // User selected a file for saving
        savedFilePath = ofn.lpstrFile;

        // Ensure the file name includes ".CR"
        if (!_tcsstr(savedFilePath.c_str(), _T(".CR"))) {
            _tcscat_s(szFileName_, _T(".CR"));
            savedFilePath += _T(".CR");
        }

        // Save content to the file
        std::ofstream file(savedFilePath);
        file << contentToSave;
        file.close();
    } else {
        // User canceled the dialog
        savedFilePath = "";
    }

    ofn.lpstrInitialDir = currentDir;

    // Restore the current working directory
    SetCurrentDirectory(currentDir);

    GetCurrentDirectory(MAX_PATH, currentDir);
//    _tprintf(_T("Current directory: %s\n"), currentDir);

    return savedFilePath;
}
