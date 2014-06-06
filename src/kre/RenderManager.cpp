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

#include "../asserts.hpp"
#include "logger.hpp"
#include "RenderManager.hpp"
#include "RenderQueue.hpp"

namespace KRE
{
	RenderManager::RenderManager()
	{
	}

	RenderManager::~RenderManager()
	{
	}

	void RenderManager::AddQueue(int priority, RenderQueuePtr queue)
	{
		auto it = render_queues_.find(priority);
		if(it != render_queues_.end()) {
			LOG_WARN("Replacing queue " << it->second->name() << " at priority " << priority << " with queue " << queue->name());
		}
		render_queues_[priority] = queue;
	}

	void RenderManager::RemoveQueue(int priority)
	{
		auto it = render_queues_.find(priority);
		ASSERT_LOG(it != render_queues_.end(), "Tried to remove non-existant render queue at priority: " << priority);
		render_queues_.erase(it);
	}

	void RenderManager::Render(const WindowManagerPtr& wm) const
	{
		for(auto& q : render_queues_) {
			q.second->PreRender();
		}
		for(auto& q : render_queues_) {
			q.second->Render(wm);
		}
		for(auto& q : render_queues_) {
			q.second->PostRender();
		}
	}

	void RenderManager::AddRenderableToQueue(size_t q, size_t order, const RenderablePtr& r)
	{
		auto it = render_queues_.find(q);
		ASSERT_LOG(it != render_queues_.end(), "Tried to add renderable to non-existant render queue at priority: " << q);
		it->second->Enqueue(order, r);
	}
}