#include "HOTA/Hero.hpp"
#include "HOTA/Animation.hpp"
#include <iostream>
// Delegation
Hero::Hero() : Hero{"", 0, 0, 0, 0, 0.0f}
{
}

Hero::Hero(std::string pathVal, int healthVal, int damageVal, int manaVal, int defenseVal, float critChanceVal)
    : AnimationCreator{pathVal}, ani_name{"idle"}, health(healthVal), damage(damageVal), mana(manaVal), defense(damageVal), crit_chance(critChanceVal)
{
}

Hero::~Hero()
{
}

void Hero::update()
{
  this->animation->update(this->is_ani_over);
  this->move_character();
  this->atk_character();
  this->select_animation(this->ani_name);
}

void Hero::render(sf::RenderTarget &target)
{
  this->animation->render(target);
}

void Hero::move_character()
{
  if (this->ani_name == "run")
  {
    this->move(sf::Keyboard::D);
  }
  else if (this->ani_name == "run_left")
  {
    this->move(sf::Keyboard::A);
  }
  if (this->ani_name == "jump_up" || this->ani_name == "jump_down")
  {
    this->move(sf::Keyboard::Space);
  }
}

void Hero::atk_character()
{
  if (this->ani_name == "1_atk" || this->ani_name == "2_atk" || this->ani_name == "sp_atk" || this->ani_name == "defend")
  {
    if (this->is_ani_over)
    {
      this->ani_name = "idle";
      this->is_ani_over = false;
    }
  }
}

void Hero::poll_events(sf::Event &event)
{
  if (this->ani_name == "jump_up" || this->ani_name == "jump_down" || this->ani_name == "1_atk" || this->ani_name == "2_atk" || this->ani_name == "sp_atk" || this->ani_name == "defend")
  {
    return;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // TODO
  {
    this->ani_name = "run";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    this->ani_name = "run_left";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
  {
    this->ani_name = "1_atk";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    this->ani_name = "2_atk";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
  {
    this->ani_name = "defend";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
  {
    this->ani_name = "sp_atk";
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    this->ani_name = "jump_up";
  }
};

void Hero::poll_events_loop(sf::Event &event)
{
  if (event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::A)
    {
      if (this->ani_name == "jump_up" || this->ani_name == "jump_down" || this->ani_name == "1_atk" || this->ani_name == "2_atk" || this->ani_name == "sp_atk" || this->ani_name == "defend")
      {
        return;
      }
      this->ani_name = "idle";
    }
  }
}

void Hero::move(sf::Keyboard::Key key)
{
  sf::Sprite *sp = this->animation->get_sprite()->at(0);
  sf::Vector2f pos = sp->getPosition();
  if (pos.x < (1548 - 505))
  {
    if (key == sf::Keyboard::D)
    {
      sp->setPosition(pos.x + 5, pos.y);
    }
  }
  if (pos.x != -355)
  {
    if (key == sf::Keyboard::A)
    {
      sp->setPosition(pos.x - 5, pos.y);
    }
  }
  if (key == sf::Keyboard::Space)
  {
    if (this->ani_name == "jump_up" && pos.y > 250.f)
    {
      sp->setPosition(pos.x, pos.y - 4);
    }
    else if (pos.y <= 343)
    {
      this->ani_name = "jump_down";
      sp->setPosition(pos.x, pos.y + 4);
    }
    else
    {
      this->ani_name = "idle";
    }
  }
  this->set_all_animation_position(this->animation->get_sprite()->at(0)->getPosition());
}
/**
 *
std::map<std::string, Animation *> &Hero::get_hero_ani()
{
  return this->hero_ani;
}

std::string Hero::get_ani_name()
{
  return this->ani_name;
}

// Getters
std::string Hero::get_path()
{
  return this->path;
}

int Hero::get_health()
{
  return this->health;
}
int Hero::get_damage()
{
  return this->damage;
}
int Hero::get_mana()
{
  return this->mana;
}
int Hero::get_defense()
{
  return this->defense;
}
float Hero::get_crit_chance()
{
  return this->critChance;
}

//
int Hero::get_idle_num()
{
  return this->idleNum;
}
int Hero::get_atk_one_num()
{
  return this->atk_one_num;
}
int Hero::get_atk_two_num()
{
  return this->atk_two_num;
}
int Hero::get_atk_sp_num()
{
  return this->atk_sp_num;
}
int Hero::get_run_num()
{
  return this->run_num;
}
int Hero::get_roll_num()
{
  return this->roll_num;
}
int Hero::get_jump_num()
{
  return this->jump_num;
}
int Hero::get_defend_num()
{
  return this->defend_num;
}
int Hero::get_death_num()
{
  return this->death_num;
}
int Hero::get_take_dmg_num()
{
  return this->take_dmg_num;
}
//
void Hero::set_hero_ani(std::pair<std::string, Animation *> pair)
{
  this->hero_ani.insert(pair);
}

// Setters
void Hero::set_path(std::string path)
{
  this->path = path;
}

void Hero::set_health(int health)
{
  this->health = health;
}
void Hero::set_damage(int damage)
{
  this->damage = damage;
}
void Hero::set_mana(int mana)
{
  this->mana = mana;
}
void Hero::set_defense(int defense)
{
  this->defense = defense;
}
void Hero::set_crit_chance(float critChance)
{
  this->critChance = critChance;
}

//
void Hero::set_idle_num(int idleNum)
{
  this->idleNum = idleNum;
}
void Hero::set_atk_one_num(int atkOneNum)
{
  this->atk_one_num = atkOneNum;
}
void Hero::set_atk_two_num(int atkTwoNum)
{
  this->atk_two_num = atkTwoNum;
}
void Hero::set_atk_sp_num(int atkSpNum)
{
  this->atk_sp_num = atkSpNum;
}
void Hero::set_run_num(int runNum)
{
  this->run_num = runNum;
}
void Hero::set_roll_num(int rollNum)
{
  this->roll_num = rollNum;
}
void Hero::set_jump_num(int jumpNum)
{
  this->jump_num = jumpNum;
}
void Hero::set_defend_num(int defendNum)
{
  this->defend_num = death_num;
}
void Hero::set_death_num(int deathNum)
{
  this->death_num = deathNum;
}
void Hero::set_take_dmg_num(int takeDmgNum)
{
  this->take_dmg_num = takeDmgNum;
}
*/
