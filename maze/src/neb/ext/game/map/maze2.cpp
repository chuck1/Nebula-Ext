#include <maze/dfs.hpp>

#include <neb/phx/core/scene/util/parent.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

typedef neb::fin::core::scene::base		T0;
typedef neb::ext::maze::game::map::base		T1;

typedef neb::ext::maze::game::map::base		THIS;

extern "C" T0*	scene_create()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new T1;
}
extern "C" void	scene_destroy(T0* t)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	delete t;
}

THIS::base():
	size_(6)
{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
}

#define D 3

void		THIS::init(parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	
	auto self(std::dynamic_pointer_cast<THIS>(shared_from_this()));

	// insert a spawn point at origin
	// and init scene
	nc::game::map::base::init(p);
	neb::fin::core::scene::base::init(p);
	
	::maze::description<D> desc(size_);
	::maze::dfs<D> m(desc);
	m.run();
	
	float width = 5.0;
	
	auto lambda = [&] (::maze::traits<D>::vec v) {
		auto actor = createActorRigidStaticCube(neb::fnd::math::pose(v), width);
	};
	
	for(int i = 0; i < prod<D>(desc.size_); ++i) {

		auto v = ::vector<D>(i, desc.size_);

		if(!m.get_ispath(v)) {

			lambda(::maze::traits<D>::vec(v) * (float)width);

		}
	}

	// outer walls
	glm::vec3 pos;
	glm::vec3 s;

	for(int d = 0; d < D; d++)
	{
		pos = glm::vec3(
				((float)desc.size_[1] - 1.0) / 2.0,
				((float)desc.size_[1] - 1.0) / 2.0,
				((float)desc.size_[2] - 1.0) / 2.0
			     );

		s = glm::vec3(desc.size_);

		s[d] = 1.0;

		pos[d] = -1;
		createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
		pos[d] = (float)desc.size_[0];
		createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
	}

	createActorLightPoint(glm::vec3(0,0,10));
}
void		THIS::release() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	nc::game::map::base::release();
	neb::fin::core::scene::base::release();

}
void		THIS::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	//neb::game::map::base::step(ts);
	//neb::phx::game::map::base::step(ts);
	neb::fin::core::scene::base::step(ts);

}



