
#include <neb/phx/core/scene/util/decl.hpp>

#include <neb/fin/gfx_phx/core/scene/util/parent.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

neb::ext::maze::game::map::maze2::maze2(
		shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent,
		ivec2 size):
	neb::core::core::scene::base(parent),
	neb::game::map::base(parent),
	neb::phx::core::scene::base(parent),
	neb::phx::game::map::base(parent),
	neb::gfx::core::scene::base(parent),
	neb::fin::gfx_phx::core::scene::base(parent)
{
}
void		neb::ext::maze::game::map::maze2::init() {
	neb::phx::game::map::base::init();
	neb::ext::maze::game::map::maze2::init();
}

