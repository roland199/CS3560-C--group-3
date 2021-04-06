//
// minimal.cpp
// ***********
//
// Copyright (c) 2020 Sharon Fox (sharon at xandium dot io)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include <aegis.hpp>
#include <nlohmann/json.hpp>

// text file
#include <string>
#include <iostream>
#include <fstream>



using json = nlohmann::json;
using aegis::rest::rest_reply;
using aegis::gateway::objects::message;

void replace(std::string username, std::string item, std::string change);

int main(int argc, char * argv[])
{
    using namespace std::chrono_literals;
    try
    {
        // Create bot object


       //BOT TOKEN LINE


        // These callbacks are what the lib calls when messages come in
        bot.set_on_message_create([&](aegis::gateway::events::message_create obj)
        {
                try
                {
                    //get snowflakes related to this message
                    // C++17 version
                    //const auto [channel_id, guild_id, message_id, member_id] = obj.msg.get_related_ids();
                    const aegis::snowflake channel_id = obj.msg.get_channel().get_id();
                    const aegis::snowflake guild_id = obj.msg.get_guild().get_id();
                    const aegis::snowflake message_id = obj.msg.get_id();
#if !defined(AEGIS_DISABLE_ALL_CACHE)
                    const aegis::snowflake member_id = obj.msg.get_user().get_id();
#else
                    const aegis::snowflake member_id = obj.msg.author.id;
#endif

                    // Is message author myself?
                    if (member_id == bot.get_id())
                        return;

                    // Ignore bot messages and DMs
                    if (obj.msg.is_bot() || !obj.msg.has_guild())
                        return;

                    auto& _channel = obj.msg.get_channel();
                    auto& _guild = _channel.get_guild();
                    auto& username = obj.msg.author.username;

                    std::string content{ obj.msg.get_content() };

                    // Simple Hi response
                                                                   // file work

                    bool found = 0;
                    std::string user = username;
                    std::ifstream infile;
                    infile.open("testfile.txt");
                    while (!infile.eof())                          // search for username
                    {
                        std::string temp = "";
                        getline(infile, temp);
                        if(temp == user){
                            found = 1;
                        }
                    }
                    infile.close();                                         //file output
                    if (found == 0) {
                        aegis::gateway::objects::embed newp;
                        newp.title(fmt::format("Hello {}, you must be new here, type 'bm start' to get started.", obj.msg.author.username));
                        
                        _channel.create_message_embed("", newp);

                        
                        std::ofstream outfile;                                                  
                        outfile.open("testfile.txt", std::ofstream::out | std::ofstream::app);
                        outfile << username << std::endl << "1" << std::endl << "0" << std::endl << "100" << std::endl << "no" << std::endl << "no" << std::endl << "no" << std::endl << "0" << std::endl << "no" << std::endl << "0" << std::endl;
                        outfile.close();
                    }else {
                        std::string plevel = "";
                        std::string pgold = "";
                        std::string phealth = "";
                        std::string psword = "";
                        std::string parmor = "";
                        std::string pbow = "";
                        std::string parrows = "";
                        std::string phealthkit = "";
                        std::string pbandages = "";
                        bool find = 0;
                        infile.open("testfile.txt");
                        while (!infile.eof() && find != 1)                          // search for username
                        {
                            std::string temp = "";
                            getline(infile, temp);
                            if (temp == user) {
                                find = 1;
                            }
                        }
                        getline(infile, plevel);                   // getting profile info
                        getline(infile, pgold);
                        getline(infile, phealth);
                        getline(infile, psword);
                        getline(infile, parmor);
                        getline(infile, pbow);
                        getline(infile, parrows);
                        getline(infile, phealthkit);
                        getline(infile, pbandages);
                      
                        infile.close();

                        std::vector<aegis::gateway::objects::field> startFields;
                        aegis::gateway::objects::field startField;
                        startField.name("Ready to get started?");
                        startField.value("Type 'bm help' to get a full list of commands");
                        startFields.push_back(startField);

                        aegis::gateway::objects::thumbnail baermelk;
                        baermelk.url = ("https://cdnb.artstation.com/p/assets/images/images/018/177/381/large/wilson-rojas-degr1.jpg?1558546923");

                        aegis::gateway::objects::embed start;
                        start.title(fmt::format("Welcome to Baermelk {}", obj.msg.author.username));
                        start.description("This is a freeroaming game where you can adventure to gather resources, fight mobs, and gain experience to defeat the main boss, BaerMelk.");
                        start.color(31);
                        start.thumbnail(baermelk);
                        start.fields(startFields);

                        std::vector<aegis::gateway::objects::field> cmdFields;                  //help vector
                        aegis::gateway::objects::field cmdShop, cmdAdventure, cmdBuy, cmdSell, cmdProfile;
                        cmdProfile.name("'bm profile'");
                        cmdProfile.value("Shows player profile and player inventory");
                        cmdShop.name("'bm shop'");
                        cmdShop.value("Shows all available items to purchase");
                        cmdAdventure.name("'bm adventure'");
                        cmdAdventure.value("May encounter dangerous mobs and/or find loot");
                        cmdBuy.name("'bm buy [item]'");
                        cmdBuy.value("Purchase items in the shop");
                        cmdSell.name("'bm sell [item]'");
                        cmdSell.value("Sell items you own");
                        cmdFields.push_back(cmdProfile); cmdFields.push_back(cmdShop); cmdFields.push_back(cmdAdventure); cmdFields.push_back(cmdBuy); cmdFields.push_back(cmdSell); 

                        aegis::gateway::objects::embed help;
                        help.title("List of Commands");
                        help.color(31);
                        help.fields(cmdFields);

                        std::vector<aegis::gateway::objects::field> itemFields;                           // shop vector
                        aegis::gateway::objects::field sword, bow, arrows, armor, healthKit, bandages;
                        sword.name("Sword");
                        sword.value("100 Gold");
                        sword.is_inline(true);
                        bow.name("Bow");
                        bow.value("50 Gold");
                        bow.is_inline(true);
                        arrows.name("Arrows");
                        arrows.value("25 Gold");
                        arrows.is_inline(true);
                        armor.name("Armor");
                        armor.value("200 Gold");
                        armor.is_inline(true);
                        healthKit.name("Health Kit");
                        healthKit.value("100 Gold");
                        healthKit.is_inline(true);
                        bandages.name("Bandages");
                        bandages.value("50 Gold");
                        bandages.is_inline(true);
                        itemFields.push_back(sword); itemFields.push_back(bow); itemFields.push_back(arrows); itemFields.push_back(armor); itemFields.push_back(healthKit); itemFields.push_back(bandages);

                        aegis::gateway::objects::embed shop;
                        shop.title("Shop");
                        shop.color(31);
                        shop.fields(itemFields);

                        std::vector<aegis::gateway::objects::field> stats;                  // Profile Vector
                        aegis::gateway::objects::field level, gold, health;
                        level.name("Level: ");
                        level.value(plevel);
                        level.is_inline(true);
                        gold.name("Gold: ");
                        gold.value(pgold);
                        gold.is_inline(true);
                        health.name("Health: ");
                        health.value(phealth);
                        health.is_inline(true);
                        stats.push_back(level);stats.push_back(gold);stats.push_back(health);

                        std::vector<aegis::gateway::objects::field> inventory;
                        aegis::gateway::objects::field lsword, larmor, lbow, larrows, lhealthkit, lbandages;
                        lsword.name("Sword: ");
                        lsword.value(psword);
                        lsword.is_inline(true);
                        lbow.name("Bow: ");
                        lbow.value(pbow);
                        lbow.is_inline(true);
                        larrows.name("Arrows: ");
                        larrows.value(parrows);
                        larrows.is_inline(true);
                        larmor.name("Armor: ");
                        larmor.value(parmor);
                        larmor.is_inline(true);
                        lhealthkit.name("Health Kit: ");
                        lhealthkit.value(phealthkit);
                        lhealthkit.is_inline(true);
                        lbandages.name("Bandages: ");
                        lbandages.value(pbandages);
                        lbandages.is_inline(true);
                        inventory.push_back(lsword);inventory.push_back(lbow);inventory.push_back(larrows);inventory.push_back(larmor);inventory.push_back(lhealthkit);inventory.push_back(lbandages);

                        aegis::gateway::objects::embed profile, linventory;
                        profile.title("Profile");
                        profile.color(31);
                        profile.fields(stats);
                        linventory.title("Inventory");
                        linventory.color(31);
                        linventory.fields(inventory);



                        if (content == "test")                              // manipulating profile data
                        {
                            replace(username, "gold", "3333");
                        }
                        
                        if (content == "bm profile") {
                            _channel.create_message_embed("", profile);
                            _channel.create_message_embed("", linventory);
                        }
                        if (content == "bm start") {
                            _channel.create_message_embed("", start);
                        }
                        if (content == "bm help") {
                            _channel.create_message_embed("", help);
                        }if (content == "bm shop") {
                            _channel.create_message_embed("", shop);
                        }
                        std::vector<aegis::gateway::objects::field> encounter;
                            aegis::gateway::objects::field egold, ehealth, esituation;
                                aegis::gateway::objects::embed encount;

                        if (content == "bm adventure") {
                            int gold; int health; int oldGold; int newGold; int oldHealth; int newHealth;

                            srand(time(0));
                            //int num = rand() % 5 + 0;
                            int num = 0;
                            switch (num) {
                            case 0:
                                esituation.name("Holy Moly");
                                esituation.value("You defeated a HUGE ASS SPIDER");
                                gold = rand() % 25 + 25;
                                egold.value(fmt::format("You found {} gold!", gold)); 
                                egold.name("Gold: ");
                                health = rand() % 25 + 25; 
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation);encounter.push_back(egold);encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                _channel.create_message_embed("", encount);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                
                                break;
                            case 1:
                                esituation.name("Trolling in The Deep");
                                esituation.value("You defeated a CAVE TROLL");
                                gold = rand() % 25 + 50;
                                egold.value(fmt::format("You found {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 25 + 35;
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                _channel.create_message_embed("", encount);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
      
                                break;
                            case 2:
                                esituation.name("Hidden Treasure");
                                esituation.value("You discovered a pouch of gold!");
                                gold = rand() % 25 + 50;
                                egold.value(fmt::format("You found {} gold!", gold));
                                egold.name("Gold: ");
                                encounter.push_back(esituation); encounter.push_back(egold);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                _channel.create_message_embed("", encount);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                break;
                            case 3:
                                esituation.name("Oh No");
                                esituation.value("You were ambushed by bandits!");
                                gold = rand() % 25 + 15;
                                egold.value(fmt::format("You lost {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 25 + 15;
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                _channel.create_message_embed("", encount);

                                oldGold = stoi(pgold);
                                newGold = oldGold - gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                break;
                            case 4:
                                esituation.name("Goblin Attack");
                                esituation.value("You defended a small village from a GOBLIN RAID");
                                gold = rand() % 25 + 50;
                                egold.value(fmt::format("You were awarded {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 25 + 20;
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                _channel.create_message_embed("", encount);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                break;
                            }
                               std::string newG = std::to_string(newGold);
                                replace(username, "gold", newG);
                                std::string newH = std::to_string(newHealth);
                                replace(username, "health", newH);
                        }
                        }
                // Send a message, wait for message to successfully be sent, then react to that message
                 if (content == "~Delay")
                {
                    _channel.create_message("First message").then([](message msg)
                    {
                        // add a reaction to that new message
                        msg.create_reaction("success:429554838083207169");
                    });
                }
                else if (content == "~exit")
                {
                    bot.shutdown();
                    return;
                }

            }
            catch (std::exception & e)
            {
                std::cout << "Error: " << e.what() << '\n';
            }
            return;
        });

        // start the bot
        bot.run();
        // yield thread execution to the library
        bot.yield();
    }
    catch (std::exception & e)
    {
        std::cout << "Error during initialization: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cout << "Error during initialization: uncaught\n";
        return 1;
    }
    std::cout << "Press any key to continue...\n";
    std::cin.ignore();
    return 0;
}

void replace(std::string username, std::string item, std::string change)
{
std::ifstream infile;
std::ofstream outfile;
infile.open("testfile.txt");
outfile.open("temp.txt");
int loopNum = 0;

std::string line;

if (item == "gold") {
    loopNum = 1;
}
if (item == "level") {
    loopNum = 0;
}
if (item == "health") {
    loopNum = 2;
}
if (item == "sword") {
    loopNum = 3;
}
if (item == "armor") {
    loopNum = 4;
}
if (item == "bow") {
    loopNum = 5;
}
if (item == "arrows") {
    loopNum = 6;
}
if (item == "healthkit") {
    loopNum = 7;
}
if (item == "bandages") {
    loopNum = 8;
}

while (!infile.eof()) {

    getline(infile, line);
    if (line == username) {
        outfile << line << std::endl;
        for (int i = 0; i < loopNum; i++) {
            getline(infile, line);
            outfile << line << std::endl;
        }
        getline(infile, line);
        outfile << change << std::endl;
    }
    else {
        outfile << line << std::endl;
    }
}
outfile.close();
infile.close();
remove("testfile.txt");
rename("temp.txt", "testfile.txt");

}
