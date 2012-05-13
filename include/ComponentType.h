#ifndef HECTATE_COMPONENTTYPE_H
#define HECTATE_COMPONENTTYPE_H

namespace hecate {

class ComponentType {
public:
	ComponentType();

	int getId() const;
	long getBit() const;

private:
	void init();

	int id;
	long bit;
};

}

#endif