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

			typedef gal::weak_ptr<neb::fnd0::core::actor::Base> W_A;

			Base();
			virtual ~Base();
			virtual void		setup();
			virtual void		release();
			virtual void		step(gal::etc::timestep const &);
			virtual S_A		v_create_player_actor(
					std::shared_ptr<neb::fnd0::window::Base> w,
					std::shared_ptr<neb::fnd0::environ::Base> e);
			virtual void		v_set_player_actor(S_A);
		private:
			bool			init_hf_;
	};
}}}

#endif

