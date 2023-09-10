#include <cheerp/client.h>    //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
#include "components/canvas.hpp"

using namespace client;

[[cheerp::genericjs]] void outputNumberOfElementsToTheConsole()
{
        double number = document.getElementsByTagName("*")->get_length();
        client::console.log("Live elements = ", number);
}

// This function will be called only after the DOM is fully loaded
[[cheerp::genericjs]] void loadCallback()
{
        client::console.log("Hi from loadCallback!");

        // Do something with the document
        outputNumberOfElementsToTheConsole();
        client::console.log("Bye from loadCallback!");
}

[[cheerp::genericjs]] void webMain()
{
        HTMLElement *body = client::document.get_body();
        Element *article = body->getElementsByTagName("article")->item(0);
        canvas::resizeControl(article);
        client::console.log("Bye from webMain!");
}