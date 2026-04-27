#pragma once
#include "GameObject.h"
namespace Match3
{
	class Candy : public GameObject
	{
	public:
		bool checked = false;
		Candy(int i);
	};
}

