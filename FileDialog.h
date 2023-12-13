#pragma once

#include <string>
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

class FileDialog {
public:
    explicit FileDialog(HWND hwnd = nullptr);
    std::string ShowOpenFileDialog();
    std::string ShowSaveFileDialog(const std::string& contentToSave, const std::string& defaultFileName);

private:
    HWND hwnd_;
    TCHAR szFileName_[MAX_PATH];
};