#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace hecate {

class Component {
public:
	Component();
	Component(std::string type);

	void setType(std::string type);
	std::string getType();

private:
	std::string type;
};

}

#endif // COMPONENT_H
