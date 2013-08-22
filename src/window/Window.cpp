#include "window/Window.hpp"

#include <iostream>
#include <algorithm>

std::vector<Window*> Window::instances;

Window::Window(const std::string& title)
    : mBackgroundColor(0.f, 0.f, 0.f, 1.f)
{
    glfwInit();
    mWindow = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(mWindow);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW Error on initialization" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);

    glfwSetKeyCallback(mWindow, window_glfw_key);
    glfwSetCharCallback(mWindow, window_glfw_character);
    glfwSetMouseButtonCallback(mWindow, window_glfw_mouse_button);
    glfwSetCursorPosCallback(mWindow, window_glfw_mouse_move);
    glfwSetCursorEnterCallback(mWindow, window_glfw_mouse_enter);
    glfwSetScrollCallback(mWindow, window_glfw_scroll);

    instances.push_back(this);
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

bool Window::isOpen()
{
    return mWindow && !glfwWindowShouldClose(mWindow);
}

double Window::getFrameDuration()
{
    return mFrameDuration;
}

float Window::getFPS()
{
    return 1.0 / mFrameDuration;
}

float Window::getAspectRatio()
{
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return width / height;
}

void Window::setTitle(const std::string& title)
{
    if(!mWindow) return;
    glfwSetWindowTitle(mWindow, title.c_str());
}

void Window::setSize(int width, int height)
{
    if(!mWindow) return;
    glfwSetWindowSize(mWindow, width, height);
}

void Window::setBackgroundColor(glm::vec4 background_color)
{
    mBackgroundColor = background_color;
}

void Window::onMouseButtonPressed(int button, int mods) {}
void Window::onMouseButtonReleased(int button, int mods) {}
void Window::onMouseMoved(double x, double y) {}
void Window::onMouseScrolled(double dx, double dy) {}
void Window::onMouseEnter() {}
void Window::onMouseLeave() {}
void Window::onKeyPressed(int key, int scancode, int mods, bool repeated) {}
void Window::onKeyReleased(int key, int scancode, int mods) {}
void Window::onCharacterTyped(unsigned int unicode) {}

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
            window->onMouseButtonPressed(button, mods);
        } else if(action == GLFW_RELEASE) {
            window->onMouseButtonReleased(button, mods);
        }
    }
}

void window_glfw_mouse_move(GLFWwindow* glfw_window, double x, double y)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->onMouseMoved(x, y);
    }
}

void window_glfw_mouse_enter(GLFWwindow* glfw_window, int entered)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        if(entered == GL_TRUE) {
            window->onMouseEnter();
        } else {
            window->onMouseLeave();
        }
    }
}

void window_glfw_scroll(GLFWwindow* glfw_window, double dx, double dy)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->onMouseScrolled(dx, dy);
    }
}

void window_glfw_key(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        if(action == GLFW_RELEASE) {
            window->onKeyReleased(key, scancode, mods);
        } else {
            window->onKeyPressed(key, scancode, mods, action == GLFW_REPEAT);
        }
    }
}

void window_glfw_character(GLFWwindow* glfw_window, unsigned int unicode)
{
    Window* window = Window::getInstance(glfw_window);
    if(window)
    {
        window->onCharacterTyped(unicode);
    }
}
