#pragma once
enum Scene_State
{
    IN_MAIN_SCENE,

    IN_BATTLE_SCENE,

    IN_ANIMAL_POCKET,

    IN_MEDICINE_POCKET,

    TRANSIT_FROM_MAIN_TO_BATTLE,

    TRANSIT_FROM_BATTLE_TO_MAIN,

    TRANSIT_FROM_BATTLE_TO_ANIMAL_POCKET,

    TRANSIT_FROM_BATTLE_TO_MEDICINE_POCKET,

    TRANSIT_FROM_MAIN_TO_ANIMAL_POCKET,

    TRANSIT_FROM_MAIN_TO_MEDICINE_POCKET
};