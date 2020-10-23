#ifndef AZGARD_LIB_WINDOW
#define AZGARD_LIB_WINDOW

namespace Azgard {

class Window {
public:
    enum graphicApi{
        OpenGLES3,
        None = 0,
    };
    
    void swap();

    void setGraphicApi(graphicApi api);

    void setVsync(bool vsync);

    void run(void(*frameCallback)(void*));

    graphicApi getCurrentGraphicApi();

    Window(const char* title, unsigned int width, unsigned int height);
    ~Window();

private:
    class WindowNativeHandler;
    class OpenGLContext;

    unsigned int width_ = 0;
    unsigned int height_ = 0;
    const char* title_ = nullptr;
    static graphicApi graphicApi_;

    WindowNativeHandler* windowHandler = nullptr;
    OpenGLContext* openGLContext = nullptr;
};

}

#endif