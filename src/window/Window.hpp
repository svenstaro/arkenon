#ifndef _WINDOW_WINDOW_HPP
#define _WINDOW_WINDOW_HPP

#include <string>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "render/RenderTarget.hpp"
#include "window/InputReceiver.hpp"

class Window : public RenderTarget, public InputReceiver {
public:
    enum CursorMode {
        Normal,     ///< Normal mouse behaviour
        Hidden,     ///< Mouse cursor invisible, but still leaves the screen.
        Captured    /**< Mouse cursor invisible, and it cannot leave the screen. For mouse position,
                     * absolute float values outside window boundaries can be reported. */
    };

public:
    Window(const std::string& title, const glm::vec2& size);
    virtual ~Window() = 0;

    /**
     * Sets this window as the current OpenGL context. Use this before rendering into this
     * window when using multiple windows.
     */
    void makeCurrentContext();

    /**
     * Updates the window. This captures the timer and polls window events.
     */
    void update();

    /**
     * Swaps buffers, displaying the recently rendered frame.
     */
    void display();

    /**
     * Clears the frame with the color set by Window::setBackgroundColor.
     */
    void clear();

    /**
     * Closes the window and frees all the resources.
     */
    void close();

    // from RenderTarget
    void setActive();
    void setSize(const glm::vec2 &size);
    glm::vec2 getSize() const;

    bool isOpen() const;
    double getFrameDuration() const;
    float getFPS() const;
    float getAspectRatio() const;

    void setTitle(const std::string& title);
    void setBackgroundColor(glm::vec4 background_color);
    void setCursorMode(CursorMode mode);

    glm::vec2 getMousePosition() const;
    void setMousePosition(const glm::vec2& mouse_position);

private:
    GLFWwindow* mWindow;
    double mFrameDuration = 0;
    double mPreviousFrameTime = 0;
    glm::vec4 mBackgroundColor;

public:
    static std::vector<Window*> instances; ///< All existing Windows are stored here.

    /**
     * Returns a Window instance for a given GLFWwindow. This is required to send
     * a global C-style event callback back to the right Window instance.
     * @return The Window instance, or nullptr if none matches.
     */
    static Window* getInstance(GLFWwindow* glfw_window);
};


void window_glfw_mouse_button(GLFWwindow* glfw_window, int button, int action, int mods);
void window_glfw_mouse_move(GLFWwindow* glfw_window, double x, double y);
void window_glfw_mouse_enter(GLFWwindow* glfw_window, int entered);
void window_glfw_scroll(GLFWwindow* glfw_window, double dx, double dy);
void window_glfw_key(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
void window_glfw_character(GLFWwindow* glfw_window, unsigned int unicode);

#endif
