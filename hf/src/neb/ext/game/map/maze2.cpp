
//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>

#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/HeightField/desc.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#define D 3

typedef neb::fnd::game::map::Base		T0;
typedef neb::mod::hf::Base			T1;

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
	init_hf_(false)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void		T1::init(parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	
	auto self(std::dynamic_pointer_cast<T1>(shared_from_this()));

	setParent(p);

	// init scene
	neb::fnd::game::map::Base::init(p);

	// insert a spawn point at origin
	// ?

	// create heightfield

	if(!init_hf_)
	{
		auto actor = _M_scene->createActorRigidStaticUninitialized().lock();
		actor->pose_.pos_ = glm::vec3(0,0,0);
		actor->init(this);

		neb::fnd::core::shape::HeightField::desc d;
		d.w = 50.0;
		d.h = 50.0;
		d.r = 128;
		d.c = 128;
		d.hs = 10.0;
		d.fc.push_back(0.2);
		d.fc.push_back(0.2);
		
		actor->createShapeHeightField(d);

		// light
		_M_scene->createActorLightPoint(glm::vec3(
					0.0 * d.w / 2.0,
					0.0,
					0.0 * d.h / 2.0));
/*		createActorLightPoint(glm::vec3(
					d.w / 2.0,
					8.0,
					d.h / 2.0));*/
/*		createActorLightPoint(glm::vec3(
					d.w / 2.0,
					-50.0,
					d.h / 2.0));
*/
		init_hf_ = true;
	}
}
void		T1::Base::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	neb::fnd::game::map::base::release();
	neb::fin::core::scene::base::release();
}
void		T1::Base::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	//neb::game::map::base::step(ts);
	//neb::phx::game::map::base::step(ts);
	neb::fin::core::scene::base::step(ts);

}



