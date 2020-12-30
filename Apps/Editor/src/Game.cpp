#include "Game.hpp"

#include <iostream>

#include "Log.hpp"

#include <NLS-Engine/IO/KeyBindingSet.hpp>
#include <NLS-Engine/IO/InputManager.hpp>
#include <NLS-Engine/Core/Engine.hpp>


#include <NLS-Engine/ECS/ECSManager.hpp>
#include <NLS-Engine/ECS/ComponentHandler.hpp>

//struct Position {
//    int x = 0;
//    int y= 0;
//    int z = 0;
//};

struct Pos2D {
    float x = 0;
    float y = 0;
};

struct Speed {
    float speedX = 2.5f;
    float speedY = 2.5f;
};

struct BenchPosition {
    float x;
    float y;

    BenchPosition(int _x, int _y) : x(_x), y(_y) { }
};

struct BenchDirection {
    float x;
    float y;
};

struct Health {
    int health = 0;
};


//struct Renderable {
//   bool isRenderable = true;
//};

struct ComflabulationComponent {
    float thingy;
    int dingy;
    bool mingy;
    std::string stringy;
};





void Game::Callback(const NLS::EVENT::OnWinFocusChangedEvent &test) {
    NLSLOG::Info("Game", "Win Focus Changed! {}", (void*)test.GetActiveWindow());
}

void Game::Callback1(const NLS::EVENT::OnWinFocusChangedEvent &test) {
    NLSLOG::Info("Game", "Win Focus Changed one!");
}

void Game::OnKeyPressed(const NLS::EVENT::OnKeyPressedEvent &test) {
    NLSLOG::Info("Game", "Key pressed!");
}

Game::Game() {

}

void Game::OnCreate() {
    static std::chrono::steady_clock mytimer; 
    static std::chrono::steady_clock::time_point myoldTime;
    static std::chrono::duration<float, std::milli> mydeltaTime;

    //std::unique_ptr<NLS::INPUT::KeyBindingSet> mySet = std::make_unique<NLS::INPUT::KeyBindingSet>(
    //            std::initializer_list<std::string>({"Jump", "Shoot", "Lurch"}));
    NLS::INPUT::KeyBindingSet mySet { "Jump", "Shoot", "Lurch" };

    //Engine::GetEngine().GetInputManager().LoadActiveKeybindingSet(std::make_unique<NLS::INPUT::KeyBindingSet>(
    //            std::initializer_list<std::string>({"Jump", "Shoot", "Lurch"})));
    //NLS::INPUT::InputManager::LoadActiveKeybindingSet(mySet);
    Engine::GetEngine().GetInputManager().LoadActiveKeybindingSet(mySet);

    // Event Testing
    mWindow = Engine::GetEngine().GetWindowManager().ConstructWindow("First Window");
    mSecondWindow = Engine::GetEngine().GetWindowManager().ConstructWindow("Second Window");
    NLS::EVENT::OnWinFocusChangedEvent myEvent(mWindow.lock()->GetGLFWWindowInstance());
    NLS::EVENT::OnKeyPressedEvent eventKey;

    RegisterForEvent<NLS::EVENT::OnWinFocusChangedEvent>(std::bind(&Game::Callback, this, std::placeholders::_1), false);
    RegisterForEvent<NLS::EVENT::OnKeyPressedEvent>(std::bind(&Game::OnKeyPressed, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);
    SendBlockingEvent(eventKey);

    RegisterForEvent<NLS::EVENT::OnWinFocusChangedEvent>(std::bind(&Game::Callback1, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);
    SendBlockingEvent(eventKey);

    UnregisterForEvent<NLS::EVENT::OnKeyPressedEvent>(std::bind(&Game::OnKeyPressed, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);

    QueueNewEvent(myEvent);


    // ECS Testing
    ECSManager manager;

    // Start by creating Component Handlers. 
    manager.CreateComponentHandler<Position>();
    manager.CreateComponentHandler<Health>();
    manager.CreateComponentHandler<Renderable>();
    manager.CreateComponentHandler<Speed>();
    manager.CreateComponentHandler<Pos2D>();

    manager.CreateComponentHandler<BenchPosition>();
    manager.CreateComponentHandler<BenchDirection>();
    manager.CreateComponentHandler<ComflabulationComponent>();
    
    for (uint64_t entity = 0; entity < 100000; entity++) {
        manager.AddComponentToEntity<Pos2D>(entity);
        manager.AddComponentToEntity<Speed>(entity);


        //if (entity % 5 == 0) {
		//    manager.AddComponentToEntity<Health>(entity);
	    //}
    }

    myoldTime = mytimer.now();

    //manager.AddComponentToEntity<Health>(0xFFF);
    //manager.AddComponentToEntity<Health>(0x21);
    //manager.AddComponentToEntity<Health>(0xFF4D111);
    
    // These are examples of O(1) lookups with unordered_flat_maps, I think. 
    // Because they are flat maps, these lookups should be cache friendly. 
    /*
    auto elementList = manager.GetEntitiesWithComponents<BenchPosition, BenchDirection>();
    //auto bab = elementList->size();
    for(EntityID element : *elementList) {
        auto &elementPos = manager.GetComponent<BenchPosition>(element);
        auto &elementDir = manager.GetComponent<BenchDirection>(element);

        elementPos.x += elementDir.x * 0.1;
	    elementPos.y += elementDir.y * 0.1;
    }
    */
   
   /*
   for (auto &element : manager.GetComponents<ComflabulationComponent>()) {

        Pair<ComflabulationComponent> pair { element.first, element.second };
        pair.component.thingy *= 1.000001f;
	    pair.component.mingy = !pair.component.mingy;
	    pair.component.dingy++;
   }
   */

  auto elementList = manager.GetEntitiesWithComponents<Pos2D, Speed>();

  for (EntityID element : *elementList) {
    auto &elementPos = manager.GetComponent<Pos2D>(element);
    auto &elementSpd = manager.GetComponent<Speed>(element);

    elementPos.x += elementSpd.speedX * (1.0f / 60.0f);
    elementPos.y += elementSpd.speedY * (1.0f / 60.0f);

  }

  //for (auto &element : manager.GetComponents<Health>()) {
  //    element.second.health++;
  //}

    mydeltaTime = mytimer.now() - myoldTime;

    //NLSLOG::Warn("Game", "Time: {}", deltaTime.count());
    std::cout << "Time: " << mydeltaTime.count() << std::endl;

    //auto tempo = manager.GetEntitiesWithComponents<Health>();

    //for (auto element : *tempo) {
    //    NLSLOG::Trace("Game", "{}", element);
    //}


    //mSharpHost.RunFunc();
    //Engine::GetEngine().GetRuntimeHost().RunFunc();


    Engine::GetEngine().GetRuntimeHost().CreateNewProject("MyTestProject");
    Engine::GetEngine().GetRuntimeHost().RunFunc();
}

void Game::OnUpdate() {
    ProcessEventQueue();

    if (Engine::GetEngine().GetInputManager().GetKeyDown("Jump")) {
        NLSLOG::Info("Game", "Player Jumped");
    }

    if (Engine::GetEngine().GetInputManager().GetKeyDown("Lurch", mWindow.lock()->GetGLFWWindowInstance())) {
        NLSLOG::Info("Game", "Player Lurched");
    }

    if (Engine::GetEngine().GetInputManager().GetKeyDownSysDelay("Shoot")) {
        NLSLOG::Info("Game", "Pew pew");
    }
}