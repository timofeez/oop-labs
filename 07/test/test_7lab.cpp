#include <gtest/gtest.h>
#include "dungeon.h"
#include "npc.h"
#include "observer.h"
#include "visitor.h"
#include <sstream>


TEST(NPCTest, CreateNPC) {
    Squirrel squirrel("Squeaky", 10, 15);
    Werewolf werewolf("Howler", 20, 25);
    Druid druid("Gandalf", 30, 35);

    EXPECT_EQ(squirrel.getName(), "Squeaky");
    EXPECT_EQ(werewolf.getX(), 20);
    EXPECT_EQ(druid.getY(), 35);
}




TEST(NPCTest, GetType) {
    Squirrel squirrel("Squeaky", 10, 15);
    Werewolf werewolf("Howler", 20, 25);
    Druid druid("Gandalf", 30, 35);
    EXPECT_EQ(squirrel.getType(), "Squirrel");
    EXPECT_EQ(werewolf.getType(), "Werewolf");
    EXPECT_EQ(druid.getType(), "Druid");
}


TEST(DungeonTest, AddNPC) {
    Dungeon dungeon;
    auto squirrel = std::make_shared<Squirrel>("Squeaky", 10, 15);
    dungeon.addNPC(squirrel);
    EXPECT_EQ(dungeon.popNPC(0)->getName(), "Squeaky");
}


TEST(DungeonTest, PrintNPCs) {
    Dungeon dungeon;
    auto squirrel = std::make_shared<Squirrel>("Squeaky", 10, 15);
    auto werewolf = std::make_shared<Werewolf>("Howler", 20, 25);
    dungeon.addNPC(squirrel);
    dungeon.addNPC(werewolf);
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf());
    dungeon.printNPCs();
    std::cout.rdbuf(old_buf);
    EXPECT_NE(output.str().find("Squirrel"), std::string::npos);
    EXPECT_NE(output.str().find("Howler"), std::string::npos);
}


TEST(DungeonTest, SaveAndLoadNPCs) {
    Dungeon dungeon;
    auto squirrel = std::make_shared<Squirrel>("Squeaky", 10, 15);
    auto werewolf = std::make_shared<Werewolf>("Howler", 20, 25);
    dungeon.addNPC(squirrel);
    dungeon.addNPC(werewolf);
    dungeon.saveToFile("test_npcs.txt");
    Dungeon newDungeon;
    newDungeon.loadFromFile("test_npcs.txt");
    EXPECT_EQ(newDungeon.popNPC(0)->getName(), "Squeaky");
    EXPECT_EQ(newDungeon.popNPC(0)->getName(), "Howler");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
