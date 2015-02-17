#ifndef NEB_MOD_MAZE_HPP
#define NEB_MOD_MAZE_HPP

#include <neb/core/game/map/base.hpp>

namespace neb { namespace mod { namespace maze {
	/** @brief Base
	 */
	class Base:
		virtual public neb::fnd::game::map::Base
	{
		public:
			Base();
			virtual ~Base();
			virtual void		init(parent_t * const & p);
			virtual void		release();
			virtual void		step(gal::etc::timestep const &);
			glm::ivec3		size_;
	};
}}}

#endif
