// FXnRXn copyright

#include "Tags/AbyssGameplayTags.h"
#include "GameplayTagsManager.h"



namespace Abyss_Tags
{
       // Input Tags
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Look, "InputTag.Look", "Look input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Fire, "InputTag.Fire", "Fire weapon input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_ADS, "InputTag.ADS", "Aim down sights input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Reload, "InputTag.Reload", "Reload weapon input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_SwitchWeapon, "InputTag.SwitchWeapon",
         "Switch weapon input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Interact, "InputTag.Interact", "Interact input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Sprint, "InputTag.Sprint", "Sprint input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Slide, "InputTag.Slide", "Slide input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Grenade, "InputTag.Grenade", "Throw grenade input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Heal, "InputTag.Heal", "Heal input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Ability1, "InputTag.Ability1",
         "Primary ability input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Ability2, "InputTag.Ability2",
         "Secondary ability input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Ultimate, "InputTag.Ultimate",
         "Ultimate ability input action");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Pause, "InputTag.Pause", "Pause game input action");

  // Ability Tags
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Fire, "Ability.Fire", "Weapon fire ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ADS, "Ability.ADS", "Aim down sights ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Reload, "Ability.Reload", "Reload ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Sprint, "Ability.Sprint", "Sprint ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Slide, "Ability.Slide", "Slide ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Grenade, "Ability.Grenade", "Grenade ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Heal, "Ability.Heal", "Heal ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Melee, "Ability.Melee", "Melee attack ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Shockwave, "Ability.Shockwave", "Shockwave AOE ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ElementalRounds, "Ability.ElementalRounds",
         "Elemental rounds ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Overdrive, "Ability.Overdrive", "Overdrive ultimate ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_SummonMinions, "Ability.SummonMinions",
         "Boss summon minions ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_BossGroundSlam, "Ability.Boss.GroundSlam",
         "Boss ground slam ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_BossCharge, "Ability.Boss.Charge", "Boss charge ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_BossRanged, "Ability.Boss.Ranged",
         "Boss ranged attack ability");

  // State Tags
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Dead, "State.Dead", "Character is dead");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Downed, "State.Downed", "Character is downed");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Invulnerable, "State.Invulnerable", "Character is invulnerable");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Sprinting, "State.Sprinting", "Character is sprinting");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Sliding, "State.Sliding", "Character is sliding");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_ADS, "State.ADS", "Character is aiming down sights");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Firing, "State.Firing", "Character is firing weapon");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Reloading, "State.Reloading", "Character is reloading");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Stunned, "State.Stunned", "Character is stunned");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Frozen, "State.Frozen", "Character is frozen");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Burning, "State.Burning", "Character is burning");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Poisoned, "State.Poisoned", "Character is poisoned");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Electrified, "State.Electrified", "Character is electrified");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Overdrive, "State.Overdrive", "Character is in overdrive mode");

  // Jump Tags
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Jump, "Ability.Jump", "Jump ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Jumping, "State.Jumping", "Character is jumping");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_InAir, "State.InAir", "Character is in air");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Movement_Jump, "Event.Movement.Jump", "Jump event");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Movement_Landed, "Event.Movement.Landed", "Landed event");

  // Crouch Tags
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Crouch, "Ability.Crouch", "Crouch ability");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Crouching, "State.Crouching", "Character is crouching");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Movement_Crouch, "Event.Movement.Crouch", "Crouch event");
  UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_Movement_Crouch, "GameplayCue.Movement.Crouch",
         "Crouch gameplay cue");
}
