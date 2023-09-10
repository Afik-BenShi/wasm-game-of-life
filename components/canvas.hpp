#include <cheerp/client.h>    //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
using namespace client;
#include "canvasUtils.hpp"

int rows = 0;
int **boardMatrix;

[[cheerp::genericjs]] void addButton(
    HTMLElement *parent,
    const std::string &text,
    const std::string &id,
    const std::string &className,
    EventListener *callback)
{
    HTMLButtonElement *button =
        static_cast<HTMLButtonElement *>(
            document.createElement("button"));
    button->set_innerHTML(text.c_str());
    button->set_id(id.c_str());
    button->set_className(className.c_str());

    if (callback)
        button->addEventListener("click", callback);
    parent->appendChild(button);
}

[[cheerp::genericjs]] HTMLElement *createCanvas(int height, int width)
{
    HTMLElement *div = static_cast<HTMLElement *>(
        document.createElement("div"));
    boardMatrix = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++)
    {
        boardMatrix[i] = (int *)malloc(width * sizeof(int));
        for (int j = 0; j < width; j++)
        {
            boardMatrix[i][j] = 0;
            auto id = std::to_string(i) + "," + std::to_string(j);
            auto clickHandler = [&](MouseEvent *e) -> void
            {
                auto *button = e->get_srcElement();
                auto btnClass = button->get_className();
                auto idx = idToArr(button->get_id());
                int iloc = std::get<0>(idx);
                int jloc = std::get<1>(idx);
                if (btnClass == new String("alive"))
                {
                    boardMatrix[iloc][jloc] = 1;
                    button->set_className("dead");
                }
                else if (btnClass == new client::String("dead"))
                {
                    boardMatrix[iloc][jloc] = 0;
                    button->set_className("alive");
                }
            };
            addButton(div, "", id, "dead", cheerp::Callback(clickHandler));
        }
    }
    div->set_className("conway-grid");
    auto *style = div->get_style();
    style->set_gridTemplateColumns(("repeat(" + std::to_string(width) + ", 1fr)").c_str());
    return div;
}

[[cheerp::genericjs]] HTMLElement *resizeCanvas(
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

[[cheerp::genericjs]] void resizeControl(Element *article)
{
    int rowsNum = 50, colsNum = 70;
    auto *rowsInput = static_cast<HTMLInputElement *>(document.getElementById("rows"));
    auto *colsInput = static_cast<HTMLInputElement *>(document.getElementById("cols"));
    rowsInput->set_value(rowsNum);
    colsInput->set_value(colsNum);

    auto canvas = createCanvas(rowsNum, colsNum);
    article->appendChild(canvas);

    rowsInput->addEventListener(
        "change",
        cheerp::Callback([&](Event *e) -> void
                         {
                int newRowsNum = parseInt(rowsInput->get_value());
                if (newRowsNum < 10) return;
                rowsNum = newRowsNum;
                canvas = resizeCanvas(article, canvas, colsNum, rowsNum); }));

    colsInput->addEventListener("change", cheerp::Callback([&](Event *e) -> void
                                                           {
                int newColsNum = colsInput->get_valueAsNumber();
                if (newColsNum < 10) return;
                colsNum = newColsNum;
                canvas = resizeCanvas(article, canvas, colsNum, rowsNum); }));
}
