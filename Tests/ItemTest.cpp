/**
 * @file ItemTest.cpp
 * @author Tyler Stefan
 */

#include <pch.h>


#include "gtest/gtest.h"
#include <FactoryGame.h>
#include <Item.h>


TEST(ItemTest, Construct)
{
    FactoryGame game;
    Item item(&game);

    ASSERT_EQ(item.GetGame(), &game);
}
