#include <cheerp/client.h> //Misc client side stuff
#include <cheerp/clientlib.h> //Complete DOM/HTML5 interface
using namespace client;

[[cheerp::genericjs]]
void addButton(
    HTMLElement *parent,
    const std::string& text, 
    const std::string& id, 
    const std::string& className, 
    EventListener* callback
    )
{
	HTMLButtonElement *button = 
        static_cast<HTMLButtonElement *>(
            document.createElement("button")
            );
	button->set_innerHTML(text.c_str());
    button->set_id(id.c_str());
    button->set_className(className.c_str());

	if (callback)
		button->addEventListener("click", callback);
    parent->appendChild(button);
}


[[cheerp::genericjs]]
HTMLElement *createCanvas(int height, int width){
    HTMLElement *div =
        static_cast<HTMLElement *>(
            document.createElement("div")
            );
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto id = std::to_string(i)+","+std::to_string(j);
            auto clickHandler = [](MouseEvent *e) -> void {
                auto *button = e->get_srcElement();
                auto btnClass = button->get_className();
                client::console.log(btnClass);
                auto actualButton = document.getElementById(button->get_id());
                if (btnClass == new String("alive")){
                    button->set_className("dead");
                } else if (btnClass == new client::String("dead")){
                    button->set_className("alive");
                }
            };
            addButton(div, "", id, "dead", cheerp::Callback(clickHandler));
        }
        
    }
    div->set_className("conway-grid");
    auto *style = div->get_style();
    style->set_gridTemplateColumns(("repeat("+std::to_string(width)+", 1fr)").c_str());
    return div;
}
