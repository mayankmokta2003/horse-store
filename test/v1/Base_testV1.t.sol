// SPDX-License-Identifier: GPL-3.0-only

pragma solidity 0.8.20;

import { Test } from "forge-std/Test.sol";
import { HorseStore } from "../../src/horseStoreV1/HorseStore.sol";
import { IHorseStore } from "../../src/horseStoreV1/IHorseStore.sol";

abstract contract Base_testV1 is Test {

    IHorseStore public horseStore;

    function setUp() public virtual{
        horseStore = IHorseStore(address(new HorseStore()));
    }

    

    function testReadvalue() public virtual{
        uint256 initialValue = horseStore.readNumberOfHorses();
        assertEq(initialValue,0);
    }

    function testCheckHorseNumber(uint256 value) public virtual{
        // uint256 value = 10;
        horseStore.updateHorseNumber(value);
        uint256 actualValue = horseStore.readNumberOfHorses();
        assertEq(value, actualValue);
    }

}