#include "Game.hpp"

#include "Log.hpp"

#include <NLS-Engine/IO/KeyBindingSet.hpp>
#include <NLS-Engine/IO/InputManager.hpp>


#include <NLS-Engine/ECS/ECSManager.hpp>
#include <NLS-Engine/ECS/ComponentHandler.hpp>

struct Position {
    int x = 0;
    int y= 0;
    int z = 500;
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
    int health = 100;
};


struct Renderable {
    bool isRenderable = true;
};

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

    mSharpHost.CreateNewProject("MyTestProject");

    NLS::INPUT::KeyBindingSet mySet { "Jump", "Shoot", "Lurch" };

    NLS::INPUT::InputManager::LoadActiveKeybindingSet(std::move(mySet));

    // Event Testing
    mWindow = NLS::RENDERING::WindowManager::ConstructWindow("First Window");
    mSecondWindow = NLS::RENDERING::WindowManager::ConstructWindow("Second Window");
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

    manager.CreateComponentHandler<BenchPosition>();
    manager.CreateComponentHandler<BenchDirection>();
    manager.CreateComponentHandler<ComflabulationComponent>();
    
    for (uint64_t entity = 0; entity < 100000; entity++) {
        //manager.AddComponentToEntity<BenchPosition>(entity, 9, 0);
        //manager.AddComponentToEntity<BenchDirection>(entity);
        manager.AddComponentToEntity<Health>(entity);


        //if (entity % 2 != 0) {
		//    manager.AddComponentToEntity<ComflabulationComponent>(entity);
	    //}
    }


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

  for (auto &element : manager.GetComponents<Health>()) {
      element.second.health++;
  }
}

void Game::OnUpdate() {
    ProcessEventQueue();

    if (NLS::INPUT::InputManager::GetKeyDown("Jump")) {
        NLSLOG::Info("Game", "Player Jumped");
    }

    if (NLS::INPUT::InputManager::GetKeyDown("Lurch", mWindow.lock()->GetGLFWWindowInstance())) {
        NLSLOG::Info("Game", "Player Lurched");
    }

    if (NLS::INPUT::InputManager::GetKeyDownSysDelay("Shoot")) {
        NLSLOG::Info("Game", "Pew pew");
    }
}