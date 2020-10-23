#include "Window.hpp"
#include "Platform/Config.hpp"

using namespace Azgard;

#if WebBrowserPlatform
#include <emscripten.h>
#endif

#ifdef SDL2Window
#include "SDL.h"

class Window::WindowNativeHandler {
public:
    SDL_Window* sdl2Handle_ = nullptr;
};

class Window::OpenGLContext {
public:
    SDL_GLContext* sdl2Context_ = nullptr;
};

#endif


Window::graphicApi Window::graphicApi_ = Window::graphicApi::None;


Window::Window(const char* title, unsigned int width, unsigned int height): title_{title}, width_{width}, height_{height} {
    #ifdef SDL2Window
    #ifdef WebBrowserPlatform
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    #else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    this->windowHandler = new WindowNativeHandler();
    this->windowHandler->sdl2Handle_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    // SDL_GL_SetSwapInterval(0);


    // this->openGLContext = SDL_GL_CreateContext(this->windowHandler);

    // if(glewInit() != GLEW_OK) {
    //     std::cout << "Glew not initialized!" << std::endl;
    //     throw;
    // }

    this->graphicApi_ = Window::graphicApi::None;

    #endif
}

Window::~Window() {
    #ifdef SDL2Window

    if(this->graphicApi_ == Window::graphicApi::OpenGLES3 && this->openGLContext)
        SDL_GL_DeleteContext(this->openGLContext->sdl2Context_);

    SDL_DestroyWindow(this->windowHandler->sdl2Handle_);
    #endif
}

void Window::swap() {
    #ifdef SDL2Window
    SDL_GL_SwapWindow(this->windowHandler->sdl2Handle_);
    #endif
}

void Window::setVsync(bool useVsync) {
    #ifdef SDL2Window
    SDL_GL_SetSwapInterval(useVsync);
    #endif
}

void Window::run(void(*frameCallback)(void*)) {
#ifdef WebBrowserPlatform
    emscripten_set_main_loop(frameCallback, -1, true);
#elif SDL2Window
    bool quit = false;
    SDL_Event e;

    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }

        frameCallback(nullptr);
        this->swap();
    }
#endif
}


void Window::setGraphicApi(Window::graphicApi api) {
    // if(context == OpenGLES3Context) {
    //     #ifdef OPENGLES3_SUPORTED

    //     SDL_GL_MakeCurrent(this->window, glContext);
    
    //     #elif
    //     #error OPENGLES3 NOT SUPORTED
    //     #endif

    // }
}

#endif