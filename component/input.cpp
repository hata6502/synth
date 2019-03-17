#include "input.hpp"

#include <io.hpp>

static void setvalueHandler(Component *com, vector<string> &args);

vector<string> Input::getIn()
{
	return vector<string>();
}

#define OUT_VALUE 0
vector<string> Input::getOut()
{
	return vector<string>{"value"};
}

vector<CallCommand> &Input::getCallCommands()
{
	static vector<CallCommand> call_commands = {
		registerCallCommand(setvalue),
	};
	return call_commands;
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

#define this static_cast < Input * > (com)
static void setvalueHandler(Component *com, vector<string> &args)
{
	if (args.size() != 2)
	{
		throw runtime_error("構文: setvalue (数値)");
	}

	this->setValue(stod(args[1]));

	EmptyResponse response;
	respond(response);
}
#undef this

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