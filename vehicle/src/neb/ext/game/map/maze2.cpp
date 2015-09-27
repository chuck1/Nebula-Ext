#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>
#include <gal/etc/stopwatch.hpp>

#include <neb/fnd0/context/Window.hpp>
#include <neb/fnd0/environ/SceneDefault.hpp>
#include <neb/fnd0/environ/Two.hpp>
#include <neb/fnd0/environ/SceneDefault.hpp>
#include <neb/fnd0/net/client/Base.hpp>
#include <neb/fnd0/net/comm/util/Parent.hpp>
#include <neb/fnd0/net/msg/Code.hpp>
#include <neb/fnd0/net/msg/game/game/List.hpp>
#include <neb/fnd0/core/actor/rigidbody/Base.hpp>
#include <neb/fnd0/core/actor/rigidbody/desc.hpp>
#include <neb/fnd0/core/shape/cuboid/desc.hpp>
#include <neb/fnd0/window/util/Parent.hpp>
#include <neb/fnd0/window/Base.hpp>
#include <neb/fnd0/app/Base00.hpp>
#include <neb/fnd0/core/scene/util/parent.hpp>
#include <neb/fnd0/game/map/util/Parent.hpp>
#include <neb/fnd0/game/weapon/SimpleProjectile.hpp>
#include <neb/fnd0/game/weapon/desc/SimpleProjectile.hpp>

#include <neb/mod/vehicle.hpp>

#define D 3

typedef neb::fnd0::game::map::Base		T0;
typedef neb::mod::vehicle::Base			T1;

extern "C" T0*	map_create()
{
	return new T1;
}
extern "C" void	map_destroy(T0* t)
{
	delete t;
}
T1::Base():
	size_(2)
{
}
T1::~Base()
{
}
void		T1::setup()
{
	printv_func(DEBUG);

	auto scene = create_scene();

	auto self = shared_from_this();

	printv(DEBUG, "make inner walls\n");
		
	//glm::vec3 offset(0,0,-100);
	glm::vec3 offset(0,0,0);

	// outer walls
	printv(DEBUG, "make outer walls\n");
	
	gal::math::pose pose(glm::vec3(0,0,-10));

	glm::vec3 s(100,100,1);

	scene->createActorRigidStaticCuboid(pose, s);

	printv(DEBUG, "create light\n");

	scene->createActorLightPoint(glm::vec3(0,0,0));

	printv(DEBUG, "setup complete\n");
}
void		T1::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::fnd0::game::map::Base::release();
}
T1::S_A			T1::Base::v_create_player_actor(
		std::shared_ptr<neb::fnd0::window::Base> w,
		std::shared_ptr<neb::fnd0::environ::Base> e)
{
	neb::fnd0::core::actor::rigidbody::Desc ad;
	neb::fnd0::core::shape::cuboid::Desc sd;
	
	auto scene = P_SC::front();


	// weapon desc
	typedef nf0::game::weapon::desc::SimpleProjectile WD;
	std::shared_ptr<WD> wd(new WD);
	wd->_M_size = 0.2;
	wd->_M_damage = 10.0;
	wd->_M_velocity = 5.0;

	ad._M_weapons.push_back(wd);

	// actor
	typedef neb::fnd0::core::actor::rigidbody::Base T;

	auto a = std::dynamic_pointer_cast<T>(
			scene->createActorRigidDynamicCuboid(ad, sd, w));

	a->flag_.set(neb::fnd0::core::actor::util::flag::E::DESTRUCTIBLE);

	spawn_actor(a);
	
	// weapon
	//auto weap = a->create_weapon_simpleprojectile(w, 0.2, 10.0, 5.0);
	//printv(INFO, "create player weapon\n");
	//weap->print_index_table();
	
	auto control = a->createControlManual(w);

	if(e) {
		auto e1 = e->is_fnd_environ_scenedefault();
		e1->create_view_ridealong(a);
	}

	return a;
}
void			T1::v_set_player_actor(T1::S_A a)
{
	assert(a);

	auto app = get_fnd_app();

	auto w0 = app->get_parent_window()->front();
	
	if(!w0) return;
	
	auto c0 = w0->P_C::front();
	
	typedef neb::fnd0::environ::util::Parent P_E;
	
	auto l = [] (P_E::S s) {
		return bool(s->is_fnd_environ_scenedefault());
	};
	
	auto e0 = c0->P_E::front(l);
	
	assert(e0);
	
	auto e1 = e0->is_fnd_environ_scenedefault();
	
	assert(e1);
	
	e1->create_view_ridealong(a);


	// weapon
	// NO! created and sent by server
	//a->create_weapon_simpleprojectile(
	//		w0, 0.1, 0.1, 1.0);
	
	auto weap = a->P_W::front();
	assert(weap);
	weap->connect(w0);
}


