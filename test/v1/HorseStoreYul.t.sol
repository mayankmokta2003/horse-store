// SPDX-License-Identifier: GPL-3.0-only

pragma solidity 0.8.20;

import { Base_testV1, IHorseStore } from "./Base_testV1.t.sol";
import { HorseStoreYul } from "../../src/horseStoreV1/HorseStoreYul.sol";

contract HorseStoreYulTest is Base_testV1{

    function setUp() public override{
        horseStore = IHorseStore(address(new HorseStoreYul()));
    }

}