#include <iostream>
#include <cheerp/client.h>    //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
#include "components/canvas.cpp"
using namespace client;

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
