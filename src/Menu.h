#pragma once

#include <functional>

namespace Menu
{
    void AddItem (std::string ItemName, std::function<void (void)> Callback);
    void Clear ();
    void Run ();
}