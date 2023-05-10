#include "includes.h"
#include "commands.h"

int main() 
{
    // Логика
    TgBot::Bot bot("ТОКЕН"); // !!!

    // Окна в чате
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    TgBot::InlineKeyboardButton::Ptr usd_btn(new TgBot::InlineKeyboardButton), eur_btn(new TgBot::InlineKeyboardButton);

    usd_btn->text = "USD";
    eur_btn->text = "EUR";
    usd_btn->callbackData = "USD";
    eur_btn->callbackData = "EUR";
    buttons.push_back(usd_btn);
    buttons.push_back(eur_btn);
    keyboard->inlineKeyboard.push_back(buttons);

    // Команды
    // 1
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) 
    {
        bot.getApi().sendMessage(message->chat->id, "Hi, " + message->chat->firstName);
    });

    // 2
    bot.getEvents().onCommand("time", [&bot](TgBot::Message::Ptr message) 
    {
        bot.getApi().sendMessage(message->chat->id, "Moscow time:\n" + get_time_as_string());
    });

    // 3
    bot.getEvents().onCommand("currency", [&bot, &keyboard](TgBot::Message::Ptr message) 
    {
        bot.getApi().sendMessage(message->chat->id ,"How currency?", false, 0, keyboard);
    });
    
    // Технические команды

    // 1
    bot.getEvents().onCallbackQuery([&bot, &keyboard](TgBot::CallbackQuery::Ptr query)
    {
        if (query->data == "USD")
            bot.getApi().sendMessage(query->message->chat->id, std::to_string(get_currency('u')));
        else
            bot.getApi().sendMessage(query->message->chat->id, std::to_string(get_currency('e')));
    });

    // Проверка на команду
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) 
    {
        for (const auto& command : bot_commands)
            if ("/" + command == message->text)
                return;
        
        bot.getApi().sendMessage(message->chat->id, "Sorry, i don`t know :(");
    });

    // Технический RunTime (НЕ ТРОГАТЬ)
    try 
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) 
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    } 
    catch (TgBot::TgException& e) 
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}