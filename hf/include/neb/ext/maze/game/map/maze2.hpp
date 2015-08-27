#ifndef NEBULA_MOD_HF_BASE_HPP
#define NEBULA_MOD_HF_BASE_HPP

#include <neb/fnd0/game/map/base.hpp>

#include <neb/fnd0/game/map/base.hpp>

namespace neb { namespace mod { namespace hf {
	/** @brief maze
	 *
	 */
	class Base:
		virtual public gal::enable_shared_from_this<neb::mod::hf::Base>,
		virtual public neb::fnd0::game::map::Base
	{
		public:
			using gal::enable_shared_from_this<neb::mod::hf::Base>::shared_from_this;

			Base();
			virtual ~Base();
			virtual void		setup();
			virtual void		release();
			virtual void		step(gal::etc::timestep const &);
			virtual void		v_create_player_actor(
					std::shared_ptr<neb::fnd0::window::Base> w,
					std::shared_ptr<neb::fnd0::environ::Base> e);
		private:
			bool			init_hf_;
	};
}}}

#endif

