#include <string>
#include <cheerp/client.h>	  //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
#include "canvasUtils.cpp"

namespace canvas
{
	int rows = 0;
	int **boardMatrix;

	[[cheerp::genericjs]] void addButton(
		client::HTMLElement *parent,
		const std::string &text,
		const std::string &id,
		const std::string &className,
		client::EventListener *callback);

	[[cheerp::genericjs]] client::HTMLElement *createCanvas(int height, int width);

	[[cheerp::genericjs]] client::HTMLElement *resizeCanvas(
		client::Element *article,
		client::HTMLElement *canvas,
		int colsNum,
		int rowsNum);

	[[cheerp::genericjs]] void resizeControl(client::Element *article);
}
