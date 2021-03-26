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



using json = nlohmann::json;
using aegis::rest::rest_reply;
using aegis::gateway::objects::message;

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    try
    {
        // Create bot object
        aegis::core bot(aegis::create_bot_t().log_level(spdlog::level::trace).token("ODE0OTc2NzgzMDUyNTcwNjI0.YDlsRg.mPiA0iXU17jmKh-glFZhuP1RESs"));

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


                    if (content == "~Hi")
                    {
                        _channel.create_message("Hello back");
                    }
                    else if (content == "~React")
                    {
                        obj.msg.create_reaction("success:429554838083207169").then([&, msg = obj.msg](aegis::rest::rest_reply reply) mutable
                        {
                            if (reply)
                            {
                                // reaction was a success. chain another?
                                msg.create_reaction("fail:429554869611921408").then([&](aegis::rest::rest_reply reply)
                                    {
                                        if (reply)
                                            _channel.create_message("React complete");
                                        else
                                            _channel.create_message("React failed");
                                    });
                            }
                        });
                    }
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

                    std::vector<aegis::gateway::objects::field> cmdFields;
                    aegis::gateway::objects::field cmdShop, cmdAdventure, cmdBuy, cmdSell;
                    cmdShop.name("'bm shop'");
                    cmdShop.value("Shows all available items to purchase");
                    cmdAdventure.name("'bm adventure'");
                    cmdAdventure.value("May encounter dangerous mobs and/or find loot");
                    cmdBuy.name("'bm buy [item]'");
                    cmdBuy.value("Purchase items in the shop");
                    cmdSell.name("'bm sell [item]'");
                    cmdSell.value("Sell items you own");
                    cmdFields.push_back(cmdShop); cmdFields.push_back(cmdAdventure); cmdFields.push_back(cmdBuy); cmdFields.push_back(cmdSell);

                    aegis::gateway::objects::embed help;
                    help.title("List of Commands");
                    help.color(31);
                    help.fields(cmdFields);

                    std::vector<aegis::gateway::objects::field> itemFields;
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
                    
                    if (content == "bm start") {
                        _channel.create_message_embed("", start);
                    }
                    if (content == "bm help") {
                        _channel.create_message_embed("", help);
                    }if (content == "bm shop") {
                        _channel.create_message_embed("", shop);
                    }
                    if (content == "bm adventure") {
                        int gold;
                        int health;
                        bool flee = false;
                        _channel.create_message("You may encounter dangerous mobs and/or find loot...");
                        srand(time(0));
                        int num = rand() % 3 + 1;
                        switch (num) {
                        case 0:
                            gold = rand() % 25 + 25;
                            _channel.create_message(fmt::format("You found {} gold!", gold));
                            break;
                        case 1:
                            gold = rand() % 25 + 25;
                            _channel.create_message(fmt::format("You found {} gold!", gold));
                            //_channel.create_message("You found encountered a poisonous spider. \n Do you wish to flee or kill?");
                            //std::string content{ obj.msg.get_content() };
                            //if (content == "flee") {
                            //    _channel.create_message("You got away safely");
                            //}
                            //else if (content == "kill") {
                            //    health = rand() % 15 + 10;
                            //    _channel.create_message(fmt::format("You lost {} health!", health));
                            //}
                            break;
                        case 2:
                            health = rand() % 25 + 25;
                            _channel.create_message(fmt::format("You killed a giant spider! But you lost {} health :(", health));
                            break;
                        case 3:
                            _channel.create_message("You found a set of old armor!");
                            break;
                        }
                    }
                    // Send a message, wait for message to successfully be sent, then react to that message
                    else if (content == "~Delay")
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