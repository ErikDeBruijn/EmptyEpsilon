#ifndef SHIP_AI_H
#define SHIP_AI_H

#include <SFML/System.hpp>
#include "pathPlanner.h"

class CpuShip;

/// Base for all ship AIs. This base class handles basic AI which just follows orders straight on and attacks head on.
// ShipAI objects are only created on the server.
class ShipAI : sf::NonCopyable
{
    float missile_fire_delay;

    bool has_missiles;
    bool has_beams;
    float beam_weapon_range;
    
    PathPlanner pathPlanner;
public:
    CpuShip* owner;

    ShipAI(CpuShip* owner);
    virtual ~ShipAI();
    
    //Run is called every frame to update the AI state and let the AI take actions.
    virtual void run(float delta);
    
    //Are we allowed to switch to a different AI right now?
    // When true is returned, and the CpuShip wants to change their AI this AI object will be destroyed and a new one will be created.
    virtual bool canSwitchAI();

protected:
    virtual void updateWeaponState(float delta);
    virtual void updateTarget();
    virtual void runOrders();
    virtual void runAttack(P<SpaceObject> target);
    virtual void flyTowards(sf::Vector2f target, float keep_distance = 100.0);
    virtual void flyFormation(P<SpaceObject> target, sf::Vector2f offset);

    P<SpaceObject> findBestTarget(sf::Vector2f position, float radius);
    float targetScore(P<SpaceObject> target);
    bool betterTarget(P<SpaceObject> new_target, P<SpaceObject> current_target);
    
    float calculateFiringSolution(P<SpaceObject> target);
    
    friend class GameMasterUI;
};

#endif//SHIP_AI_H
