#include "UI_Button.h"
#include "GeneralDefines.h"

UI_Button::UI_Button() {
	text = Text();

    textAlignment = Text::Center;
    buttonState = UI_Button::Unselected;
    color = glm::vec4(1,1,1,1);
}

void UI_Button::init(const glm::vec2 &pos, const string &_buttonText, const int &size) {
    posButton = pos;
    fontSize = size;
    currentFontSize = fontSize;
    buttonText = _buttonText;

	if(!text.init("fonts/OpenSans-Bold.ttf"))
		cout << "Could not load font!!!" << endl;
}

void UI_Button::update(int deltaTime)
{
}

void UI_Button::render() {
    text.render(buttonText, glm::vec2(posButton.x, posButton.y), currentFontSize, glm::vec4(1, 1, 1, 1), textAlignment);
}

void UI_Button::setPosition(const glm::vec2 &_pos) {
    posButton = _pos;

    render();
}

void UI_Button::setColor(const glm::vec4 &_color) {
    color = glm::vec4(_color.x, _color.y, _color.z, 1);

    render();
}

void UI_Button::setSize(const int &_size) {
    fontSize = _size;

    if (buttonState == UI_Button::Unselected) currentFontSize = fontSize;
    else currentFontSize = fontSize * 1.3f;

    render();
}

void UI_Button::setAlignment(const Text::textAlignment _align) {
    textAlignment = _align;

    render();
}

void UI_Button::setState(const UI_Button::ButtonState _state) {
    buttonState = _state;

    if (buttonState != UI_Button::Unselected) currentFontSize = fontSize * 1.3f;
    else currentFontSize = fontSize;

    render();
}
