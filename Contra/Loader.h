#pragma once

namespace Contra
{
	class Loader;
	class Bill;
}

class Contra::Loader
{
public:

	static Bill* load(int round);
};
