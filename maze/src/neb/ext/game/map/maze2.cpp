#include <maze/dfs.hpp>

#include <neb/fnd/core/scene/util/parent.hpp>

#include <neb/mod/maze.hpp>

#define D 3

typedef neb::fnd::game::map::Base		T0;
typedef neb::mod::maze::Base			T1;

extern "C" T0*	map_create()
{
	return new T1;
}
extern "C" void	map_destroy(T0* t)
{
	delete t;
}
T1::Base():
	size_(3)
{
	printv_func(DEBUG);
}
T1::~Base()
{
	printv_func(DEBUG);
}
void		T1::setup()
{
	printv_func(DEBUG);

	auto scene = get_scene();

	auto self = shared_from_this();

	::maze::description<D> desc(size_);
	::maze::dfs<D> m(desc);
	m.run();

	float width = 5.0;

	printv(DEBUG, "make inner walls\n");
		
	//glm::vec3 offset(0,0,-100);
	glm::vec3 offset(0,0,0);

	auto lambda = [&] (::maze::traits<D>::vec p)
	{
		printv(DEBUG, "mod: p = %16f %16f %16f\n", p.x, p.y, p.z);
		auto actor = scene->createActorRigidStaticCube(gal::math::pose(p), width);
	};

	for(int i = 0; i < prod<D>(desc.size_); ++i) {
		auto v = ::vector<D>(i, desc.size_);

		glm::vec3 pos = ::maze::traits<D>::vec(v) * (float)width + offset;

		if(m.get_ispath(v)) {
			// path
			printv(DEBUG, "create_spawn\n");
			create_spawn(gal::math::pose(pos));

			// random lights
			if((rand() % 5) == 0)
				scene->createActorLightPoint(pos);


		} else {
			// wall
			lambda(pos);
		}
	}
	
	// outer walls
	printv(DEBUG, "make outer walls\n");

	glm::vec3 pos;
	glm::vec3 s;

	for(int d = 0; d < 3; d++)
	{
		pos = glm::vec3(
				((float)desc.size_[0] - 1.0) / 2.0,
				((float)desc.size_[1] - 1.0) / 2.0,
				((float)desc.size_[2] - 1.0) / 2.0
			       );
		
		s = glm::vec3(desc.size_);
		
		s[d] = 1.0;
		
		pos[d] = -1;
		scene->createActorRigidStaticCuboid(gal::math::pose((pos * width) + offset), s * width);

		pos[d] = (float)desc.size_[d];
		scene->createActorRigidStaticCuboid(gal::math::pose((pos * width) + offset), s * width);
	}

	printv(DEBUG, "create light\n");

	scene->createActorLightPoint(glm::vec3(0,0,10));

	printv(DEBUG, "setup complete\n");
}
void		T1::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::fnd::game::map::Base::release();
}


