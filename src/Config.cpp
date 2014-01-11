/**
 * @file   Config.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  XML configuration parser
 *
 **/
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Config.h"

using namespace nsGame;
using namespace nsConsole;

unsigned            nsConfig::RenderLoopInterval;
unsigned            nsConfig::ErrorMessageDisplayTime;
unsigned            nsConfig::TurnTimeoutDelay;
unsigned            nsConfig::BotPlayDelay;
BackgroundColors    nsConfig::BorderColor;
BackgroundColors    nsConfig::CaseColor1;
BackgroundColors    nsConfig::CaseColor2;
BackgroundColors    nsConfig::MenuBorderColor;

void nsGame::nsConfig::LoadFile ()
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
} // LoadFile