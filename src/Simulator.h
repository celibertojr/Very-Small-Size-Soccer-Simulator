/*The MIT License (MIT)

Copyright (c) 2016 Lucas Borsatto Simão

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "Header.h"
#include "Scenario.h"
#include "strategies/ModelStrategy.h"

class Simulator{
    struct GameState{
        vector<RobotStrategy*> robotStrategiesTeam;
        vector<RobotStrategy*> robotStrategiesAdv;
        bool sameState;

        GameState():sameState(true){};
    };

private:
    const float timeStep = 1.f/60.f;
    const float handTime = 1.f;
    int numRobotsTeam;
    bool runningPhysics;

    GameState* gameState;
    int stratStep;
    int loopBullet;

	HandleGraphics* handleGraphics;
	Physics* physics;
	vector<ModelStrategy*> strategies;

	void updateWorld();
	btVector3 calcRelativePosition(btVector3 absPos, int attackDir);
	void calcRelativeWorld(vector<RobotStrategy*> robotStrategiesTeam, int attackDir);
	RobotStrategy* updateLocalPhysics(int id, RobotPhysics* bdRobot);
public:
	Simulator();
	void runSimulator(int argc, char *argv[], ModelStrategy* strategyTeam, ModelStrategy* strategyAdv);

	void *runPhysics();
	void *runGraphics();
	void* runStrategies();

	static void* runGraphics_thread(void* simulator){
        return ((Simulator*)simulator)->runGraphics();
	}

    static void* runPhysics_thread(void* simulator){
        return ((Simulator*)simulator)->runPhysics();
    }

    static void* runStrategies_thread(void* simulator){
        return ((Simulator*)simulator)->runStrategies();
    }

};

#endif
