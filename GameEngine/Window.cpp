#include "Window.h"

Window::Window() : window(nullptr), context(nullptr)
{
    
}

Window::~Window()
{
    OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
    //anything less 0 means it didn't work
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL" << std::endl;
        return false;
    }
    
    //sdl init does work save w and h of window
    this->width = width_;
    this->height = height_;

    SetPreAttributes();
    //convert title name_ to const char , defind x and y pos of window launch centre of the screen, width height of window, 
    //flag want to set tell SDL window expecting opengl rendering to happend
    window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);
    SetPosAttributes();
  
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        //return false;
        exit(1);
    }
    //when the object is rendered, thier Z value will be taken into account
    glEnable(GL_DEPTH_TEST);
    std::cout << "OpenGL version:" << glGetString(GL_VERSION) << std::endl;

    //if there is no if error sta return true
    return true;
}

void Window::OnDestroy()
{
    //Delete the OPENGL context
    SDL_GL_DeleteContext(context);

    //Destroy Wind
    SDL_DestroyWindow(window);

    //Set window equal null
    window = nullptr;
}

int Window::GetWidth() const
{
    return width;
}

int Window::GetHeight() const
{
    return height;
}

SDL_Window* Window::GetWindow() const
{
    return window;
}

//function before sdl window is created
void Window::SetPreAttributes()
{
   //will get rid fo any deprecated functions (Deprecation, in its programming sense,
   // is the process of taking older code and marking it as no longer being useful within the codebase)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //setting glversion 4.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //enable doublebuffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //set the swap interval to be equal and sychronized with the vertical retrace of your screen
    SDL_GL_SetSwapInterval(1);

    //f
     glewExperimental = GL_TRUE;
}

void Window::SetPosAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
   
}