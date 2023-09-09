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

[[cheerp::genericjs]] HTMLElement *updatedCanvas(
    Element *article,
    HTMLElement *canvas,
    int colsNum,
    int rowsNum)
{
        article->removeChild(canvas);
        auto newCanvas = createCanvas(rowsNum, colsNum);
        article->appendChild(newCanvas);
        return newCanvas;
}

[[cheerp::genericjs]] void webMain()
{
        int rowsNum = 50, colsNum = 70;
        HTMLElement *body = client::document.get_body();
        Element *article = body->getElementsByTagName("article")->item(0);
        auto canvas = createCanvas(rowsNum, colsNum);
        article->appendChild(canvas);

        auto *rowsInput = static_cast<HTMLInputElement *>(document.getElementById("rows"));
        auto *colsInput = static_cast<HTMLInputElement *>(document.getElementById("cols"));
        rowsInput->set_value(rowsNum);
        colsInput->set_value(colsNum);

        rowsInput->addEventListener(
            "change",
            cheerp::Callback([&](Event *e) -> void
                             {
                int newRowsNum = parseInt(rowsInput->get_value());
                if (newRowsNum < 10) return;
                rowsNum = newRowsNum;
                canvas = updatedCanvas(article, canvas, colsNum, rowsNum); }));
        colsInput->addEventListener("change", cheerp::Callback([&](Event *e) -> void
                                                               {
                int newColsNum = colsInput->get_valueAsNumber();
                if (newColsNum < 10) return;
                colsNum = newColsNum;
                canvas = updatedCanvas(article, canvas, colsNum, rowsNum); }));
        client::console.log("Bye from webMain!");
}