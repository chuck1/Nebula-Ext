
//#include <neb/core/shape/Box.hh>
//#include <neb/core/actor/RigidStatic/local.hpp>

#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/HeightField/desc.hpp>
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
	neb::fin::gfx_phx::core::scene::base(parent)
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


	// create heightfield
	
	auto actor = createActorRigidStaticUninitialized().lock();
	actor->pose_.pos_ = glm::vec3(0,0,-20);
	actor->init();

	actor->createShapeHeightField(neb::core::core::shape::HeightField::desc());

	// light
	createActorLightPoint(glm::vec3(0,0,10));
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


