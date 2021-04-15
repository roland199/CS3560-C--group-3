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
                        outfile << username << std::endl << "0" << std::endl << "0" << std::endl << "100" << std::endl << "no" << std::endl << "no" << std::endl << "no" << std::endl << "0" << std::endl << "no" << std::endl << "0" << std::endl << "0" << std::endl << "100" << std::endl << "-1" << std::endl;
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
                        std::string pbm = "";
                        std::string pbmH = "";
                        std::string pweap = "";
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
                        getline(infile, pbm);
                        getline(infile, pbmH);
                        getline(infile, pweap);

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
                        aegis::gateway::objects::field cmdShop, cmdAdventure, cmdBuy, cmdSell, cmdProfile, cmdUse, cmdBM, cmdTips;
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
                        cmdBM.name("'bm baermelk'");
                        cmdBM.value("Take a shot at the boss. You will not be able to shop while fighting but you can use items any time.");
                        cmdTips.name("Tips");
                        cmdTips.value("Armor reduces damage taken by 50%.\n Sword reduces damage taken in close quarters by 25%. \n Bow reduces damage taken in a long range encounter by 25%.");
                        cmdFields.push_back(cmdProfile); cmdFields.push_back(cmdShop);
                        cmdFields.push_back(cmdAdventure); cmdFields.push_back(cmdBuy);
                        cmdFields.push_back(cmdSell); cmdFields.push_back(cmdUse); cmdFields.push_back(cmdBM); cmdFields.push_back(cmdTips);

                        aegis::gateway::objects::embed help;
                        help.title("List of Commands");
                        help.color(31);
                        help.fields(cmdFields);

                        std::vector<aegis::gateway::objects::field> itemFields;                           // shop vector
                        aegis::gateway::objects::field sword, bow, arrows, armor, healthKit, bandages;
                        sword.name("Sword <:sword:831267587370909766>");
                        sword.value("100 Gold <:goldcoin:829105003129995346>");
                        sword.is_inline(true);
                        bow.name("Bow :bow_and_arrow:");
                        bow.value("50 Gold <:goldcoin:829105003129995346>");
                        bow.is_inline(true);
                        arrows.name("Arrows(10) <:arrow:831269918372659210>");
                        arrows.value("25 Gold <:goldcoin:829105003129995346>");
                        arrows.is_inline(true);
                        armor.name("Armor <:armor:831273791535316992>");
                        armor.value("200 Gold <:goldcoin:829105003129995346>");
                        armor.is_inline(true);
                        healthKit.name("Health Kit <:health:831276638884855878>");
                        healthKit.value("100 Gold <:goldcoin:829105003129995346>");
                        healthKit.is_inline(true);
                        bandages.name("Bandages(5) :adhesive_bandage:");
                        bandages.value("50 Gold <:goldcoin:829105003129995346>");
                        bandages.is_inline(true);
                        itemFields.push_back(sword); itemFields.push_back(bow); itemFields.push_back(arrows); itemFields.push_back(armor); itemFields.push_back(healthKit); itemFields.push_back(bandages);

                        aegis::gateway::objects::embed shop;
                        shop.title("Shop");
                        shop.color(31);
                        shop.fields(itemFields);

                        std::vector<aegis::gateway::objects::field> stats;                  // Profile Vector
                        aegis::gateway::objects::field exp, gold, health;
                        exp.name("<:exp:832036952613322832> Experience: ");
                        exp.value(pexperience);
                        exp.is_inline(true);
                        gold.name("<:goldcoin:829105003129995346> Gold: ");
                        gold.value(pgold);
                        gold.is_inline(true);
                        health.name("<:health:831276638884855878> Health: ");
                        health.value(fmt::format("{}/100", phealth));
                        health.is_inline(true);
                        stats.push_back(exp);stats.push_back(gold);stats.push_back(health);

                        std::vector<aegis::gateway::objects::field> inventory;
                        aegis::gateway::objects::field lsword, larmor, lbow, larrows, lhealthkit, lbandages;
                        lsword.name("<:sword:831267587370909766> Sword: ");
                        lsword.value(psword);
                        lsword.is_inline(true);
                        lbow.name(":bow_and_arrow: Bow: ");
                        lbow.value(pbow);
                        lbow.is_inline(true);
                        larrows.name("<:arrow:831269918372659210> Arrows: ");
                        larrows.value(parrows);
                        larrows.is_inline(true);
                        larmor.name("<:armor:831273791535316992> Armor: ");
                        larmor.value(parmor);
                        larmor.is_inline(true);
                        lhealthkit.name("<:health:831276638884855878> Health Kit: ");
                        lhealthkit.value(phealthkit);
                        lhealthkit.is_inline(true);
                        lbandages.name(":adhesive_bandage: Bandages: ");
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
                        
                        if (content == "bm profile") {
                            _channel.create_message_embed("", profile);
                            _channel.create_message_embed("", linventory);
                        }
                        if (content == "bm help") {
                            _channel.create_message_embed("", help);
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
                                    healing.push_back(action);
                                    result.title("Healing:");
                                    result.color(31);
                                    result.fields(healing);
                                    _channel.create_message_embed("", result);
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
                        int weap; // 0 = bow  1 = sword;
                        if (pbm != "1" && pbm != "2" && pbm != "3"){
                        if (content == "test") {
                            deleteSpace();
                        }
                        
                        if (content == "bm start") {
                            _channel.create_message_embed("", start);
                        }
                        
                        if (content == "bm shop") {
                            _channel.create_message_embed("", shop);
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
                                    bitem.value("Obtained a sword <:sword:831267587370909766> for 100 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one sword <:sword:831267587370909766>");
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
                                    bitem.value("Obtained a bow :bow_and_arrow: for 50 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one bow :bow_and_arrow:");
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
                                    bitem.value("Obtained a 10 arrows <:arrow:831269918372659210> for 25 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry 30 arrows <:arrow:831269918372659210>");
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
                                    bitem.value("Obtained a set of armor <:armor:831273791535316992> for 200 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one set of armor <:armor:831273791535316992>");
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
                                    bitem.value("Obtained a health kit <:health:831276638884855878> for 100 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry one health kit <:health:831276638884855878>");
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
                                    bitem.value("Obtained a 5 bandages :adhesive_bandage: for 50 gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                                else {
                                    bitem.name("Transaction Incomplete");
                                    bitem.value("You don't have enough gold <:goldcoin:829105003129995346>");
                                    buying.push_back(bitem);
                                }
                            }
                            else {
                                bitem.name("Transaction Incomplete");
                                bitem.value("You can only carry 20 bandages :adhesive_bandage:");
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
                                bitem.value("Sold a sword <:sword:831267587370909766> for 100 gold <:goldcoin:829105003129995346>");
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
                                bitem.value("Sold a bow :bow_and_arrow: for 50 gold <:goldcoin:829105003129995346>");
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
                                bitem.value("Sold armor <:armor:831273791535316992> for 200 gold <:goldcoin:829105003129995346>");
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
                                bitem.value("Sold a health kit <:health:831276638884855878> for 100 gold <:goldcoin:829105003129995346>");
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
                                bitem.value("Sold 5 bandages :adhesive_bandage: for 50 gold <:goldcoin:829105003129995346>");
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
                                bitem.value("Sold 10 arrows <:arrow:831269918372659210> for 25 gold <:goldcoin:829105003129995346>");
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
                            int gold; int health; int oldGold; int newGold; int oldHealth; int newHealth; int oldExp; int newExp; int dead;

                            
                            srand(time(0));
                            //int num = rand() % 4;
                            int num = 3;
                            switch (num) {
                            case 0:
                                esituation.name("Holy Moly");
                                esituation.value("You found a HUGE SPIDER <:spider1:832049424963469312>");
                                gold = rand() % 60 + 75;
                                egold.value(fmt::format("You found {} gold <:goldcoin:829105003129995346>", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes") {
                                    health *= .5;
                                }
                                if (psword == "yes") {
                                    health -= (health * .25);
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
                                esituation.value("You defeated a CAVE TROLL <:troll:832049964283723787>");
                                gold = rand() % 25 + 50;
                                egold.value(fmt::format("You found {} gold <:goldcoin:829105003129995346>", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes") {
                                    health *= .5;
                                }
                                if (psword == "yes") {
                                    health -= (health * .25);
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
                                esituation.value("You discovered a pouch of gold <:goldcoin:829105003129995346>");
                                gold = rand() % 25 + 50;
                                egold.value(fmt::format("You found {} gold <:goldcoin:829105003129995346>", gold));
                                egold.name("Gold: ");
                                encounter.push_back(esituation); encounter.push_back(egold);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold + gold;
                                newHealth = stoi(phealth);
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;
                            case 3:
                                esituation.name("Oh No");
                                esituation.value("You were ambushed by bandits <:bandit:832051777188265995>");
                                gold = rand() % 30 + 15;
                                egold.value(fmt::format("You lost {} gold <:goldcoin:829105003129995346> ", gold));
                                egold.name("Gold: ");
                                health = rand() % 10 + 40;
                                if (parmor == "yes") {
                                    health *= .5;
                                }
                                if (pbow == "yes") {
                                    health -= (health * .25);
                                }
                                ehealth.value(fmt::format("You lost {} health!", health));
                                ehealth.name("Health: ");
                                encounter.push_back(esituation); encounter.push_back(egold); encounter.push_back(ehealth);

                                encount.title("Encounter:");
                                encount.color(31);
                                encount.fields(encounter);

                                oldGold = stoi(pgold);
                                newGold = oldGold - gold;
                                oldHealth = stoi(phealth);
                                newHealth = oldHealth - health;
                                oldExp = stoi(pexperience);
                                newExp = oldExp + 1;
                                break;
                            

                            }
                            if (newHealth <= 0) {
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
                            }


                        }

                        std::vector<aegis::gateway::objects::field> boss;
                        aegis::gateway::objects::field actions;
                        aegis::gateway::objects::embed final;
                        if (content == "bm baermelk") {                     // Beginning of baermelk
                            int exp = stoi(pexperience);
                            if (exp >= 10) {
                                replace(username, "bm", "1");
                                final.title("Baermelk <:health:831276638884855878>(100/100)");
                                actions.name("Congratulations on making it this far. Now time for the real test.");
                                actions.value("After some time walking, you see Baermelk in the distance... \n Choose sword or bow \n'sword' - charge with your sword or 'bow' - take some shots from the distance");
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
                    else if (pbm == "1") {                           //Stage 1
                    std::vector<aegis::gateway::objects::field> boss;
                    aegis::gateway::objects::field actions;
                    aegis::gateway::objects::embed final;
                            srand(time(0));
                            int health;
                            int oldH = stoi(phealth);
                            int bhealth;
                            int btot;
                            
                            if (content == "sword") {
                                int arrow = stoi(parrows);
                                if (psword == "yes") {
                                    actions.name("Charging with sword...");                          //fight w sword
                                    health = rand() % 5 + 30;
                                    bhealth = rand() % 5 + 20;
                                    btot = 100 - bhealth;
                                    replace(username, "weap", "1");
                                    actions.value(fmt::format("You took {} damage \n Baermelk is close and fighting back would you like to switch weapons? \n 'yes' or 'no'", health));
                                }
                                else if (pbow == "yes" && arrow > 0){
                                    actions.name("You don't have a sword! Switching to your bow.");                   //switch to bow        
                                    health = rand() % 5 + 20;
                                    bhealth = rand() % 5 + 40;
                                    btot = 100 - bhealth;
                                    arrow -= 5;
                                    replace(username, "weap", "0");
                                    actions.value(fmt::format("You took {} damage \n Baermelk is close and fighting back would you like to switch weapons? \n 'yes' or 'no'", health));
                                }
                                else {
                                    actions.name("You don't have a sword or a bow! Good luck...");              //hands        
                                    health = rand() % 5 + 45;
                                    bhealth = rand() % 5 + 15;
                                    btot = 100 - bhealth;
                                    actions.value(fmt::format("You took {} damage /n Baermelk is close and fighting back! You have no weapons to switch to.", health));
                                }
                                if (parmor == "yes") {    // lower damage
                                    health *= .5;
                                }
                                oldH -= health;
                                if (oldH <= 0) {
                                    pdeath(username, _channel);
                                }
                                else {
                                
                                boss.push_back(actions);
                                std::string newH = std::to_string(oldH);
                                replace(username, "health", newH);
                                std::string newA = std::to_string(arrow);
                                replace(username, "arrows", newA);
                                std::string btotH = std::to_string(btot);
                                replace(username, "bmH", btotH);
                                final.title(fmt::format("Baermelk <:health:831276638884855878>({}/100)", btot));
                                final.color(31);
                                final.fields(boss);
                                _channel.create_message_embed("", final);
                                }
                                
                            }
                            else if (content == "bow") {
                                int arrow = stoi(parrows);
                                if (pbow == "yes" && arrow > 0) {
                                    actions.name("Shooting from a distance...");                   //switch to bow        
                                    health = rand() % 5 + 20;
                                    bhealth = rand() % 5 + 40;
                                    btot = 100 - bhealth;
                                    arrow -= 5;
                                    replace(username, "weap", "0");
                                    actions.value(fmt::format("You took {} damage \n Baermelk is close and fighting back would you like to switch weapons? \n 'yes' or 'no'", health));
                                }
                                else if(psword == "yes"){
                                    actions.name("You either don't have a bow or arrows! Charging with sword...");                          //fight w sword
                                    health = rand() % 5 + 30;
                                    bhealth = rand() % 5 + 20;
                                    btot = 100 - bhealth;
                                    replace(username, "weap", "1");
                                    actions.value(fmt::format("You took {} damage \n Baermelk is close and fighting back would you like to switch weapons? \n 'yes' or 'no'", health));
                                }
                                else {
                                    actions.name("You don't have a sword or a bow! Good luck...");              //hands        
                                    health = rand() % 5 + 45;
                                    bhealth = rand() % 5 + 15;
                                    btot = 100 - bhealth;
                                    actions.value(fmt::format("You took {} damage \n Baermelk is close and fighting back! You have no weapons to switch to.", health));
                                }
                                if (parmor == "yes") {
                                    health *= .5;
                                }
                                oldH -= health; 
                                if (oldH <= 0) {
                                    pdeath(username, _channel);
                                }
                                else {
                                    
                                    boss.push_back(actions);
                                    std::string newH = std::to_string(oldH);
                                    replace(username, "health", newH);
                                    std::string newA = std::to_string(arrow);
                                    replace(username, "arrows", newA);
                                    std::string btotH = std::to_string(btot);
                                    replace(username, "bmH", btotH);
                                    final.title(fmt::format("Baermelk ({}/100)", btot));
                                    final.color(31);
                                    final.fields(boss);
                                    _channel.create_message_embed("", final);
                                }
                            }
                            replace(username, "bm", "2");
                        }
                        else if (pbm == "2") {
                        std::vector<aegis::gateway::objects::field> boss;
                        aegis::gateway::objects::field actions;
                        aegis::gateway::objects::embed final;
                        srand(time(0));
                        int health;
                        int oldH = stoi(phealth);
                        int bhealth;
                        int btot;
                        int arrow = stoi(parrows);
                        int bearH = stoi(pbmH);

                        if (pbow == "no" && psword == "no" && parrows == "0") {
                            actions.name("How have you made it this far with no weapons!?");
                            health = rand() % 5 + 55;
                            bhealth = rand() % 5 + 10;
                            btot = bearH - bhealth;
                            actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                        }
                        else if (content == "yes") {         //switch
                            if (pweap == "1") {      //sword
                                if (pbow == "yes" && arrow > 0) {
                                actions.name("Switching to bow, not as effective for close range combat...");                          
                                health = rand() % 5 + 35;
                                bhealth = rand() % 5 + 15;
                                btot = bearH - bhealth;
                                arrow -= 5;
                                replace(username, "weap", "0");
                                actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                                }
                                else {
                                    actions.name("You do not have a bow to switch to or you have no arrows! Using last used weapon.");
                                    health = rand() % 5 + 30;
                                    bhealth = rand() % 5 + 40;
                                    btot = bearH - bhealth;
                                    
                                    actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                                }

                                
                            }
                            else if(pweap == "0"){   // bow
                                if (psword == "yes") {
                                actions.name("Switching to sword, very effective for close range combat...");                          //fight w sword
                                health = rand() % 5 + 30;
                                bhealth = rand() % 5 + 40;
                                btot = bearH - bhealth;
                                replace(username, "weap", "1");
                                actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                                }
                                else {
                                    actions.name("You do not have a sword to switch to! Using last used weapon.");
                                    health = rand() % 5 + 35;
                                    bhealth = rand() % 5 + 15;
                                    btot = bearH - bhealth;
                                    if (pbow == "yes") {
                                        arrow -= 5;
                                    }
                                    
                                    actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                                }
                                
                            }
                            if (parmor == "yes") {
                                health *= .5;
                            }
                            oldH -= health;
                            if (oldH <= 0) {
                                pdeath(username, _channel);
                            }
                            else {

                                boss.push_back(actions);
                                std::string newH = std::to_string(oldH);
                                replace(username, "health", newH);
                                std::string newA = std::to_string(arrow);
                                replace(username, "arrows", newA);
                                std::string btotH = std::to_string(btot);
                                replace(username, "bmH", btotH);
                                final.title(fmt::format("Baermelk ({}/100)", btot));
                                final.color(31);
                                final.fields(boss);
                                _channel.create_message_embed("", final);
                            }
                        }
                        else if (content == "no") {          // dont switch
                            if (pweap == "1") {      //sword
                                actions.name("Using sword, very effective for close range combat...");                          //fight w sword
                                health = rand() % 5 + 30;
                                bhealth = rand() % 5 + 40;
                                btot = bearH - bhealth;
                                
                                actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health)); 
                            }
                            else if (pweap == "0") {   // bow
                                actions.name("Using bow, not as effective for close range combat...");
                                health = rand() % 5 + 35;
                                bhealth = rand() % 5 + 15;
                                btot = bearH - bhealth;
                                
                                actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));

                            }
                            if (parmor == "yes") {
                                health *= .5;
                            }
                            oldH -= health;
                            if (oldH <= 0) {
                                pdeath(username, _channel);
                            }
                            else {

                                boss.push_back(actions);
                                std::string newH = std::to_string(oldH);
                                replace(username, "health", newH);
                                std::string newA = std::to_string(arrow);
                                replace(username, "arrows", newA);
                                std::string btotH = std::to_string(btot);
                                replace(username, "bmH", btotH);
                                final.title(fmt::format("Baermelk ({}/100)", btot));
                                final.color(31);
                                final.fields(boss);
                                _channel.create_message_embed("", final);
                            }
                            }
                         replace(username, "bm", "3");
                        }
                        else if (pbm == "3") {
                        std::vector<aegis::gateway::objects::field> boss;
                        aegis::gateway::objects::field actions;
                        aegis::gateway::objects::embed final;
                        srand(time(0));
                        int health;
                        int oldH = stoi(phealth);
                        int bhealth;
                        int btot;
                        int arrow = stoi(parrows);
                        int bearH = stoi(pbmH);
                        if (content == "yes") {
                            if (psword == "no" && ((pbow == "no") || (arrow == 0))) {
                                pdeath(username, _channel);
                            }
                            if (pweap == "1") {
                                health = rand() % 5 + 65;
                                bhealth = rand() % 5 + 35;
                                btot = bearH - bhealth;
                                if (btot <= 0) {
                                    actions.name("We are proud.");
                                    actions.value("Youre now classified as a god");
                                    replace(username, "exp", "111");
                                    replace(username, "bm", "0");
                                    
                                }
                                else {
                                    actions.name("Baermelk has fled the scene");
                                    actions.value("You are lucky enough to try again");
                                    replace(username, "bm", "0");
                                    replace(username, "bmH", "0");
                                }
                            }
                            if (pweap == "0") {
                                health = rand() % 5 + 65;
                                bhealth = rand() % 5 + 25;
                                arrow -= 5;
                                btot = bearH - bhealth;
                                if (btot <= 0) {
                                    actions.name("We are proud.");
                                    actions.value("Youre now classified as a god");
                                    replace(username, "exp", "Godly");
                                    replace(username, "bm", "0");
                                    
                                }
                                else {
                                    actions.name("Baermelk has fled the scene");
                                    actions.value("You are lucky enough to try again");
                                    replace(username, "bm", "0");
                                    replace(username, "bmH", "0");
                                }
                            }
                            if (parmor == "yes") {
                                health *= .5;
                            }
                            oldH -= health;
                            if (oldH <= 0) {
                                pdeath(username, _channel);
                            }
                            else {

                                boss.push_back(actions);
                                std::string newH = std::to_string(oldH);
                                replace(username, "health", newH);
                                std::string newA = std::to_string(arrow);
                                replace(username, "arrows", newA);
                                std::string btotH = std::to_string(btot);
                                replace(username, "bmH", "100");
                                if (btot <= 0) {
                                    final.title("Congratulations you have beaten Baermelk!");
                                    
                                }
                                else {
                                    final.title(fmt::format("You were so close!", btot));
                                }
                                
                                final.color(31);
                                final.fields(boss);
                                _channel.create_message_embed("", final);
                            }
                            }
                        if (content == "no") {
                            actions.name("Using bow, not as effective for close range combat...");
                            actions.value(fmt::format("You took {} damage \n Baermelk is angry, his attacks will cause more damage. Would you like to continue? (recommendation: heal)  \n 'yes' or 'no'", health));
                        }
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
    if (item == "bmH") {
        loopNum = 10;
    }
    if (item == "weap") {
        loopNum = 11;
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
void pdeath(std::string username, aegis::channel &_chan) {
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
    replace(username, "bmH", "100");
    replace(username, "weap", "-1");
}