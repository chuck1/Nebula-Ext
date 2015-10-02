
//#include <neb/fnd0/shape/Box.hh>
//#include <neb/fnd0/actor/RigidStatic/local.hpp>
#include <neb/fnd0/context/Window.hpp>
#include <neb/fnd0/environ/SceneDefault.hpp>
#include <neb/fnd0/environ/Two.hpp>
#include <neb/fnd0/net/comm/util/Parent.hpp>
#include <neb/fnd0/net/client/Base.hpp>
#include <neb/fnd0/net/msg/Code.hpp>
#include <neb/fnd0/net/msg/game/game/List.hpp>
#include <neb/fnd0/core/actor/rigidbody/Base.hpp>
#include <neb/fnd0/core/actor/rigidbody/desc.hpp>
#include <neb/fnd0/core/shape/cuboid/desc.hpp>
#include <neb/fnd0/window/util/Parent.hpp>
#include <neb/fnd0/window/Base.hpp>
#include <neb/fnd0/app/Base00.hpp>
#include <neb/fnd0/game/map/util/Parent.hpp>
#include <neb/fnd0/game/weapon/desc/SimpleProjectile.hpp>
#include <neb/fnd0/core/actor/Base.hpp>
#include <neb/fnd0/core/shape/HeightField/desc.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#define D 3

typedef neb::fnd0::game::map::Base		T0;
typedef neb::mod::hf::Base			T1;

extern "C" T0*	map_create()
{
	return new T1;
}
extern "C" void	map_destroy(T0* t)
{
	delete t;
}

T1::Base():
	init_hf_(false)
{
}
T1::~Base()
{
}
void		T1::setup()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	auto self = shared_from_this();

	auto scene = create_scene();

	// insert a spawn point at origin
	// ?

	// create heightfield

	if(!init_hf_) {
		auto actor = scene->createActorRigidStaticUninitialized();
		//auto actor = scene->createActorRigidStatic();
		actor->pose_.pos_ = glm::vec3(0,-10,0);
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

	neb::fnd0::game::map::Base::release();
}
void		T1::Base::step(gal::etc::timestep const & ts)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	neb::fnd0::game::map::Base::step(ts);
}
T1::S_A			T1::Base::v_create_player_actor(
		std::shared_ptr<neb::fnd0::window::Base> w,
		std::shared_ptr<neb::fnd0::environ::Base> e)
{
	neb::fnd0::core::actor::rigidbody::Desc ad;
	ad.pose.pos_.x = -10.0;
	ad.pose.pos_.z =  10.0;
	neb::fnd0::core::shape::cuboid::Desc sd;

	auto scene = P_SC::front();

	typedef neb::fnd0::core::actor::rigidbody::Base T;

	// weapon desc
	typedef nf0::game::weapon::desc::SimpleProjectile WD;
	std::shared_ptr<WD> wd(new WD);
	wd->_M_size = 0.2;
	wd->_M_damage = 10.0;
	wd->_M_velocity = 5.0;

	ad._M_weapons.push_back(wd);

	// actor

	auto actor_player = std::dynamic_pointer_cast<T>(
			scene->createActorRigidDynamicCuboid(ad, sd, w));
	
	gal::math::pose light_pose;
	auto light_shape = actor_player->createShapeBase(light_pose);
	light_shape->createLightPoint();

	//auto weap = actor_player->create_weapon_simpleprojectile(
	//		w, 0.2, 10.0, 5.0);

	auto control = actor_player->createControlManual(w);

	if(e) {
		auto e1 = e->is_fnd_environ_scenedefault();
		e1->create_view_ridealong(actor_player);
	}

	return actor_player;
}
void			T1::v_set_player_actor(S_A a)
{
	assert(a);

	auto app = get_fnd_app();

	auto w0 = app->get_parent_window()->front();

	if(!w0) return;

	auto c0 = w0->P_C::front();

	auto e0 = c0->P_E::front();

	auto e1 = e0->is_fnd_environ_scenedefault();

	e1->create_view_ridealong(a);
}


