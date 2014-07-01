/*
	Copyright (C) 2003-2013 by Kristina Simpson <sweet.kristas@gmail.com>
	
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	   1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgement in the product documentation would be
	   appreciated but is not required.

	   2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.

	   3. This notice may not be removed or altered from any source
	   distribution.
*/

#pragma once

#include "Renderable.hpp"
#include "SceneFwd.hpp"

namespace KRE
{
	class SceneObject : public Renderable
	{
	public:
		SceneObject(const std::string& name);
		virtual ~SceneObject();
		size_t getQueue() const { return queue_; }
		void setQueue(size_t q) { queue_ = q; }
		const std::string& objectName() const { return name_; }
		DisplayDeviceDef attach(const DisplayDevicePtr& dd);
	private:
		virtual DisplayDeviceDef doAttach(const DisplayDevicePtr& dd) = 0;
		size_t queue_;
		std::string name_;
		SceneObject();
		SceneObject(const SceneObject&);
	};
}