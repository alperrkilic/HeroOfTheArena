#include "HOTA/Wind.hpp"
#include <iostream>

Wind::Wind() : Hero{"image", 5000, 200, 500, 250, 0.1f}
{
    this->init_var();
    std::cout << this->ani_name << std::endl;
}

Wind::~Wind()
{
}

void Wind::init_var()
{
    this->init_ani_stats();
    this->init_ani();
    this->init_stats();
}

void Wind::init_ani_stats()
{

    this->path += "/Wind";
    this->atk_one_num = 8;
    this->atk_two_num = 18;
    this->atk_sp_num = 30;
    this->death_num = 19;
    this->defend_num = 8;
    this->idle_num = 8;
    this->jump_num = 6;
    this->roll_num = 6;
    this->run_num = 8;
    this->take_dmg_num = 6;
}

void Wind::init_stats()
{
    this->health -= 1800;
    this->damage += 100;
    this->mana += 200;
    this->defense -= 50;
    this->crit_chance += 0.25;
}

void Wind::init_ani()
{
    // auto ani_path = this->get_path();
    this->hero_ani.insert(std::pair<std::string, Animation *>("idle", new Animation(this->path, "idle", "idle_", this->idle_num)));
    this->hero_ani.insert(std::pair<std::string, Animation *>("run", new Animation(this->path, "run", "run_", this->run_num)));
    this->hero_ani.insert(std::pair<std::string, Animation *>("roll", new Animation(this->path, "roll", "roll_", this->roll_num)));
    this->hero_ani.insert(std::pair<std::string, Animation *>("roll_left", new Animation(this->path, "roll", "roll_", this->roll_num)));
    this->hero_ani.insert(std::pair<std::string, Animation *>("run_left", new Animation(this->path, "run_left", "run_", this->run_num)));
    this->hero_ani.insert(std::pair<std::string, Animation *>("jump", new Animation(this->path, "jump_up", "jump_up_", 3)));
    // this->hero_ani.insert(std::pair<std::string, Animation *>("jump", new Animation(this->path, "jump_up", "jump_up_", this->jump_num)));
}

void Wind::skill()
{
    // TODO
}

void Wind::upgrade()
{
    // TODO
}

void Wind::update(sf::RenderWindow &window)
{
    for (auto &i : this->hero_ani)
    {
        if (i.first == this->ani_name)
        {
            this->move_character(window);
            return this->hero_ani[this->ani_name]->update();
        }
    }
    // this->get_hero_ani()["idle"]->update();
}

void Wind::render(sf::RenderTarget &target)
{

    for (auto &i : this->hero_ani)
    {
        if (i.first == this->ani_name)
        {
            this->hero_ani[this->ani_name]->render(target);
        }
    }
}

void Wind::move_character(sf::RenderWindow &window)
{
    if (this->ani_name == "run")
    {
        this->move(sf::Keyboard::D, window);
    }
    else if (this->ani_name == "run_left")
    {
        this->move(sf::Keyboard::A, window);
    }
    // if (this->ani_name == "jump")
    // {
    //     this->move(sf::Keyboard::W, window);
    // }
}