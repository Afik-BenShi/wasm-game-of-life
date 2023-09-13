#include <iostream>
#include <cheerp/client.h>    //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
#include "components/canvas.cpp"
using namespace client;

// [[cheerp::genericjs]] void outputNumberOfElementsToTheConsole()
// {
//     double number = document.getElementsByTagName("*")->get_length();
//     client::console.log("Live elements = ", number);
// }

// This function will be called only after the DOM is fully loaded
// [[cheerp::genericjs]] void loadCallback()
// {
//     client::console.log("Hi from loadCallback!");

//     // Do something with the document
//     outputNumberOfElementsToTheConsole();
//     client::console.log("Bye from loadCallback!");
// }

[[cheerp::genericjs]] void webMain()
{
    int ***boardPtr = (int ***)malloc(sizeof(int **));
    client::console.log("start");
    HTMLElement *body = client::document.get_body();
    HTMLElement *article = static_cast<HTMLElement *>(body->getElementsByTagName("article")->item(0));
    canvas::initializeCanvas(boardPtr, article);
    HTMLButtonElement *tickBtn = static_cast<HTMLButtonElement *>(client::document.getElementById("tick"));
    canvas::test(boardPtr, tickBtn, article);
}
