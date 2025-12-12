// SPDX-License-Identifier: GPL-3.0-only

pragma solidity 0.8.20;

import { Base_testV1, HorseStore } from "./Base_testV1.t.sol";
import { HuffDeployer } from "../../lib/foundry-huff/src/HuffDeployer.sol";

contract HorseStoreHull is Base_testV1 {

    string public constant FILE_PATH = "horseStoreV1/horseStore";  // we write in "" with no src and .huff

    function setUp() public override {
        horseStore = HorseStore(HuffDeployer.config().deploy(FILE_PATH));
    }

}

