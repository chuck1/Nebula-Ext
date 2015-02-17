#include <maze/dfs.hpp>

#include <neb/core/core/scene/util/parent.hpp>

#include <neb/mod/maze.hpp>

#define D 3

typedef neb::fnd::game::map::Base		T0;
typedef neb::mod::maze::Base			T1;

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
T1::Base():
	size_(6)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void		T1::init(parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	assert(_M_scene);

	auto self(std::dynamic_pointer_cast<T1>(shared_from_this()));

	// insert a spawn point at origin
	// and init scene
	neb::fnd::game::map::Base::init(p);

	::maze::description<D> desc(size_);
	::maze::dfs<D> m(desc);
	m.run();

	float width = 5.0;

	auto lambda = [&] (::maze::traits<D>::vec v)
	{
		auto actor = _M_scene->createActorRigidStaticCube(neb::fnd::math::pose(v), width);
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
		_M_scene->createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
		pos[d] = (float)desc.size_[0];
		_M_scene->createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
	}

	_M_scene->createActorLightPoint(glm::vec3(0,0,10));
}
void		T1::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::fnd::game::map::Base::release();
}
void		T1::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//neb::game::map::base::step(ts);
	//neb::phx::game::map::base::step(ts);
}

