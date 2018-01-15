#pragma once

struct keyBooleans {
	bool q;
	bool quit;
	bool w;
	bool s;
	bool a;
	bool d;
	bool x;
	bool i;
	bool l;
	bool k;
	bool j;
	bool space;
	bool arrow_right;
	bool arrow_left;
	bool arrow_up;
	bool arrow_down;
	bool b;
	bool v;
	bool n;
	bool m;

	int mousePosX;
	int mousePosY;
};

class inputProcessing
{
public:
	inputProcessing();
	~inputProcessing();

	keyBooleans events;
	void update();
private:

};

