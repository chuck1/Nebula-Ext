#ifndef NEBULA_MOD_HF_BASE_HPP
#define NEBULA_MOD_HF_BASE_HPP

#include <neb/fnd/game/map/base.hpp>

#include <neb/fnd/game/map/base.hpp>

namespace neb { namespace mod { namespace hf {
	/** @brief maze
	 *
	 */
	class Base:
		virtual public gal::enable_shared_from_this<neb::mod::hf::Base>,
		virtual public neb::fnd::game::map::Base
	{
		public:
			using gal::enable_shared_from_this<neb::mod::hf::Base>::shared_from_this;

			Base();
			virtual ~Base();
			virtual void		setup();
			virtual void		release();
			virtual void		step(gal::etc::timestep const &);
		private:
			bool			init_hf_;
	};
}}}

#endif

