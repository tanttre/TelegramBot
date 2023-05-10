#pragma once

#include <iostream>
#include <tgbot/tgbot.h>
#include <vector>
#include <string>
#include <ctime>
#include <curl/curl.h>
#include "json.hpp"

std::vector<std::string> bot_commands = {"start", "time", "currency"};