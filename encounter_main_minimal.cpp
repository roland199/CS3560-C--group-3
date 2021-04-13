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
void deleteSpace();
void pdeath(std::string username, aegis::channel& _chan);


int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    try
    {
        // Create bot object
        //BOT LINE
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
                        if (temp == user) {
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
                        outfile << username << std::endl << "0" << std::endl << "0" << std::endl << "100" << std::endl << "no" << std::endl << "no" << std::endl << "no" << std::endl << "0" << std::endl << "no" << std::endl << "0" << std::endl << "0" << std::endl;
                        outfile.close();
                    }
                    else {
                        std::string pexperience = "";
                        std::string pgold = "";
                        std::string phealth = "";
                        std::string psword = "";
                        std::string parmor = "";
                        std::string pbow = "";
                        std::string parrows = "";
                        std::string phealthkit = "";
                        std::string pbandages = "";
                        std::string bm = "";
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
                        getline(infile, pexperience);                   // getting profile info
                        getline(infile, pgold);
                        getline(infile, phealth);
                        getline(infile, psword);
                        getline(infile, parmor);
                        getline(infile, pbow);
                        getline(infile, parrows);
                        getline(infile, phealthkit);
                        getline(infile, pbandages);
                        getline(infile, bm);

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
                        aegis::gateway::objects::field cmdShop, cmdAdventure, cmdBuy, cmdSell, cmdProfile, cmdUse, cmdTips;
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
                        cmdUse.name("'bm use bandage' or 'bm use health kit'");
                        cmdUse.value("Uses a bandage which heals 10 health or a health kit which heals you fully");
                        cmdTips.name("Tips");
                        cmdTips.value("Armor reduces damage taken by 50%.\n Sword reduces damage taken in close quarters by 25%. \n Bow reduces damage taken in a long range encounter by 25%.");
                        cmdFields.push_back(cmdProfile); cmdFields.push_back(cmdShop); 
                        cmdFields.push_back(cmdAdventure); cmdFields.push_back(cmdBuy); 
                        cmdFields.push_back(cmdSell); cmdFields.push_back(cmdUse); cmdFields.push_back(cmdTips);

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
                        arrows.name("Arrows(10)");
                        arrows.value("25 Gold");
                        arrows.is_inline(true);
                        armor.name("Armor");
                        armor.value("200 Gold");
                        armor.is_inline(true);
                        healthKit.name("Health Kit");
                        healthKit.value("100 Gold");
                        healthKit.is_inline(true);
                        bandages.name("Bandages(5)");
                        bandages.value("50 Gold");
                        bandages.is_inline(true);
                        itemFields.push_back(sword); itemFields.push_back(bow); itemFields.push_back(arrows); itemFields.push_back(armor); itemFields.push_back(healthKit); itemFields.push_back(bandages);

                        aegis::gateway::objects::embed shop;
                        shop.title("Shop");
                        shop.color(31);
                        shop.fields(itemFields);

                        std::vector<aegis::gateway::objects::field> stats;                  // Profile Vector
                        aegis::gateway::objects::field exp, gold, health;
                        exp.name("Experience: ");
                        exp.value(pexperience);
                        exp.is_inline(true);
                        gold.name("Gold: ");
                        gold.value(pgold);
                        gold.is_inline(true);
                        health.name("Health: ");
                        health.value(fmt::format("{}/100", phealth));
                        health.is_inline(true);
                        stats.push_back(exp);stats.push_back(gold);stats.push_back(health);

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

                        if (content == "test") {
                            deleteSpace();
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
                        }
                        if (content == "bm shop") {
                            _channel.create_message_embed("", shop);
                        }
                        std::vector<aegis::gateway::objects::field> healing;          
                        aegis::gateway::objects::field action;
                        aegis::gateway::objects::embed result;
                        if (content == "bm use bandage") {
                            int Bands = stoi(pbandages);
                            int healed = stoi(phealth);
                            if (healed == 100)
                            {
                                action.name("Unable to use bandage");
                                    action.value("You're at full health! no bandage needed");
                            }
                            else{
                                if (Bands > 0) {
                                    Bands--;
                                    if (healed + 10 > 100)
                                    {
                                        healed = 100;
                                    }
                                    else
                                    {
                                    healed += 10;
                                    }
                                    std::string newH = std::to_string(healed);
                                    std::string newB = std::to_string(Bands);
                                    replace(username, "health", newH);
                                    replace(username, "bandages", newB);
                                    action.name("Used One Bandage");
                                    action.value(fmt::format("Health is now {}/100", healed));
                                }
                                else {
                                    action.name("Can't Use a Bandage");
                                    action.value("You have no bandages to use");
                                }
                                healing.push_back(action);
                                result.title("Healing:");
                                result.color(31);
                                result.fields(healing);
                                _channel.create_message_embed("", result);
                            }
                        }
                        if (content == "bm use health kit") {
                            if (phealthkit == "yes") {
                                replace(username, "health", "100");
                                replace(username, "healthkit", "no");
                                action.name("Used Health Kit");
                                action.value("Health is now 100/100");
                            }
                            else {
                                action.name("Can't Use a Health Kit");
                                action.value("You do not have a health kit to use");
                            }
                            healing.push_back(action);\
                            result.title("Healing:");
                            result.color(31);
                            result.fields(healing);
                            _channel.create_message_embed("", result);
                        }
                        std::vector<aegis::gateway::objects::field> buying;             //BUYING AREA OF CODE
                        aegis::gateway::objects::field bitem;
                        aegis::gateway::objects::embed bought;

                        if (content == "bm buy sword") {
                            int oldGold = stoi(pgold);
                            if (psword == "no") {
                                if (oldGold >= 100) {
                                    oldGold -= 100;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    replace(username, "sword", "yes");
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a sword for 100 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one sword");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm buy bow") {
                            int oldGold = stoi(pgold);
                            if (pbow == "no") {
                                if (oldGold >= 50) {
                                    oldGold -= 50;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    replace(username, "bow", "yes");
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a bow for 50 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one bow");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm buy arrows") {
                            int oldGold = stoi(pgold);
                            int oldarrows = stoi(parrows);
                            if (oldarrows + 10 <= 30) {
                                if (oldGold >= 25) {
                                    oldGold -= 25;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    oldarrows += 10;
                                    std::string newA = std::to_string(oldarrows);
                                    replace(username, "arrows", newA);
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a 10 arrows for 25 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry 30 arrows");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm buy armor") {
                            int oldGold = stoi(pgold);
                            if (parmor == "no") {
                                if (oldGold >= 200) {
                                    oldGold -= 200;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    replace(username, "armor", "yes");
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a set of armor for 200 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one set of armor");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm buy health kit") {
                            int oldGold = stoi(pgold);
                            if (phealthkit == "no") {
                                if (oldGold >= 100) {
                                    oldGold -= 100;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    replace(username, "healthkit", "yes");
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a health kit for 100 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one health kit");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm buy bandages") {
                            int oldGold = stoi(pgold);
                            int oldbandages = stoi(pbandages);
                            if (oldbandages + 5 <= 20) {
                                if (oldGold >= 50) {
                                    oldGold -= 50;
                                    std::string newG = std::to_string(oldGold);
                                    replace(username, "gold", newG);
                                    oldbandages += 5;
                                    std::string newB = std::to_string(oldbandages);
                                    replace(username, "bandages", newB);
                                    bitem.name("Transaction Complete");
                                    bitem.value("Obtained a 5 bandages for 50 gold");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry 20 bandages");
                                buying.push_back(bitem);
                            }
                            bought.title("Buying from Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);                     //BUYING AREA OF CODE END
                        }
                        if (content == "bm sell sword") {                                  //SELLING AREA OF CODE 
                            int oldGold = stoi(pgold);
                            if (psword == "yes") {
                                oldGold += 100;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                replace(username, "sword", "no");
                                bitem.name("Transaction Complete");
                                bitem.value("Sold a sword for 100 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own a sword to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm sell bow") {
                            int oldGold = stoi(pgold);
                            if (pbow == "yes") {
                                oldGold += 50;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                replace(username, "bow", "no");
                                bitem.name("Transaction Complete");
                                bitem.value("Sold a bow for 50 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own a bow to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm sell armor") {
                            int oldGold = stoi(pgold);
                            if (parmor == "yes") {
                                oldGold += 200;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                replace(username, "armor", "no");
                                bitem.name("Transaction Complete");
                                bitem.value("Sold armor for 200 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own armor to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm sell health kit") {
                            int oldGold = stoi(pgold);
                            if (phealthkit == "yes") {
                                oldGold += 100;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                replace(username, "healthkit", "no");
                                bitem.name("Transaction Complete");
                                bitem.value("Sold a health kit for 100 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own a health kit to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm sell bandages") {
                            int oldGold = stoi(pgold);
                            int oldbandages = stoi(pbandages);
                            if (oldbandages >= 5) {
                                oldGold += 50;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                oldbandages -= 5;
                                std::string newB = std::to_string(oldbandages);
                                replace(username, "bandages", newB);
                                bitem.name("Transaction Complete");
                                bitem.value("Sold 5 bandages for 50 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own 5 bandages to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }
                        if (content == "bm sell arrows") {
                            int oldGold = stoi(pgold);
                            int oldarrows = stoi(parrows);
                            if (oldarrows >= 10) {
                                oldGold += 25;
                                std::string newG = std::to_string(oldGold);
                                replace(username, "gold", newG);
                                oldarrows -= 10;
                                std::string newA = std::to_string(oldarrows);
                                replace(username, "arrows", newA);
                                bitem.name("Transaction Complete");
                                bitem.value("Sold 10 arrows for 25 gold");
                                buying.push_back(bitem);
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You do not own 10 arrows to sell");
                                buying.push_back(bitem);
                            }
                            bought.title("Selling to Shop");
                            bought.color(31);
                            bought.fields(buying);
                            _channel.create_message_embed("", bought);
                        }                                                                             //SELLING AREA OF CODE END




                        std::vector<aegis::gateway::objects::field> encounter;
                        aegis::gateway::objects::field egold, ehealth, esituation;
                        aegis::gateway::objects::embed encount;

                        if (content == "bm adventure") {
                            int gold; int health; int oldGold; int newGold; int oldHealth; int newHealth; int oldExp; int newExp; int dead; int arrows; int winrate; bool won;

                            srand(time(0));
                            //int num = rand() % 5;
                            int num = 0;
                            switch (num) {
                            case 0:
                                esituation.name("Holy Moly");
                                esituation.value("You found a HUGE SPIDER");
                                gold = rand() % 30 + 60;
                                egold.value(fmt::format("You found {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 30;
                                {
                                    health *= .5;
                                }
                                if (psword == "yes" && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (psword == "yes" && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                

                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation);encounter.push_back(egold);encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;
                            case 1:
                                esituation.name("Trolling in The Deep");
                                esituation.value("You defeated a CAVE TROLL");
                                gold = rand() % 40 + 80;
                                egold.value(fmt::format("You found {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes" && psword == "no")
                                {
                                    health *= .5;
                                }
                                if (psword == "yes" && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (psword == "yes" && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
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

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                newHealth = stoi(phealth);
                                oldExp = stoi(pexperience);
                                break;
                            case 3:
                                esituation.name("Oh No");
                                esituation.value("You were ambushed by bandits!");
                                gold = rand() % 30 + 15;
                                egold.value(fmt::format("You lost {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes" && psword == "no") 
                                {
                                    health *= .5;
                                }
                                if (psword == "yes" && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (psword == "yes" && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold - gold;
                                if (newGold < 0) {newGold = 0;}
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;
                            
                            case 4:
                                esituation.name("Mysterious Assasin!");
                                esituation.value("You are being shot at from the North by an unknown attacker!");
                                health = rand() % 25 + 15;
                                if (parmor == "yes" && pbow == "no")
                                {
                                    health *= .5;
                                }
                                if (psword == "yes" && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (psword == "yes" && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;

                              case 5:
                                esituation.name("Kobold Quest");
                                gold = rand() % 40 + 40;
                                esituation.value(fmt::format("A disraught farmer paid you {} gold to rid thier fields of kobolds", gold));
                                egold.value(fmt::format("You gained {} gold!", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes" && psword == "no") 
                                {
                                    health *= .5;
                                }
                                if (pbow == "yes" && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (pbow == "yes" && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;

                            case 6:
                                esituation.name("Mage Duel");
                                gold = rand() % 40 + 50;
                                esituation.value(fmt::format("A powerful mage wagers {} gold and challenges you to a duel", gold));
                                 arrows == stoi(parrows);
                                if (pbow == "yes" && arrows > 0 )
                                {
                                    winrate = rand() % 4;
                                    if (winrate == 1)
                                    {
                                        egold.value(fmt::format("you lost :( you lose {} gold", gold));
                                        egold. name("Gold: ");  
                                    won = false;
                                    } 
                                    else
                                    {
                                        egold.value(fmt::format("you won! you gained {} gold!", gold));
                                       egold.name("Gold: ");
                                    won = true;
                                    }
                                    int arrows_lost = rand() %5;  
                                    arrows == arrows - arrows_lost;
                                    if (arrows < 0)
                                    {
                                        arrows == 0;
                                    }
                                }
                                else if (pbow == "no" || arrows == 0)
                                {
                                     winrate = rand() % 4;
                                    if (winrate == 1)
                                    {
                                        egold.value(fmt::format("you won! you gained {} gold!", gold));
                                        egold. name("Gold: "); 
                                    won = true; 
                                    } 
                                    else
                                    {
                                        egold.value(fmt::format("you lost :( you gained {} gold!", gold));
                                        egold.name("Gold: ");
                                    won = false;
                                }
                                health = rand() % 10 + 30;
                                if (parmor == "yes" && pbow == "no")
                                {
                                    health *= .5;
                                }
                                if (pbow == "yes" && arrows > 0 && parmor == "no")
                                {
                                    health -= (health * .25);
                                }
                                if (pbow == "yes" && arrows > 0 && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                if (won == true) {
                                    newGold = oldGold + gold;
                                }
                                else if (won == false) {
                                    newGold = oldGold - gold;
                                    if (newGold < 0) {newGold = 0;}
                                }
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;
                            case 7: 
                                esituation.name("Gladiator Tournament");
                                gold = rand() % 40 + 80;
                                esituation.value(fmt::format("You enter a gladiator tournament!", gold));
                                arrows == stoi(parrows);
                                if (psword == "yes" && parmor == "yes")
                                {
                                    winrate = rand() % 4;
                                    if (winrate == 1)
                                    {
                                        egold.value(fmt::format("you lost :( you lose {} gold", gold));
                                    egold. name("Gold: ");  
                                    won == false;
                                    } 
                                    else
                                    {
                                        egold.value(fmt::format("you won! you gained {} gold!", gold));
                                            egold.name("Gold: ");
                                    won == true;
                                    }
                                    int arrows_lost = rand() %5;  
                                    arrows = (arrows - arrows_lost);
                                    if (arrows < 0)
                                    {
                                        arrows == 0;
                                    }
                                }
                                else if ((psword == "no" && parmor == "yes") || (parmor == "no" && psword == "yes"))
                                {
                                    winrate = rand() % 4;
                                    if (winrate == 1 || winrate == 2)
                                    {
                                        egold.value(fmt::format("you won! you gained {} gold!", gold));
                                    egold. name("Gold: "); 
                                    won = true; 
                                    } 
                                    else
                                    {
                                        egold.value(fmt::format("you lost :( you gained {} gold!", gold));
                                            egold.name("Gold: ");
                                    won = false;
                                }
                                health = rand() % 10 + 30;
                                if (parmor == "yes" && pbow == "no") 
                                {
                                    health *= .5;
                                }
                                if (pbow == "yes" && arrows > 0  && parmor == "no") 
                                {
                                    health -= (health * .25);
                                }
                                if (pbow == "yes" && arrows > 0 && parmor == "yes")
                                {
                                    health -= (health * .75);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                if (won == true) {
                                    newGold = oldGold + gold;
                                }
                                else if (won == false) {
                                    newGold = oldGold - gold;
                                }
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;

                            /*
                               case :
                                esituation.name("Aid in a strange place");
                                esituation.value("You have stumbled upon 5 unused bandages! Nice!");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                int oldbandages = stoi(pbandages);
                                if (oldbandages + 5 <= 20) 
                                {
                                    oldbandages += 5;
                                    std::string newB = std::to_string(oldbandages);
                                    replace(username, "bandages", newB);
                                }
                                else
                                {
                                    eitem.name("Unable to pick up item");
                                    eitem.value("your pockets are too full! You set the bandages back down")
                                }
                                oldGold = stoi(pgold);
                                oldHealth = stoi(phealth);
                                oldExp = stoi(pexperience);
                                break;
                            */
                            if (newHealth <= 0) 
                            {
                                pdeath(username, _channel);
                            }
                            else {
                                _channel.create_message_embed("", encount);
                                std::string newG = std::to_string(newGold);
                                replace(username, "gold", newG);
                                std::string newH = std::to_string(newHealth);
                                replace(username, "health", newH);
                                std::string newE = std::to_string(newExp);
                                replace(username, "experience", newE);
                                std::string newA = std::to_string(arrows);
                                replace(username, "arrows", newA);
                            }   
                        }
                    }
                        std::vector<aegis::gateway::objects::field> boss;
                        aegis::gateway::objects::field actions;
                        aegis::gateway::objects::embed final;
                        if (content == "bm baermelk") {
                            int exp = stoi(pexperience);
                            if (exp >= 10) {
                                replace(username, "bm", "1");
                                final.title("Baermelk");
                                actions.name("Congratulations on making it this far. Now time for the real test.");
                                actions.value("After some time walking, you see Baermelk in the distance...");
                            }
                            else {
                                actions.name("You don't have enough experience to fight the one and only Baermelk");
                                int need = 10 - exp;
                                actions.value(fmt::format("You need {} more experience", need));
                                
                                final.title("Not Yet!");

                            }
                            boss.push_back(actions); 
                            final.color(31);
                            final.fields(boss);
                            _channel.create_message_embed("", final);
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
                catch (std::exception& e)
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
    catch (std::exception& e)
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
    if (item == "experience") {
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
    if (item == "bm") {
        loopNum = 9;
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
    deleteSpace();
}
void deleteSpace() {
    std::ifstream infile;
    std::ofstream outfile;
    infile.open("testfile.txt");
    outfile.open("temp.txt");
    std::string line;

    while (!infile.eof()) {

        getline(infile, line);
        if (line == "") {

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
void pdeath(std::string username, aegis::channel &_chan) 
{
    std::vector<aegis::gateway::objects::field> death;
    aegis::gateway::objects::field dying;
    dying.name("You Died");
    dying.value("Try again?");
    death.push_back(dying);
    aegis::gateway::objects::embed sadness;
    sadness.title("Yikes");
    sadness.color(31);
    sadness.fields(death);
    _chan.create_message_embed("", sadness);
    replace(username, "experience", "0");
    replace(username, "gold", "0");
    replace(username, "health", "100");
    replace(username, "sword", "no");
    replace(username, "armor", "no");
    replace(username, "bow", "no");
    replace(username, "bandages", "0");
    replace(username, "healthkit", "no");
    replace(username, "arrows", "0");
    replace(username, "bm", "0");
}