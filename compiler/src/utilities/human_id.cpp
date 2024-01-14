// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
// human_id.cpp
#include "human_id.h"
#include <ios>
#include <random>
#include <sstream>
// words from = https://gist.github.com/prschmid/4447660
using namespace yaksha;
#ifdef YAKSHA_DEBUG
static std::random_device rd;
#else
std::mt19937 predictable_random{20};
static auto rd() { return predictable_random(); }
#endif
static std::vector<std::mt19937> generators_{
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
    std::mt19937{rd()}, std::mt19937{rd()}, std::mt19937{rd()},
};
static std::mt19937_64 base_random{rd() ^ rd() ^ 0xDEADBEEF};
static std::uniform_int_distribution<> g(0, (int) generators_.size() - 1);
static std::uniform_int_distribution<> num_d(10, 99);
static std::vector<std::string> adjective{
    "adorable",     "adventurous", "alluring",   "amazing",      "ambitious",
    "amusing",      "astonishing", "attractive", "awesome",      "bashful",
    "bawdy",        "beautiful",   "bewildered", "bizarre",      "bouncy",
    "brainy",       "brave",       "brawny",     "burly",        "capricious",
    "careful",      "caring",      "cautious",   "charming",     "cheerful",
    "chivalrous",   "classy",      "clever",     "clumsy",       "colossal",
    "cool",         "coordinated", "courageous", "cuddly",       "curious",
    "cute",         "daffy",       "dapper",     "dashing",      "dazzling",
    "delicate",     "delightful",  "determined", "eager",        "embarrassed",
    "enchanted",    "energetic",   "enormous",   "entertaining", "enthralling",
    "enthusiastic", "evanescent",  "excited",    "exotic",       "exuberant",
    "exultant",     "fabulous",    "fancy",      "festive",      "finicky",
    "flashy",       "flippant",    "fluffy",     "fluttering",   "funny",
    "furry",        "fuzzy",       "gaudy",      "gentle",       "giddy",
    "glamorous",    "gleaming",    "goofy",      "gorgeous",     "graceful",
    "grandiose",    "groovy",      "handsome",   "happy",        "hilarious",
    "honorable",    "hulking",     "humorous",   "industrious",  "incredible",
    "intelligent",  "jazzy",       "jolly",      "joyous",       "kind",
    "macho",        "magnificent", "majestic",   "marvelous",    "mighty",
    "mysterious",   "naughty",     "nimble",     "nutty",        "oafish",
    "obnoxious",    "outrageous",  "pretty",     "psychedelic",  "psychotic",
    "puzzled",      "quirky",      "quizzical",  "rambunctious", "remarkable",
    "sassy",        "shaggy",      "smelly",     "sneaky",       "spiffy",
    "swanky",       "sweet",       "swift",      "talented",     "thundering",
    "unkempt",      "upbeat",      "uppity",     "wacky",        "waggish",
    "whimsical",    "wiggly",      "zany"};
static std::uniform_int_distribution<> adjective_d(0,
                                                   (int) adjective.size() - 1);
static std::vector<std::string> noun{
    "aardvarks",    "alligators",   "alpacas",     "anteaters",  "antelopes",
    "armadillos",   "baboons",      "badgers",     "bears",      "beavers",
    "boars",        "buffalos",     "bulls",       "bunnies",    "camels",
    "cats",         "chameleons",   "cheetahs",    "centaurs",   "chickens",
    "chimpanzees",  "chinchillas",  "chipmunks",   "cougars",    "cows",
    "coyotes",      "cranes",       "crickets",    "crocodiles", "deers",
    "dinasaurs",    "dingos",       "dogs",        "donkeys",    "dragons",
    "elephants",    "elves",        "ferrets",     "flamingos",  "foxes",
    "frogs",        "gazelles",     "giraffes",    "gnomes",     "gnus",
    "goats",        "gophers",      "gorillas",    "hamsters",   "hedgehogs",
    "hippopotamus", "hobbits",      "hogs",        "horses",     "hyenas",
    "ibexes",       "iguanas",      "impalas",     "jackals",    "jackalopes",
    "jaguars",      "kangaroos",    "kittens",     "koalas",     "lambs",
    "lemmings",     "leopards",     "lions",       "ligers",     "lizards",
    "llamas",       "lynxes",       "meerkat",     "moles",      "mongooses",
    "monkeys",      "moose",        "mules",       "newts",      "okapis",
    "orangutans",   "ostriches",    "otters",      "oxes",       "pandas",
    "panthers",     "peacocks",     "pegasuses",   "phoenixes",  "pigeons",
    "pigs",         "platypuses",   "ponies",      "porcupines", "porpoises",
    "pumas",        "pythons",      "rabbits",     "raccoons",   "rams",
    "reindeers",    "rhinoceroses", "salamanders", "seals",      "sheep",
    "skunks",       "sloths",       "slugs",       "snails",     "snakes",
    "sphinxes",     "sprites",      "squirrels",   "takins",     "tigers",
    "toads",        "trolls",       "turtles",     "unicorns",   "walruses",
    "warthogs",     "weasels",      "wolves",      "wolverines", "wombats",
    "woodchucks",   "yaks",         "zebras"};
