#include <maze/dfs.hpp>

//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>

#include <neb/phx/core/scene/util/parent.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

typedef neb::fin::gfx_phx::core::scene::base	T0;
typedef neb::ext::maze::game::map::base		T1;

extern "C" T0*	scene_create(shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new T1(parent);
}
extern "C" void	scene_destroy(T0* t)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	delete t;
}

neb::ext::maze::game::map::base::base(
		shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent),
	neb::game::map::base(parent),
	neb::phx::core::scene::base(parent),
	neb::phx::game::map::base(parent),
	neb::fin::gfx_phx::core::scene::base(parent),
	size_(6)
{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
}

#define D 3

void		neb::ext::maze::game::map::base::init() {
	
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	
	auto self(std::dynamic_pointer_cast<neb::ext::maze::game::map::base>(shared_from_this()));

	// insert a spawn point at origin
	// and init scene
	neb::game::map::base::init();
	neb::fin::gfx_phx::core::scene::base::init();
	
	::maze::description<D> desc(size_);
	::maze::dfs<D> m(desc);
	m.run();
	
	float width = 5.0;
	
	auto lambda = [&] (::maze::traits<D>::vec v) {
		auto actor = createActorRigidStaticCube(neb::core::pose(v), width);
	};
	
	for(int i = 0; i < prod<D>(desc.size_); ++i) {

		auto v = ::vector<D>(i, desc.size_);

		if(!m.get_ispath(v)) {

			lambda(::maze::traits<D>::vec(v) * (float)width);

		}
	}

	// outer walls
	glm::vec3 p;
	glm::vec3 s;

	for(int d = 0; d < D; d++)
	{
		p = glm::vec3(
				((float)desc.size_[1] - 1.0) / 2.0,
				((float)desc.size_[1] - 1.0) / 2.0,
				((float)desc.size_[2] - 1.0) / 2.0
			     );

		s = glm::vec3(desc.size_);

		s[d] = 1.0;

		p[d] = -1;
		createActorRigidStaticCuboid(neb::core::pose(p * width), s * width);
		p[d] = (float)desc.size_[0];
		createActorRigidStaticCuboid(neb::core::pose(p * width), s * width);
	}
}
void		neb::ext::maze::game::map::base::release() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::game::map::base::release();
	neb::phx::game::map::base::release();
	neb::fin::gfx_phx::core::scene::base::release();

}
void		neb::ext::maze::game::map::base::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	//neb::game::map::base::step(ts);
	//neb::phx::game::map::base::step(ts);
	neb::fin::gfx_phx::core::scene::base::step(ts);

}



