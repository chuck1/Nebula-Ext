#ifndef NEBULA_MOD_HF_BASE_HPP
#define NEBULA_MOD_HF_BASE_HPP

#include <neb/core/game/map/base.hpp>

#include <neb/core/game/map/base.hpp>

namespace neb { namespace mod { namespace hf {
	/** @brief maze
	 *
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
		private:
			bool			init_hf_;
	};
}}}

#endif

