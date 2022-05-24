#pragma once
#include "Observer.h"
namespace dae {
	class Achievement {};;
	class Achievements : public Observer
	{
	public:
		virtual void onNotify(const GameObject& gameObject, Event event);
	private:
		void unlock(Achievement achievement);
	};

}