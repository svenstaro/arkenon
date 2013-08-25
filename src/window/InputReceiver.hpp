#ifndef _WINDOW_INPUTRECEIVER_HPP
#define _WINDOW_INPUTRECEIVER_HPP

#include <vector>
#include <memory>

class InputReceiver {
public:
    virtual ~InputReceiver() = 0;

    void addInputForwarding(InputReceiver* receiver);

    void mouseButtonPressed(int button, int mods);
    void mouseButtonReleased(int button, int mods);
    void mouseMoved(double x, double y);
    void mouseScrolled(double dx, double dy);
    void mouseEnter();
    void mouseLeave();
    void keyPressed(int key, int scancode, int mods, bool repeated);
    void keyReleased(int key, int scancode, int mods);
    void characterTyped(unsigned int unicode);

    virtual void onMouseButtonPressed(int button, int mods);
    virtual void onMouseButtonReleased(int button, int mods);
    virtual void onMouseMoved(double x, double y);
    virtual void onMouseScrolled(double dx, double dy);
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual void onKeyPressed(int key, int scancode, int mods, bool repeated);
    virtual void onKeyReleased(int key, int scancode, int mods);
    virtual void onCharacterTyped(unsigned int unicode);

protected:
    std::vector<InputReceiver*> mForwards;

};

#endif
