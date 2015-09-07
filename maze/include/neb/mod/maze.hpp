#ifndef NEB_MOD_MAZE_HPP
#define NEB_MOD_MAZE_HPP

#include <neb/fnd0/game/map/base.hpp>

namespace neb { namespace mod { namespace maze {
	/** @brief Base
	 */
	class Base:
		virtual public gal::enable_shared_from_this<neb::mod::maze::Base>,
		virtual public neb::fnd0::game::map::Base
	{
		public:
			using gal::enable_shared_from_this<neb::mod::maze::Base>::shared_from_this;

			typedef std::shared_ptr<neb::fnd0::core::actor::Base> S_A;

			Base();
			virtual ~Base();
			virtual void		setup();
			virtual void		release();
 			virtual S_A		v_create_player_actor(
					std::shared_ptr<neb::fnd0::window::Base> w,
					std::shared_ptr<neb::fnd0::environ::Base> e);
			virtual void		v_set_player_actor(S_A a);

			glm::ivec3		size_;
	};
}}}

#endif
