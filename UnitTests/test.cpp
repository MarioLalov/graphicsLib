#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <nlohmann/json.hpp>
#include "../Managers/FactoryManager/FactoryManager.h"

using node_ptr = std::shared_ptr<Node>;

TEST_CASE("Node transformations") {
    RssManager rssMgr;
    FactoryManager factoryMgr(rssMgr);

    auto root = factoryMgr.CreateNode("ROOT");

    auto lvl1ch1 = factoryMgr.CreateNode("LVL1_CH1");
    auto lvl1ch2 = factoryMgr.CreateNode("LVL1_CH2");

    auto lvl2ch1 = factoryMgr.CreateNode("LVL2_CH1");

    root->add_child(lvl1ch1);
    root->add_child(lvl1ch2);

    lvl1ch1->add_child(lvl2ch1);

	SECTION("Sequential position setting") {
        root->set_position({50, 20});
        lvl1ch1->set_position({30, 10});
        lvl2ch1->set_position({6, 7});

		REQUIRE(lvl1ch1->get_global_position().x == 80);
        REQUIRE(lvl1ch1->get_global_position().y == 30);

        REQUIRE(lvl2ch1->get_global_position().x == 86);
        REQUIRE(lvl2ch1->get_global_position().y == 37);
	}

    SECTION("Non-sequential position setting") {
        lvl1ch1->set_position({30, 10});
        lvl2ch1->set_position({6, 7});
        root->set_position({50, 20});

		REQUIRE(lvl1ch1->get_global_position().x == 80);
        REQUIRE(lvl1ch1->get_global_position().y == 30);

        REQUIRE(lvl2ch1->get_global_position().x == 86);
        REQUIRE(lvl2ch1->get_global_position().y == 37);
	}

    SECTION("Sequential rotation setting") {
        std::cout << "Rotate Root" << std::endl;
        root->set_rotation(30);
        std::cout << "Rotate lvl1ch1" << std::endl;
        lvl1ch1->set_rotation(60);
        std::cout << "Rotate lvl2ch1" << std::endl;
        lvl2ch1->set_rotation(34);

		REQUIRE(lvl1ch1->get_global_rotation() == 90);
        
        REQUIRE(lvl2ch1->get_global_rotation() == 124);
	}

    // SECTION("Non-sequential rotation setting") {
    //     lvl1ch1->set_position({30, 10});
    //     lvl2ch1->set_position({6, 7});
    //     root->set_position({50, 20});

	// 	REQUIRE(lvl1ch1->get_global_position().x == 80);
    //     REQUIRE(lvl1ch1->get_global_position().y == 30);

    //     REQUIRE(lvl2ch1->get_global_position().x == 86);
    //     REQUIRE(lvl2ch1->get_global_position().y == 37);
	// }
}