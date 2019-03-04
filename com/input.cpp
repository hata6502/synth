#include "input.hpp"

map<string, int> Input::getIn()
{
	return map<string, int>();
}

#define OUT_VALUE 0
map<string, int> Input::getOut()
{
	return map<string, int>{{"value", OUT_VALUE}};
}

double Input::setValue(double value)
{
	this->val = value;
	return value;
}

Input::Input() : Component()
{
	this->initPort(this->getIn().size(), this->getOut().size());
	this->com_name = string(__FUNCTION__);
	this->val = 0.0;
}

void Input::onChangeTime(double dt, deque<Component *> &chcoms)
{
	Component::onChangeTime(dt, chcoms);
	this->outs[OUT_VALUE]->setLatch(this->val);
	this->update(chcoms);
}

void Input::exportExtends()
{
	this->extends = map<string, string>{{"value", to_string(this->val)}};
}

/*
var Input = class extends Component{

	constructor(){
		this.ui_class = UiInput;
	}

	import(im){
		var lut = super.import(im);
		this._val = im.value;
		return lut;
	}
};

*/