#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <nlohmann/json.hpp>
#include "../Managers/FactoryManager/FactoryManager.h"

using node_ptr = std::shared_ptr<Node>;

static auto roundFloat(float f, uint16_t decimalPoint = 7) -> float
{
    static auto ROUNDING_BASE = std::pow(10.0f, decimalPoint);
    return std::round(f*ROUNDING_BASE) / ROUNDING_BASE;
}

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
        root->set_rotation(30);
        lvl1ch1->set_rotation(60);
        lvl2ch1->set_rotation(34);

		REQUIRE(roundFloat(lvl1ch1->get_global_rotation(), 1) == 90);
        
        REQUIRE(roundFloat(lvl2ch1->get_global_rotation(), 1) == 124);
	}

    SECTION("Non-sequential rotation setting") {
        lvl1ch1->set_rotation(60);
        lvl2ch1->set_rotation(34);
        root->set_rotation(30);

		REQUIRE(roundFloat(lvl1ch1->get_global_rotation(), 1) == 90);
        
        REQUIRE(roundFloat(lvl2ch1->get_global_rotation(), 1) == 124);
	}

    SECTION("Sequential scale setting") {
        root->set_scale({2.0f, 2.0f});
        lvl1ch1->set_scale({1.5f, 1.7f});
        lvl2ch1->set_scale({0.33f, 0.2941f});

		REQUIRE(roundFloat(lvl1ch1->get_global_scale().x, 1) == 3.0f);
        REQUIRE(roundFloat(lvl1ch1->get_global_scale().y, 1) == 3.4f);

        REQUIRE(roundFloat(lvl2ch1->get_global_scale().x, 1) == 1.0f);
        REQUIRE(roundFloat(lvl2ch1->get_global_scale().y, 1) == 1.0f);   
	}

    SECTION("Non-sequential scale setting") {
        lvl1ch1->set_scale({1.5f, 1.7f});
        lvl2ch1->set_scale({0.33f, 0.2941f});
        root->set_scale({2.0f, 2.0f});

		REQUIRE(roundFloat(lvl1ch1->get_global_scale().x, 1) == 3.0f);
        REQUIRE(roundFloat(lvl1ch1->get_global_scale().y, 1) == 3.4f);

        REQUIRE(roundFloat(lvl2ch1->get_global_scale().x, 1) == 1.0f);
        REQUIRE(roundFloat(lvl2ch1->get_global_scale().y, 1) == 1.0f);   
	}
}