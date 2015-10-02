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
#include <neb/fnd0/core/actor/rigiddynamic/Base.hpp>
#include <neb/fnd0/core/actor/rigidbody/Base.hpp>
#include <neb/fnd0/core/actor/rigidbody/desc.hpp>
#include <neb/fnd0/core/actor/vehicle/drive4w/Base.hpp>
#include <neb/fnd0/core/shape/cuboid/desc.hpp>
#include <neb/fnd0/core/shape/HeightField/desc.hpp>
#include <neb/fnd0/core/scene/Base.hpp>
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
T1::Base()
{
}
T1::~Base()
{
}
void		T1::setup()
{
	printv_func(DEBUG);

	auto scene = create_scene();

	scene->set_gravity(glm::vec3(0,1.0,0));

	auto self = shared_from_this();

	printv(DEBUG, "make inner walls\n");
		
	//glm::vec3 offset(0,0,-100);
	glm::vec3 offset(0,0,0);

	// outer walls
	printv(DEBUG, "make outer walls\n");
	
	gal::math::pose pose(glm::vec3(0,15,0));

	glm::vec3 s(100,1,100);

	scene->createActorRigidStaticCuboid(pose, s);

	printv(DEBUG, "create light\n");

	scene->createActorLightPoint(glm::vec3(0,0,0));

	_M_veh = std::dynamic_pointer_cast<neb::fnd0::core::actor::vehicle::drive4w::Base>(
			scene->create_actor_vehicle_drive_4w());






	// heightfield

	auto actor = scene->createActorRigidStaticUninitialized();
	//auto actor = scene->createActorRigidStatic();
	actor->pose_.pos_ = glm::vec3(100,100,0);
	//actor->init(scene.get());

	neb::fnd0::core::shape::HeightField::desc d;
	d.w = 50.0;
	d.h = 50.0;
	d.r = 128;
	d.c = 128;
	d.hs = 10.0;
	d.fc.push_back(0.2);
	d.fc.push_back(0.2);

	actor->createShapeHeightField(d);
	
	actor->init(scene.get());

	// light
	scene->createActorLightPoint(glm::vec3(
				0.0 * d.w / 2.0,
				0.0,
				0.0 * d.h / 2.0));










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

	// control
	auto control = _M_veh->create_control(w);

	if(e) {
		auto e1 = e->is_fnd_environ_scenedefault();
		//e1->create_view_ridealong(a);
		assert(_M_veh);
		printf("mod veh actor    %p\n", _M_veh.get());
		auto a1 = _M_veh->_M_actor_rd.lock();
		printf("mod veh actor_rd %p\n", a1.get());
		assert(a1);
		e1->create_view_ridealong(a1);
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


