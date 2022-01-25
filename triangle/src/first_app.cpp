#include "first_app.hpp"
namespace zw{
    void FirstApp::run(){
        while (!this->zwWindow.shouldClose())
        {
            /* code */
            glfwPollEvents();
        }
        
    }
}