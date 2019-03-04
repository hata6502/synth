#include "port_out.hpp"

PortOut::PortOut() : int_("")
{
	this->initVal();
}

double PortOut::getVal()
{
	return this->val;
}

double PortOut::setLatch(double value)
{
	return this->latch = value;
}

void PortOut::initVal()
{
	this->latch = 0.0;
	this->val = 0.0;
}

void PortOut::update(deque<Component *> &chcoms)
{
	if (this->val != this->latch)
	{
		this->val = this->latch;

		for (PortIn *to : this->tos)
		{
			to->val = this->val;
			chcoms.push_back(to->com); // ここで重複を確認する
		}
	}
}

void PortOut::disconnectAll()
{
	while (!this->tos.empty())
	{
		this->tos[0]->disconnect();
	}
}

vector<string> PortOut::exportTos()
{
	vector<string> tos;
	char uuid_str[37];

	for (PortIn *to : this->tos)
	{
		uuid_unparse_lower(to->id, uuid_str);
		tos.push_back(string(uuid_str));
	}

	return tos;
}

/*
var PortOut = class{


	import(im){
		this.to_ids = im.tos;
		this.int = im.int;
	}

	connectById(lut){
		this.disconnectAll();
		this.to_ids.forEach((to_id) => {
			for(var i = 0; i<lut.length; i++){
				if (to_id==lut[i].id){
					lut[i].inst.connect(this);
					break;
				}
			}
		});
	}
};

*/