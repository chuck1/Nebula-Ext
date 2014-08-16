
#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <neb/core/app/__base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/Camera/View/ridealong.hh>

#include <neb/core/game/map/base.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/game/game/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/gfx_phx/app/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::fin::gfx_phx::app::base::global();
	
	auto layout = app->createLayout().lock();

	context->environ_->drawable_ = layout;

	layout->connect(window);

	layout->createObjectTerminal();

	return layout;
}
shared_ptr<neb::phx::core::actor::rigiddynamic::base>		create_actor_dynamic(shared_ptr<neb::fin::gfx_phx::core::scene::base> scene, neb::core::pose pose, double size,
		const char * texture_filename)
{
	auto actor = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			scene->createActorRigidDynamicUninitialized().lock()
			);

	actor->pose_ = pose;

	actor->flag_.set(neb::core::core::actor::util::flag::DESTRUCTIBLE);
	
	actor->init();

	// shape

	auto shape = dynamic_pointer_cast<neb::fin::gfx_phx::core::shape::box>(
			actor->createShapeCube(neb::core::pose(), size).lock()
			);
	
	actor->setupFiltering();

	// texture
	if(texture_filename) {

		shape->mesh_->material_front_.raw_.diffuse_ = neb::Color::color<float>(1,1,1,1);

		shape->mesh_->texture_.reset(new neb::gfx::texture);
		shape->mesh_->texture_->load_png(texture_filename);
	}
	return actor;
}
weak_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>		create_actor_ai(shared_ptr<neb::fin::gfx_phx::core::scene::base> scene) {
	
	auto actor = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			scene->createActorRigidDynamicUninitialized().lock()
			);

	actor->flag_.set(neb::core::core::actor::util::flag::DESTRUCTIBLE);

	actor->init();

	// shape	
	auto shape = actor->createShapeCube(neb::core::pose(), 1.0);

	actor->setupFiltering();

	actor->setGlobalPosition(vec3(0,0,5));

	auto pxrd = actor->px_actor_->isRigidDynamic();

	pxrd->setLinearDamping(5.0);
	pxrd->setAngularDamping(3.0);

	// control

	auto control(make_shared<neb::phx::core::actor::control::rigidbody::pd>());

	actor->control_ = control;

	control->actor_ = actor;//->isPxActorRigidBodyBase();

	// target
	control->p_target_ = vec3(0,0,5);

	control->q_target_ = glm::angleAxis(1.5f, vec3(0.0,1.0,0.0));
	
	return actor;	
}
shared_ptr<neb::fin::gfx_phx::core::scene::base>			create_scene(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context,
		shared_ptr<neb::fin::gfx_phx::core::actor::base>& enemy)
{

	auto app = neb::fin::gfx_phx::app::base::global();
	assert(app);
	

	auto scene = app->createScene().lock();

	// actors
	
	//create_actor_dynamic(scene, neb::core::pose(vec3(-5, 0, 0)), 1.0, 0);
	create_actor_dynamic(scene, neb::core::pose(vec3(-5, 0, 0)), 1.0, "/nfs/stak/students/r/rymalc/Documents/Pictures/crab.png");
	//scene->createActorRigidStaticCube(neb::core::pose(vec3(-5, 0, 0)), 1.0);

	scene->createActorRigidStaticCube(neb::core::pose(vec3( 5, 0, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0,-5, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 5, 0)), 1.0);
	auto static_cube5 = scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0,-5)), 1.0).lock();

	// testing for multiple inheritance
	auto test = static_cube5->gal::std::shared::name();


	//scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0, 5)), 1.0);

	// player's actor
	auto actor3 = create_actor_dynamic(scene, neb::core::pose(), 1.0, 0);
	actor3->setGlobalPosition(vec3(0,0,0));

	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	scene->createActorLightPoint(vec3());
	scene->createActorLightPoint(vec3(10,0,0));

	context->environ_->drawable_ = scene;

	// connect actor

	actor3->create_control(window);

/*	auto cam = make_shared<neb::gfx::Camera::View::Ridealong>(context->environ_, actor3);

	cam->actor_ = actor3;

	auto e3 = context->environ_->isEnvironThree();
	assert(e3);

	e3->view_ = cam;*/


	context->environ_->isEnvironThree()->createViewRidealong(actor3);



	// game
	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::phx::game::game::util::parent::insert(game);

	// ai
	enemy = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(create_actor_ai(scene).lock());

	// weapon
	enemy->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	auto ai(sp::make_shared<neb::phx::game::ai::base>());

	game->neb::phx::game::ai::util::parent::insert(ai);

	ai->actor_ = enemy;
	ai->target_ = actor3;

	return scene;
}
shared_ptr<neb::phx::game::map::base>			create_maze(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::fin::gfx_phx::app::base::global();

	auto map = make_shared<neb::ext::maze::game::map::maze2>(app, ivec2(15,15));

	app->neb::phx::core::scene::util::parent::insert(map);

	map->init();

	// player's actor
	auto actor3 = create_actor_dynamic(map, neb::core::pose(), 1.0, 0);
	actor3->setGlobalPosition(vec3(0,0,0));

	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	map->createActorLightPoint(vec3());
	map->createActorLightPoint(vec3(10,0,0));

	// give scene to context

	context->environ_->drawable_ = map;

	// camera

	actor3->create_control(window);

	context->environ_->isEnvironThree()->createViewRidealong(actor3);

	return map;
}
weak_ptr<neb::phx::game::game::base>		create_game() {

	auto app(neb::phx::app::base::global());

	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::game::game::util::parent::insert(game);


	return game;
}
void						setup_game(
		shared_ptr<neb::phx::game::game::base> game,
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context)
{
	// scene
	shared_ptr<neb::fin::gfx_phx::core::actor::base> enemy;

	auto scene = create_scene(window, context, enemy);

	game->scene_ = scene;

	// trigger
	auto trig(make_shared<neb::game::trigger::ActorEx1>(game));

	game->neb::game::trigger::util::parent::insert(trig);

	trig->connect(enemy);

	cout << "game use count " << game.use_count() << endl;
}
int			main() {

	auto app = neb::fin::gfx_phx::app::base::init();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = window->createContextThree().lock();
	auto context2 = window->createContextTwo().lock();

	// game
	auto game = create_game().lock();

	// create drawables
	//shared_ptr<neb::fin::gfx_phx::core::actor::base> enemy;
	
	//auto scene = create_scene(window, context1, enemy);
	
	setup_game(game, window, context1);

	auto layout = create_layout(window, context2);

	app->loop();
}



