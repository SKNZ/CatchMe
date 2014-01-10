#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Config.h"

unsigned Game::Config::RenderLoopInterval;
unsigned Game::Config::ErrorMessageDisplayTime;
unsigned Game::Config::TurnTimeoutDelay;
unsigned Game::Config::BotPlayDelay;

void Game::Config::LoadFile ()
{
    using boost::property_tree::ptree;
    ptree PropertyTree;
    
    read_xml (KFileName, PropertyTree);
    
    RenderLoopInterval      = PropertyTree.get  ("Conf.RenderLoopInterval",         100);
    ErrorMessageDisplayTime = PropertyTree.get  ("Conf.ErrorMessageDisplayTime",    1000);
    TurnTimeoutDelay        = PropertyTree.get  ("Conf.TurnTimeoutDelay",           15000);
    BotPlayDelay            = PropertyTree.get  ("Conf.BotPlayDelay",               500);
}