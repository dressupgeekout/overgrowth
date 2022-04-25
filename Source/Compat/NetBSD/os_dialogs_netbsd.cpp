#include <Compat/os_dialogs.h>
#include <Logging/logdata.h>
#include <UserInput/input.h>

#include <SDL.h>


ErrorResponse OSDisplayError(const char* title, const char* contents, ErrorType type)
{
    bool old_mouse = Input::Instance()->GetGrabMouse();
    Input::Instance()->SetGrabMouse(false);
    UIShowCursor(1);
    
    SDL_MessageBoxButtonData buttons[] = {
        { 0, 0, "OK"},
        { 0, 1, "Cancel"},
        { 0, 2, "Retry"},
    };

    int numButtons = 0;

    switch (type) {
        case _ok_cancel_retry:
            ++numButtons;
        case _ok_cancel:
            ++numButtons;
        case _ok:
            ++numButtons;
            break;
        default: 
            LOGW << "Unhandled display error button type" << std::endl; 
            break;
    }

    std::string limited_contents = std::string(contents);

    int newline_count = 0;
    for(int i = 0; i < limited_contents.size(); i++) {
        if(limited_contents[i] == '\n') {
            newline_count++;
            if(newline_count == 20) {
                limited_contents = limited_contents.substr(0,i) + "\n[Contents Cut]"; 
            }
        }
    }

    SDL_MessageBoxData messageBox = {
        SDL_MESSAGEBOX_ERROR,
        SDL_GL_GetCurrentWindow(),
        title,
        limited_contents.c_str(),
        numButtons,
        buttons,
        NULL
    };

    int choice = -1;
    if (SDL_ShowMessageBox(&messageBox, &choice) < 0) {
        LOGE << "Failed to show message dialog: " <<  SDL_GetError() << std::endl;
    }

    ErrorResponse ret = _continue;
    if (choice == 2) {
        ret = _retry;
    } else if (choice == 1) {
        ret = _er_exit;
    } else {
    }

    Input::Instance()->SetGrabMouse(old_mouse);
    UIShowCursor(0);
    return ret;
}
