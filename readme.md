TGBOT source = https://github.com/reo7sp/tgbot-cpp
PARSER(json.hpp) = https://github.com/nlohmann/json
TELEGRAM BOT
    commands:
        /start - старт
        /time - время (МСК +3)
        /currency (курс валют(доллар / евро) к рублю)
BUILD : g++ telegram_bot.cpp -o telegram_bot --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread -lcurl