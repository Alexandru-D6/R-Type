#include "UI_Button.h"
#include "GeneralDefines.h"

UI_Button::UI_Button() {
	projection = NULL;
	text = Text();
}

UI_Button::UI_Button(glm::mat4 *project) {
    projection = project;
}

void UI_Button::init(glm::ivec2 &tileMapPos, const string &buttonText) {

    tileMapDispl = tileMapPos;

	this->buttonText = buttonText;
	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

    //sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void UI_Button::update(int deltaTime)
{
    //sprite->update(deltaTime);
 
    //sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void UI_Button::render() {
    //sprite->render();
	text.render("Rebots: ", glm::vec2(10, 30), 32, glm::vec4(1, 1, 1, 1));
}

void UI_Button::setPosition(const glm::vec2 &pos) {
    posButton = pos;
    //sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}
