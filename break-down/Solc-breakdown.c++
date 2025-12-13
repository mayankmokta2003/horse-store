6080604052 34801561000f575f80fd5b506101438061001d5f395ff3fe608060405234801561000f575f80fd5b5060043610610034575f3560e01c8063cdfead2e14610038578063e026c01714610054575b5f80fd5b610052600480360381019061004d91906100ba565b610072565b005b61005c61007b565b60405161006991906100f4565b60405180910390f35b805f8190555050565b5f8054905090565b5f80fd5b5f819050919050565b61009981610087565b81146100a3575f80fd5b50565b5f813590506100b481610090565b92915050565b5f602082840312156100cf576100ce610083565b5b5f6100dc848285016100a6565b91505092915050565b6100ee81610087565b82525050565b5f6020820190506101075f8301846100e5565b9291505056fea2646970667358fe12201d640d0586e687fefe7e7b7f0b54cd51fc32b312bbdc50e66bec57b1e902b65664736f6c63430008140033

PUSH1 0x80
PUSH1 0x40
MSTORE      //at 0x40 is ox80


CALLVALUE     // wei
DUP1     
ISZERO     // [ms.value = 0  ,msg.value]
PUSH2 0x000f     
JUMPI    //jump if 0
PUSH0    //  [0x00  msg.value]
DUP1     //[0x00 , 0x00 , msg.value]
REVERT   //revert if ms.value is not zero


// this sticks the runtime code on-chain
JUMPDEST    // [msg.value]
POP         
PUSH2 0x0143   //[0x0143]
DUP1           //   [0x0143   0x0143]
PUSH2 0x001d    //  [0x001d  0x0143  0x0143]
PUSH0           //[0x00  0x001d  0x0143   0x0143]
CODECOPY        // [0x0143]   memory = [0x00  0x001d  0x0143]
PUSH0           // [0x00  0x0143]
RETURN          //
INVALID

// so basically says if someone sends eth revert else jump to 0x000f
PUSH1 0x80
PUSH1 0x40
MSTORE    //free memory pointer
CALLVALUE      //[msg.value]
DUP1           // [msg.value , msg.value]
ISZERO         // check [msg.value == 0]
PUSH2 0x000f   //  push [0x000f , msg.value = 0  msg.value]
JUMPI          // if zero then jump 0x000f
PUSH0          //[0x00  msg.value]
DUP1            //[0x00 , 0x00 , msg.value]
REVERT         // if msg.value != 0 revert

JUMPDEST     //[msg.value]
POP          //[]
PUSH1 0x04     // [0x04]
CALLDATASIZE    //  [eg :calldata_size(0x10)  0x04]
LT              //   [calldata_size < 0x04] returns 1 else 0
PUSH2 0x0034    //   [0x0034    calldata_size < 0x04]
JUMPI           //  if calldata_size < 0x04  jump to 0x0034

PUSH0           //  [0x00]
CALLDATALOAD    //  [32byteCalldata]
PUSH1 0xe0      //  [0xe0   32byteCalldata]
SHR             //  [fnSelector]
DUP1            //  [fnSelector , fnSelector]
PUSH4 0xcdfead2e       //   [0xcdfead2e , fnSelector , fnSelector]
EQ              //  [0xcdfead2e = fnSelector , fnSelector]
PUSH2 0x0038    //  [0x0038 , 0xcdfead2e = fnSelector , fnSelector]
JUMPI           // if 0xcdfead2e = fnSelector true the jump to 0x0038  [fnSelector]
DUP1            // [fnSelector , fnSelector]
PUSH4 0xe026c017      // [0xe026c017 , fnSelector , fnSelector]
EQ              // [0xe026c017 = fnSelector , fnSelector]
PUSH2 0x0054     // [0x0054 , 0xe026c017 = fnSelector , fnSelector]
JUMPI           // if 0xe026c017 = fnSelector jump to 0x0054   [fnSelector]


JUMPDEST   // 0x0034   []   Revert jumpdest
PUSH0     // [0x00]
DUP1      // [0x00 , 0x00]
REVERT    // revert as calldata_size < 0x04  []


JUMPDEST   // 0x0038   [fnSelector]
PUSH2 0x0052    // [0x0052 , fnSelector]
PUSH1 0x04      // [0x04 , 0x0052 , fnSelector]
DUP1            // [0x04 , 0x04 , 0x0052 , fnSelector]
CALLDATASIZE    //  [calldatasize , 0x04 , 0x04 , 0x0052 , fnSelector]
SUB             // [calldatasize - 0x04 , 0x04 , 0x0052 , fnSelector]
DUP2            // [calldatasize - 0x04 , calldatasize - 0x04 , 0x04 , 0x0052 , fnSelector]
ADD             // [ans1 + ans1 , 0x04 , 0x0052 , fnSelector]   ///wrong///
SWAP1           // [0x04 , ans , 0x0052 , fnSelector]
PUSH2 0x004d    // [0x004d , 0x04 , ans , 0x0052 , fnSelector]
SWAP2           // [ans , 0x04 , 0x004d , 0x0052 , fnSelector]
SWAP1           // [0x04 , ans , 0x004d , 0x0052 , fnSelector]
PUSH2 0x00ba    // [0x00ba , 0x04 , ans , 0x004d , 0x0052 , fnSelector]
JUMP            // jump to 0x00ba  [0x04 , ans , 0x004d , 0x0052 , fnSelector]


JUMPDEST    //0x0054  [fnSelector]
PUSH2 0x0072    // [0x0072 , fnSelector]
JUMP   //  jump to 0x0072   [fnSelector]

JUMPDEST  // 0x00ba  [0x04 , ans , 0x004d , 0x0052 , fnSelector]
STOP      // stop

JUMPDEST     // [0x04 , ans , 0x004d , 0x0052 , fnSelector]
PUSH2 0x005c
PUSH2 0x007b
JUMP


JUMPDEST
PUSH1 0x40
MLOAD
PUSH2 0x0069
SWAP2
SWAP1
PUSH2 0x00f4
JUMP
JUMPDEST

PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST

DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
JUMPDEST

PUSH0
DUP1
SLOAD
SWAP1
POP
SWAP1
JUMP
JUMPDEST

PUSH0
DUP1
REVERT
JUMPDEST

PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST

PUSH2 0x0099
DUP2
PUSH2 0x0087
JUMP
JUMPDEST

DUP2
EQ
PUSH2 0x00a3
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST

POP
JUMP
JUMPDEST

PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH2 0x00b4
DUP2
PUSH2 0x0090
JUMP
JUMPDEST

SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST

PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH2 0x00cf
JUMPI
PUSH2 0x00ce
PUSH2 0x0083
JUMP
JUMPDEST

JUMPDEST

PUSH0
PUSH2 0x00dc
DUP5
DUP3
DUP6
ADD
PUSH2 0x00a6
JUMP

JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP

JUMPDEST
PUSH2 0x00ee
DUP2
PUSH2 0x0087
JUMP

JUMPDEST
DUP3
MSTORE
POP
POP
JUMP

JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH2 0x0107
PUSH0
DUP4
ADD
DUP5
PUSH2 0x00e5
JUMP

JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
SAR
PUSH5 0x0d0586e687
INVALID
INVALID
PUSH31 0x7b7f0b54cd51fc32b312bbdc50e66bec57b1e902b65664736f6c6343000814
STOP
CALLER