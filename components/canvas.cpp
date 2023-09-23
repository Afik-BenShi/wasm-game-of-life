#include "../conwayLogic.cpp"
#include <cheerp/client.h>    //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
#include <iostream>
#include <string>
using namespace client;

int rows = 0;
int cols = 0;
double interval = -1.0;
namespace canvas {

[[cheerp::genericjs]] client::HTMLButtonElement *
addButton(HTMLElement *parent, const std::string &text, const std::string &id,
          const std::string &className, EventListener *callback) {
  HTMLButtonElement *button =
      static_cast<HTMLButtonElement *>(document.createElement("button"));
  button->set_innerHTML(text.c_str());
  button->set_id(id.c_str());
  button->set_className(className.c_str());

  if (callback)
    button->addEventListener("click", callback);
  parent->appendChild(button);
  return button;
}

[[cheerp::genericjs]] HTMLElement *createCanvas(int ***boardPtr, int height,
                                                int width) {
  HTMLElement *div =
      static_cast<HTMLElement *>(client::document.createElement("div"));
  rows = height;
  cols = width;
  *boardPtr = (int **)malloc(height * sizeof(int *));
  auto clickHandler = [&](MouseEvent *e) -> void {
    auto *button = e->get_srcElement();
    auto btnClass = button->get_className();
    auto id = button->get_id();
    auto comma = id->indexOf(",");
    int iloc = client::parseInt(id->slice(0, comma));
    int jloc = client::parseInt(id->slice(comma + 1));
    if (btnClass == new String("alive")) {
      ((*boardPtr)[iloc])[jloc] = 0;
      button->set_className("dead");
    } else if (btnClass == new client::String("dead")) {
      ((*boardPtr)[iloc])[jloc] = 1;
      button->set_className("alive");
    }
  };
  for (int i = 0; i < height; i++) {
    (*boardPtr)[i] = (int *)malloc(width * sizeof(int));
    for (int j = 0; j < width; j++) {
      ((*boardPtr)[i])[j] = 0;
      auto id = std::to_string(i) + "," + std::to_string(j);
      addButton(div, "", id, "dead", cheerp::Callback(clickHandler));
    }
  }

  div->set_className("conway-grid");
  auto *style = div->get_style();
  style->set_gridTemplateColumns(
      ("repeat(" + std::to_string(width) + ", 1fr)").c_str());
  return div;
}

[[cheerp::genericjs]] HTMLElement *resizeCanvas(int ***boardPtr,
                                                HTMLElement *article,
                                                HTMLElement *canvas,
                                                int colsNum, int rowsNum) {
  article->removeChild(canvas);
  auto newCanvas = createCanvas(boardPtr, rowsNum, colsNum);
  article->appendChild(newCanvas);
  return newCanvas;
}

[[cheerp::genericjs]] int ***initializeCanvas(int ***boardPtr,
                                              HTMLElement *article) {
  int rowsNum = 50, colsNum = 70;
  auto *rowsInput =
      static_cast<HTMLInputElement *>(document.getElementById("rows"));
  auto *colsInput =
      static_cast<HTMLInputElement *>(document.getElementById("cols"));
  rowsInput->set_value(rowsNum);
  colsInput->set_value(colsNum);

  auto canvas = createCanvas(boardPtr, rowsNum, colsNum);
  article->appendChild(canvas);

  rowsInput->addEventListener(
      "change", cheerp::Callback([&](Event *e) -> void {
        int newRowsNum = parseInt(rowsInput->get_value());
        if (newRowsNum < 10)
          return;
        rowsNum = newRowsNum;
        canvas = resizeCanvas(boardPtr, article, canvas, colsNum, rowsNum);
      }));

  colsInput->addEventListener("change", cheerp::Callback([&](Event *e) -> void {
                                int newColsNum = colsInput->get_valueAsNumber();
                                if (newColsNum < 10)
                                  return;
                                colsNum = newColsNum;
                                canvas = resizeCanvas(boardPtr, article, canvas,
                                                      colsNum, rowsNum);
                              }));
  return boardPtr;
}

[[cheerp::genericjs]] void updateBasedOnDiff(int **diff) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (diff[i][j]) {
        auto id = std::to_string(i) + "," + std::to_string(j);
        auto *button = static_cast<HTMLElement *>(
            client::document.getElementById(id.c_str()));
        if (button->get_className() == new client::String("alive")) {
          button->set_className("dead");
        } else {
          button->set_className("alive");
        }
      }
    }
  }
}

[[cheerp::genericjs]] void tickButton(int ***boardPtr,
                                      client::HTMLButtonElement *tickbtn) {
  tickbtn->addEventListener("click", cheerp::Callback([&]() -> void {
                              int **diff = tick(boardPtr, rows, cols);
                              updateBasedOnDiff(diff);
                            }));
}

[[cheerp::genericjs]] void startStop(int ***boardPtr,
                                     client::HTMLButtonElement *controlBtn) {

  controlBtn->addEventListener(
      "click", cheerp::Callback([&]() -> void {
        int working = false;
        if (controlBtn->get_innerText() == new client::String("start")) {
          working = true;
          interval = client::setInterval(cheerp::Callback([&]() -> void {
                                           if (working) {
                                             int **diff =
                                                 tick(boardPtr, rows, cols);
                                             updateBasedOnDiff(diff);
                                           }
                                         }),
                                         50.0);
          controlBtn->set_innerText("stop");
        } else {
          client::clearInterval(interval);
          interval = -1;
          controlBtn->set_innerText("start");
        }
      }));
}
} // namespace canvas
