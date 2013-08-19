#ifndef _WINDOW_WINDOW_HPP
#define _WINDOW_WINDOW_HPP

#include <string>
#include <vector>
#include <memory>

#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string& title);
    virtual ~Window() = 0;

    void update();
    void display();
    void close();

    bool isOpen();
    double getFrameDuration();
    float getFPS();

    void setTitle(const std::string& title);
    void setSize(int width, int height);

    virtual void onMouseButtonPressed(int button, int mods);
    virtual void onMouseButtonReleased(int button, int mods);
    virtual void onMouseMoved(double x, double y);
    virtual void onMouseScrolled(double dx, double dy);
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual void onKeyPressed(int key, int scancode, int mods, bool repeated);
    virtual void onKeyReleased(int key, int scancode, int mods);
    virtual void onCharacterTyped(unsigned int unicode);

private:
    GLFWwindow* mWindow;
    double mFrameDuration;
    double mPreviousFrameTime;

public:
    static std::vector<Window*> instances;
    static Window* getInstance(GLFWwindow*);
};


void window_glfw_mouse_button(GLFWwindow* glfw_window, int button, int action, int mods);
void window_glfw_mouse_move(GLFWwindow* glfw_window, double x, double y);
void window_glfw_mouse_enter(GLFWwindow* glfw_window, int entered);
void window_glfw_scroll(GLFWwindow* glfw_window, double dx, double dy);
void window_glfw_key(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
void window_glfw_character(GLFWwindow* glfw_window, unsigned int unicode);

#endif
