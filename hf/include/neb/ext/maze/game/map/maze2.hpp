#ifndef NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP
#define NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP

#include <neb/core/game/map/base.hpp>

#include <neb/phx/game/map/base.hpp>

#include <neb/fin/gfx_phx/core/scene/base.hpp>

namespace neb {
	namespace ext {
		namespace maze {
			namespace game {
				namespace map {
					/** @brief maze
					 *
					 */
					class base:
						virtual public neb::game::map::base,
						virtual public neb::phx::game::map::base,
						virtual public neb::fin::gfx_phx::core::scene::base
					{
						public:
							base(shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent);
							virtual ~base() {}
									
							virtual void		init();
							virtual void		release();
							virtual void		step(gal::etc::timestep const &);
					};
				}
			}
		}
	}
}

#endif

