#include <maze/dfs.hpp>


#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/fnd0/context/Window.hpp>
#include <neb/fnd0/environ/SceneDefault.hpp>
#include <neb/fnd0/environ/Two.hpp>
#include <neb/fnd0/environ/SceneDefault.hpp>
#include <neb/fnd0/net/client/Base.hpp>
#include <neb/fnd0/net/msg/Code.hpp>
#include <neb/fnd0/net/msg/game/game/List.hpp>
#include <neb/fnd0/core/actor/rigidbody/Base.hpp>
#include <neb/fnd0/core/actor/rigidbody/desc.hpp>
#include <neb/fnd0/core/shape/cuboid/desc.hpp>

#include <neb/fnd0/app/Base10.hpp>
#include <neb/fnd0/core/scene/util/parent.hpp>
#include <neb/fnd0/game/map/util/Parent.hpp>

#include <neb/mod/maze.hpp>

#define D 3

typedef neb::fnd0::game::map::Base		T0;
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
		scene->createActorRigidStaticCuboid(
				gal::math::pose((pos * width) + offset), s * width);

		pos[d] = (float)desc.size_[d];
		scene->createActorRigidStaticCuboid(
				gal::math::pose((pos * width) + offset), s * width);
	}

	printv(DEBUG, "create light\n");

	scene->createActorLightPoint(glm::vec3(0,0,10));

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
	
	auto actor_player = std::dynamic_pointer_cast<neb::fnd0::core::actor::rigidbody::Base>(
			scene->createActorRigidDynamicCuboid(ad, sd).lock());
	
	spawn_actor(actor_player);
	
	auto weap = actor_player->createWeaponSimpleProjectile(w, 0.2, 10.0, 5.0);
	
	auto control = actor_player->createControlManual(w);

	if(e) {
		auto e1 = e->is_fnd_environ_scenedefault();
		e1->create_view_ridealong(actor_player);
	}

	return actor_player;
}
void			T1::v_set_player_actor(
		std::shared_ptr<neb::fnd0::core::actor::Base> a)
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
	a->createWeaponSimpleProjectile(w0.lock(), 0.1, 0.1, 1.0);
}


