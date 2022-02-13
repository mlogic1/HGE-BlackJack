#pragma once

class IUpdatable
{
	public:
		virtual ~IUpdatable() {}

		virtual void Update(float dt) = 0;
};