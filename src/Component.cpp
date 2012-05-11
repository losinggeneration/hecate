#include "Component.h"

namespace hecate {

Component::Component() {
}

Component::Component(std::string type) {
	setType(type);
}

void Component::setType(std::string type) {
	this->type = type;
}

std::string Component::getType() {
	return type;
}

}