static std::uniform_int_distribution<> noun_d(0, (int) noun.size() - 1);
static std::vector<std::string> verb{
    "ambled",    "assembled", "burst",     "babbled",   "charged",  "chewed",
    "clamored",  "coasted",   "crawled",   "crept",     "danced",   "dashed",
    "drove",     "flopped",   "galloped",  "gathered",  "glided",   "hobbled",
    "hopped",    "hurried",   "hustled",   "jogged",    "juggled",  "jumped",
    "laughed",   "marched",   "meandered", "munched",   "passed",   "plodded",
    "pranced",   "ran",       "raced",     "rushed",    "sailed",   "sang",
    "sauntered", "scampered", "scurried",  "skipped",   "slogged",  "slurped",
    "spied",     "sprinted",  "spurted",   "squiggled", "squirmed", "stretched",
    "strode",    "strut",     "swam",      "swung",     "traveled", "trudged",
    "tumbled",   "twisted",   "wade",      "wandered",  "whistled", "wiggled",
    "wobbled",   "yawned",    "zipped",    "zoomed"};
static std::uniform_int_distribution<> verb_d(0, (int) verb.size() - 1);
static std::vector<std::string> adverb{"absentmindedly",
                                       "adventurously",
                                       "angrily",
                                       "anxiously",
                                       "awkwardly",
                                       "bashfully",
                                       "beautifully",
                                       "bleakly",
                                       "blissfully",
                                       "boastfully",
                                       "boldly",
                                       "bravely",
                                       "briskly",
                                       "calmly",
                                       "carefully",
                                       "cautiously",
                                       "cheerfully",
                                       "cleverly",
                                       "cluelessly",
                                       "clumsily",
                                       "coaxingly",
                                       "colorfully",
                                       "coolly",
                                       "courageously",
                                       "curiously",
                                       "daintily",
                                       "defiantly",
                                       "deliberately",
                                       "delightfully",
                                       "diligently",
                                       "dreamily",
                                       "drudgingly",
                                       "eagerly",
                                       "effortlessly",
                                       "elegantly",
                                       "energetically",
                                       "enthusiastically",
                                       "excitedly",
                                       "fervently",
                                       "foolishly",
                                       "furiously",
                                       "gallantly",
                                       "gently",
                                       "gladly",
                                       "gleefully",
                                       "gracefully",
                                       "gratefully",
                                       "happily",
                                       "hastily",
                                       "haphazardly",
                                       "hungrily",
                                       "innocently",
                                       "inquisitively",
                                       "intensely",
                                       "jokingly",
                                       "joshingly",
                                       "joyously",
                                       "jovially",
                                       "jubilantly",
                                       "kiddingly",
                                       "knavishly",
                                       "knottily",
                                       "kookily",
                                       "lazily",
                                       "loftily",
                                       "longingly",
                                       "lovingly",
                                       "loudly",
                                       "loyally",
                                       "madly",
                                       "majestically",
                                       "merrily",
                                       "mockingly",
                                       "mysteriously",
                                       "nervously",
                                       "noisily",
                                       "obnoxiously",
                                       "oddly",
                                       "optimistically",
                                       "overconfidently",
                                       "outside",
                                       "owlishly",
                                       "patiently",
                                       "playfully",
                                       "politely",
                                       "powerfully",
                                       "purposefully",
                                       "quaintly",
                                       "quarrelsomely",
                                       "queasily",
                                       "quickly",
                                       "quietly",
                                       "quirkily",
                                       "quizzically",
                                       "rapidly",
                                       "reassuringly",
                                       "recklessly",
                                       "reluctantly",
                                       "reproachfully",
                                       "sadly",
                                       "scarily",
                                       "seriously",
                                       "shakily",
                                       "sheepishly",
                                       "shyly",
                                       "silently",
                                       "sillily",
                                       "sleepily",
                                       "slowly",
                                       "speedily",
                                       "stealthily",
                                       "sternly",
                                       "suspiciously",
                                       "sweetly",
                                       "tenderly",
                                       "tensely",
                                       "thoughtfully",
                                       "triumphantly",
                                       "unabashedly",
                                       "unaccountably",
                                       "urgently",
                                       "vainly",
                                       "valiantly",
                                       "victoriously",
                                       "warmly",
                                       "wearily",
                                       "youthfully",
                                       "zestfully"};
static std::uniform_int_distribution<> adverb_d(0, (int) adverb.size() - 1);
static std::mt19937 &gen() { return generators_[g(base_random)]; }
std::string yaksha::human_id::human_id() {
  std::stringstream text{};
  text << "the-";
  text << num_d(gen());
  text << "-";
  text << adjective[adjective_d(gen())];
  text << "-";
  text << noun[noun_d(gen())];
  text << "-";
  text << verb[verb_d(gen())];
  text << "-";
  text << adverb[adverb_d(gen())];
  text << "-";
  text << num_d(gen());
  text << "-";
  text << num_d(gen());
  return text.str();
}
// Based on -- https://stackoverflow.com/a/60198074
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);
std::string yaksha::human_id::low_entropy_uuid() {
  std::stringstream ss{};
  int i;
  ss << std::hex;
  for (i = 0; i < 8; i++) { ss << dis(gen()); }
  ss << "-";
  for (i = 0; i < 4; i++) { ss << dis(gen()); }
  ss << "-4";
  for (i = 0; i < 3; i++) { ss << dis(gen()); }
  ss << "-";
  ss << dis2(gen());
  for (i = 0; i < 3; i++) { ss << dis(gen()); }
  ss << "-";
  for (i = 0; i < 12; i++) { ss << dis(gen()); };
  return ss.str();
}
