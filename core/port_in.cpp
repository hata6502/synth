#include "port_in.hpp"

typedef shared_ptr<PortIn> PortIn_p;

PortIn::PortIn() : com(nullptr), src(PortOut_p(nullptr)), int_("")
{
	uuid_generate(this->id);
	this->initVal();
}

void PortIn::initVal()
{
	this->val = 0.0;
}

void PortIn::connect(PortOut_p &src)
{
	this->disconnect();
	this->src = src;
	src->tos.push_back(this);
}

void PortIn::disconnect()
{
	if (this->src)
	{
		PortIn *dis = this;
		this->src->tos.erase(remove_if(this->src->tos.begin(), this->src->tos.end(), [&](PortIn *to) -> bool { return to == dis; }), this->src->tos.end());
		this->src = PortOut_p(nullptr);
	}
}

/*
var PortIn = class{
	import(im){
		this.id = im.id;
		this.int = im.int;
		return { id: this.id, inst: this };
	}
};

*/