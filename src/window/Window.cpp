#include "window/Window.hpp"
#include "utils.hpp"

#include <iostream>
#include <algorithm>

std::vector<Window*> Window::instances;

Window::Window(const std::string& title, const glm::vec2& size)
    : RenderTarget(size),
      mBackgroundColor(0.f, 0.f, 0.f, 1.f)
{
    glfwInit();
    mWindow = glfwCreateWindow(mSize.x, mSize.y, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(mWindow);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW Error on initialization" << std::endl;
    }

    makeCurrentContext();

    glfwSetKeyCallback(mWindow, window_glfw_key);
    glfwSetCharCallback(mWindow, window_glfw_character);
    glfwSetMouseButtonCallback(mWindow, window_glfw_mouse_button);
    glfwSetCursorPosCallback(mWindow, window_glfw_mouse_move);
    glfwSetCursorEnterCallback(mWindow, window_glfw_mouse_enter);
    glfwSetScrollCallback(mWindow, window_glfw_scroll);

    instances.push_back(this);
}

void Window::makeCurrentContext()
{
    glfwMakeContextCurrent(mWindow);

}

Window::~Window()
{
    close();
    std::remove(instances.begin(), instances.end(), this);
    glfwTerminate();
}

void Window::update()
{
    if(!mWindow) return;

    double time = glfwGetTime();
    mFrameDuration = time - mPreviousFrameTime;
    mPreviousFrameTime = time;

    glfwPollEvents();

    // close window if it was closed
    if(!isOpen()) {
        close();
    }
}

void Window::display()
{
    if(!mWindow) return;
    glfwSwapBuffers(mWindow);
}

void Window::clear()
{
    glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close()
{
    if(!mWindow) return;
    std::cout << "Closing window" << std::endl;
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
}

void Window::setActive()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, getSize().x, getSize().y);
}

bool Window::isOpen() const
{
    return mWindow && !glfwWindowShouldClose(mWindow);
}

double Window::getFrameDuration() const
{
    return mFrameDuration;
}

float Window::getFPS() const
{
    return 1.0 / mFrameDuration;
}

float Window::getAspectRatio() const
{
    return mSize.x / mSize.y;
}

void Window::setTitle(const std::string& title)
{
    if(!mWindow) return;
    glfwSetWindowTitle(mWindow, title.c_str());
}

void Window::setSize(glm::vec2 size)
{
    if(!mWindow) return;
    glfwSetWindowSize(mWindow, (int)size.x, (int)size.y);
    mSize = size;
}

void Window::setBackgroundColor(glm::vec4 background_color)
{
    mBackgroundColor = background_color;
}

void Window::setCursorMode(Window::CursorMode mode)
{
    int m = GLFW_CURSOR_NORMAL;
    if(mode == Hidden) m = GLFW_CURSOR_HIDDEN;
    else if(mode == Captured) m = GLFW_CURSOR_DISABLED;
    glfwSetInputMode(mWindow, GLFW_CURSOR, m);
}

glm::vec2 Window::getMousePosition() const
{
    if(!mWindow) return glm::vec2(0, 0);
    double x, y;
    glfwGetCursorPos(mWindow, &x, &y);
    return glm::vec2(float(x), float(y));
}

void Window::setMousePosition(const glm::vec2& mouse_position)
{
    glfwSetCursorPos(mWindow, mouse_position.x, mouse_position.y);
}

Window* Window::getInstance(GLFWwindow* glfw_window)
{
    for(auto i = instances.begin(); i != instances.end(); ++i)
    {
        if((*i)->mWindow == glfw_window) {
            return (*i);
        }
    }
    return nullptr;
}

void window_glfw_mouse_button(GLFWwindow* glfw_window, int button, int action, int mods)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        if(action == GLFW_PRESS) {
            window->mouseButtonPressed(button, mods);
        } else if(action == GLFW_RELEASE) {
            window->mouseButtonReleased(button, mods);
        }
    }
}

void window_glfw_mouse_move(GLFWwindow* glfw_window, double x, double y)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->mouseMoved(x, y);
    }
}

void window_glfw_mouse_enter(GLFWwindow* glfw_window, int entered)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        if(entered == GL_TRUE) {
            window->mouseEnter();
        } else {
            window->mouseLeave();
        }
    }
}

void window_glfw_scroll(GLFWwindow* glfw_window, double dx, double dy)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->mouseScrolled(dx, dy);
    }
}

void window_glfw_key(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        if(action == GLFW_RELEASE) {
            window->keyReleased(key, scancode, mods);
        } else {
            window->keyPressed(key, scancode, mods, action == GLFW_REPEAT);
        }
    }
}

void window_glfw_character(GLFWwindow* glfw_window, unsigned int unicode)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->characterTyped(unicode);
    }
}
