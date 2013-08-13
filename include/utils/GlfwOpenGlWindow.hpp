/**
 * @brief Abstract class for other classes to inherit that want access to an
 * GLFW OpenGL context and rendering window.
 *
 * @author Dustin Biser
 */

#ifndef GLFWOPENGLWINDOW_HPP_
#define GLFWOPENGLWINDOW_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

using namespace std;
struct GLFWwindow;

class GlfwOpenGlWindow {
public:
    virtual void start(int width, int height, const string & windowTitle);

    virtual ~GlfwOpenGlWindow();

    void setWindowTitle(string windowTitle) {
        this->windowTitle = windowTitle;
    }

    virtual void resize(int width, int height) { }

    virtual void close();

protected:
    GLFWwindow *window;
    string windowTitle;

    static void error_callback(int error, const char* description);

    static void keyInputHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

    void centerWindow();

    virtual void init() { }

    virtual void draw();

    virtual void cleanup() { }

    virtual void setupGl();
};


#endif /* GLFWOPENGLWINDOW_HPP_ */
