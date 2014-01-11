#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Config.h"

using namespace NSGame;
using namespace Console;

unsigned            Config::RenderLoopInterval;
unsigned            Config::ErrorMessageDisplayTime;
unsigned            Config::TurnTimeoutDelay;
unsigned            Config::BotPlayDelay;
BackgroundColors    Config::BorderColor;
BackgroundColors    Config::CaseColor1;
BackgroundColors    Config::CaseColor2;
BackgroundColors    Config::MenuBorderColor;

void NSGame::Config::LoadFile ()
{
    using boost::property_tree::ptree;
    ptree PropertyTree;
    
    read_xml (KFileName, PropertyTree);
    
    RenderLoopInterval      = PropertyTree.get ("Conf.RenderLoopInterval",         100);
    ErrorMessageDisplayTime = PropertyTree.get ("Conf.ErrorMessageDisplayTime",    1000);
    TurnTimeoutDelay        = PropertyTree.get ("Conf.TurnTimeoutDelay",           15000);
    BotPlayDelay            = PropertyTree.get ("Conf.BotPlayDelay",               500);
    BorderColor             = static_cast<BackgroundColors> (PropertyTree.get ("Conf.BorderColor",      static_cast<int> (BackgroundColors::KGreen)));
    CaseColor1              = static_cast<BackgroundColors> (PropertyTree.get ("Conf.CaseColor1",       static_cast<int> (BackgroundColors::KBlack)));
    CaseColor2              = static_cast<BackgroundColors> (PropertyTree.get ("Conf.CaseColor2",       static_cast<int> (BackgroundColors::KBlue)));
    MenuBorderColor         = static_cast<BackgroundColors> (PropertyTree.get ("Conf.MenuBorderColor",  static_cast<int> (BackgroundColors::KMagenta)));
}